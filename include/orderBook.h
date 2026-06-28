#pragma once
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <deque>

enum class Side { BUY, SELL };

struct Order {
    int _id;
    double _price;
    int _qty;
    Side _side;
};

struct Trade {
    double _price;
    int _qty;
    int _buyId;
    int _sellId;
};

struct BenchResult {
    double _seconds;
    double _perSecOps;
};

struct Level {
    double _price;
    int _totalQty;
    int _orderCount;
};

class OrderBook {
public:
    void addOrder(int id, double price, int qty, std::string side);
    void modifyOrder(int id, double price, int qty);
    void cancelOrder(int id);
    std::vector<Trade> getTrades();
    std::pair<std::vector<Level>, std::vector<Level>> getSnapshot(int numLevels = -1);
    BenchResult runBenchmark(int numOperations);

private:
    using OrderQueue = std::deque<Order>;
    using BidBook = std::map<double, OrderQueue, std::greater<>>;
    using AskBook = std::map<double, OrderQueue, std::greater<>>;

    BidBook _buyBook;
    AskBook _sellBook;

    struct Location {
        Side _side;
        double _price;
        OrderQueue* _queue;
        OrderQueue::iterator _it;
    };

    std::unordered_map<int, Location> _orderMap;
    std::vector<Trade> _trades;
    void match();
};
