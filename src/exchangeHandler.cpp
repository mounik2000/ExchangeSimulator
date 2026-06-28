#include "exchangeHandler.h"

void ExchangeHandler::addOrder(const std::string& symbol, int id, double price, int qty, std::string side) {
    _orderBooks[symbol].addOrder(id, price, qty, side);
}

void ExchangeHandler::cancelOrder(const std::string& symbol, int id) {
    _orderBooks[symbol].cancelOrder(id);
}

void ExchangeHandler::modifyOrder(const std::string& symbol, int id, double price, int qty) {
    _orderBooks[symbol].modifyOrder(id, price, qty);
}

std::vector<Trade> ExchangeHandler::getTrades(const std::string& symbol) {
    return _orderBooks[symbol].getTrades();
}
    
std::pair<std::vector<Level>, std::vector<Level>> ExchangeHandler::getSnapshot(const std::string& symbol, int numLevels) {
    return _orderBooks[symbol].getSnapshot(numLevels);
}

BenchResult ExchangeHandler::runBenchmark(const std::string& symbol, int numOps) {
    return _orderBooks[symbol].runBenchmark(numOps);
}
