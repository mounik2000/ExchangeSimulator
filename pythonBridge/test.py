import ExchangeSimulator

ex = ExchangeSimulator.ExchangeHandler()

ex.addOrder("AAPL", 1, 100.5, 10, "BUY")
ex.addOrder("AAPL", 2, 100.0, 5, "SELL")
ex.modifyOrder("AAPL", 1, 100.5, 20)

print(ex.getTrades("AAPL"))

result = ex.runBenchmark("AAPL", 500000)
print("OPS/sec:", result.perSecOps)
print("Time:", result.seconds)
