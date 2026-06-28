#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "orderBook.h"
#include "exchangeHandler.h"

namespace py = pybind11;

PYBIND11_MODULE(ExchangeSimulator, m) {

    py::class_<Trade>(m, "Trade")
        .def_readonly("price", &Trade::_price)
        .def_readonly("qty", &Trade::_qty)
        .def_readonly("buyId", &Trade::_buyId)
        .def_readonly("sellId", &Trade::_sellId);

    py::class_<Level>(m, "Level")
        .def_readonly("price", &Level::_price)
        .def_readonly("qty", &Level::_totalQty)
        .def_readonly("orderCount", &Level::_orderCount);

    py::class_<BenchResult>(m, "BenchResult")
        .def_readonly("seconds", &BenchResult::_seconds)
        .def_readonly("perSecOps", &BenchResult::_perSecOps);

    py::class_<OrderBook>(m, "OrderBook")
        .def(py::init<>())
        .def("addOrder", &OrderBook::addOrder)
        .def("cancelOrder", &OrderBook::cancelOrder)
        .def("modifyOrder", &OrderBook::modifyOrder)
        .def("getTrades", &OrderBook::getTrades)
        .def("getSnapshot", &OrderBook::getSnapshot)
        .def("runBenchmark", &OrderBook::runBenchmark);

    py::class_<ExchangeHandler>(m, "ExchangeHandler")
        .def(py::init<>())
        .def("addOrder", &ExchangeHandler::addOrder)
        .def("cancelOrder", &ExchangeHandler::cancelOrder)
        .def("modifyOrder", &ExchangeHandler::modifyOrder)
        .def("getTrades", &ExchangeHandler::getTrades)
        .def("getSnapshot", &ExchangeHandler::getSnapshot)
        .def("runBenchmark", &ExchangeHandler::runBenchmark);
}
