#pragma once
#include "orderBook.h"
#include <unordered_map>
#include <string>

class ExchangeHandler {
public:
    void addOrder(const std::string& symbol, int id, double price, int qty, std::string side);
    void modifyOrder(const std::string& symbol, int id, double price, int qty);
    void cancelOrder(const std::string& symbol, int id);
    std::vector<Trade> getTrades(const std::string& symbol);
    BenchResult runBenchmark(const std::string& symbol, int numOperations);
private:
    std::unordered_map<std::string, OrderBook> _orderBooks;
};
