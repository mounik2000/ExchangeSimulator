#include "orderBook.h"
#include <chrono>
#include <algorithm>
#include <climits>

static Side parseSide(const std::string& s) {
    return (s == "BUY") ? Side::BUY : Side::SELL;
}

void OrderBook::addOrder(int id, double price, int qty, std::string side) {
    Side s = parseSide(side);
    Order order{id, price, qty, s};

    if (s == Side::BUY) {
        auto& q = _buyBook[price];
        q.push_back(order);
        _orderMap[id] = {s, price, &q, std::prev(q.end())};
    } else {
        auto& q = _sellBook[price];
        q.push_back(order);
        _orderMap[id] = {s, price, &q, std::prev(q.end())};
    }
    match();
}

void OrderBook::cancelOrder(int id) {
    if (_orderMap.find(id) == _orderMap.end()) return;

    auto loc = _orderMap[id];
    auto& q = *(loc._queue);
    q.erase(loc._it);
    if (q.empty()) {
        if (loc._side == Side::BUY) _buyBook.erase(loc._price);
        else _sellBook.erase(loc._price);
    }
    _orderMap.erase(id);
}

void OrderBook::modifyOrder(int id, double price, int qty) {
    if (_orderMap.find(id) == _orderMap.end()) return;

    auto loc = _orderMap[id];
    Order& order = *(loc._it);
    
    //TODO: PriceTime
    if (loc._price == price) {
        order._qty = qty;
        return;
    }

    cancelOrder(id);
    addOrder(id, price, qty, (loc._side == Side::BUY ? "BUY" : "SELL"));
}

void OrderBook::match() {
    while (!_buyBook.empty() && !_sellBook.empty()) {
        auto bidIt = _buyBook.begin();
        auto askIt = _sellBook.begin();

        if (bidIt->first < askIt->first) break;

        auto& bq = bidIt->second;
        auto& aq = askIt->second;

        while (!bq.empty() && !aq.empty()) {
            Order& bid = bq.front();
            Order& ask = aq.front();

            int qty = std::min(bid._qty, ask._qty);

            _trades.push_back({askIt->first, qty, bid._id, ask._id});

            bid._qty -= qty;
            ask._qty -= qty;

            if (bid._qty == 0) {
                _orderMap.erase(bid._id);
                bq.pop_front();
            }

            if (ask._qty == 0) {
                _orderMap.erase(ask._id);
                aq.pop_front();
            }
        }

        if (bq.empty()) _buyBook.erase(bidIt);
        if (aq.empty()) _sellBook.erase(askIt);
    }
}

std::vector<Trade> OrderBook::getTrades() {
    auto out = _trades;
    _trades.clear();
    return out;
}

std::pair<std::vector<Level>, std::vector<Level>> OrderBook::getSnapshot(int numLevels) {
    std::vector<Level> bidLevels, askLevels;
    int totalLevels = INT_MAX;
    if (numLevels > 0) totalLevels = numLevels;

    int levels = 0;
    for (auto it = _buyBook.begin(); ((it != _buyBook.end()) & (levels < totalLevels)); ++it) {
        int qty = 0;
        int orderCount = 0;
        for (auto& o : it->second) {
            qty += o._qty;
            orderCount++;
        }
        bidLevels.push_back({it->first, qty, orderCount});
        levels++;
    }

    levels = 0;
    for (auto it = _sellBook.begin(); ((it != _sellBook.end()) & (levels < totalLevels)); ++it) {
        int qty = 0;
        int orderCount = 0;
        for (auto& o : it->second) {
            qty += o._qty;
            orderCount++;
        }
        askLevels.push_back({it->first, qty, orderCount});
    }

    return {bidLevels, askLevels};
}

BenchResult OrderBook::runBenchmark(int operations) {
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    int id = 1;
    for (int i = 0; i < operations; i++) {
        if (i % 3 == 0)
            addOrder(id++, 100 + (i % 10), 10, "BUY");
        else if (i % 3 == 1)
            addOrder(id++, 100 + (i % 10), 10, "SELL");
        else if (id > 10)
            modifyOrder(id / 2, 101, 5);
        if (i % 50 == 0 && id > 10)
            cancelOrder(id - 5);
    }

    auto end = high_resolution_clock::now();
    double sec = duration_cast<duration<double>>(end - start).count();

    return {sec, operations / sec};
}
