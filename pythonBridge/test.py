import ExchangeSimulator

ex = ExchangeSimulator.ExchangeHandler()

ex.addOrder("AAPL", 1, 100.5, 10, "BUY")
ex.addOrder("AAPL", 2, 100.0, 5, "SELL")
ex.modifyOrder("AAPL", 1, 100.5, 20)
ex.cancelOrder("AAPL",3)

for t in ex.getTrades("AAPL"):
    print(
        t.price,
        t.qty,
        t.buyId,
        t.sellId
    )

result = ex.runBenchmark("AAPL", 500000)
print("OPS/sec:", result.perSecOps)
print("Time:", result.seconds)
