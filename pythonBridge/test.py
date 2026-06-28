import ExchangeSimulator

ex = ExchangeSimulator.ExchangeHandler()

ex.addOrder("JIOF", 1, 99.0, 5, "BUY")
ex.addOrder("JIOF", 2, 100.0, 5, "SELL")

for s in ex.getSnapshot("JIOF", 5):
    for j in s:
        print(j.price, " ", j.qty, " ", j.orderCount)

ex.modifyOrder("JIOF", 1, 100.5, 20)

for t in ex.getTrades("JIOF"):
    print(
        t.price,
        t.qty,
        t.buyId,
        t.sellId
    )

for s in ex.getSnapshot("JIOF", 5):
    for j in s:
        print(j.price, " ", j.qty, " ", j.orderCount)

ex.cancelOrder("JIOF",3)

for s in ex.getSnapshot("JIOF", 5):
    for j in s:
        print(j.price, " ", j.qty, " ", j.orderCount)

for s in ["JIOF","AMZN","GOOG","NVDA"]:
    result = ex.runBenchmark(s, 100000)
    print("Symbol:", s)
    print("OPS/sec:", result.perSecOps)
    print("Time:", result.seconds)
    print("NanoSecPerOp", result.seconds*10000)


'''
Sample o/p
99.0   5   1
100.0   5   1
100.0 5 1 2
100.5   15   1
100.5   15   1
Symbol: JIOF
OPS/sec: 19907941.69600931
Time: 0.005023121
NanoSecPerOp 50.231210000000004
Symbol: AMZN
OPS/sec: 19677884.83203056
Time: 0.005081847
NanoSecPerOp 50.81847
Symbol: GOOG
OPS/sec: 19687663.099983994
Time: 0.005079323
NanoSecPerOp 50.79323
Symbol: NVDA
OPS/sec: 19512374.06469874
Time: 0.005124953
NanoSecPerOp 51.24953

'''
