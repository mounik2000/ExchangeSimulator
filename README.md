# Exchnage Order Book Simulator (C++ + Python)

## Overview
A high-performance limit order book simulator implemented in C++ with Python bindings.  
Supports full order lifecycle operations and provides benchmarking tools for throughput analysis.

---

## Features

### Core Matching Engine
- Price-time priority limit order book
- Supports BUY / SELL orders
- Deterministic matching logic

### Order Operations
- Add Order
- Modify Order (in-place or price-level migration)
- Cancel Order

### Market Data Features
- Order book snapshot (bid/ask depth)
- Trade generation feed

### Performance
- Benchmark tool for orders/sec throughput
- Mixed workload simulation (add/modify/cancel)

---

## Architecture

Python (research / orchestration)
        ->
pybind11 boundary
        ->
C++ matching engine (low latency core)

---

## Build Instructions

```bash
mkdir build
cmake ..
make -j
cp ExchangeSim* ../pythonBridge/
cd ../pythonBridge/
python test.py
