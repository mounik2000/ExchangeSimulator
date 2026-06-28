import ExchangeSimulator

ex = ExchangeSimulator.ExchangeHandler()

ex.addOrder("JIOF", 1, 100.5, 10, "BUY")
ex.addOrder("JIOF", 2, 100.0, 5, "SELL")
ex.modifyOrder("JIOF", 1, 100.5, 20)
ex.cancelOrder("JIOF",3)

for t in ex.getTrades("JIOF"):
    print(
        t.price,
        t.qty,
        t.buyId,
        t.sellId
    )


for s in ["JIOF","AMZN","GOOG","NVDA"]:
    result = ex.runBenchmark(s, 100000)
    print("Symbol:", s)
    print("OPS/sec:", result.perSecOps)
    print("Time:", result.seconds)
    print("NanoSecPerOp", result.seconds*10000)
