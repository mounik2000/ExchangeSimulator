cmake_minimum_required(VERSION 3.10)
project(md_exchange)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

find_package(pybind11 REQUIRED)


include_directories(include)

pybind11_add_module(ExchangeSimulator
    src/bindings.cpp
    src/orderBook.cpp
    src/exchangeHandler.cpp
)
