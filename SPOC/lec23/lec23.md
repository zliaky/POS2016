# 磁盘访问 练习

## 问题 1：请执行 FIFO磁盘调度策略

```
./disksim.py  采用FIFO -a 0
./disksim.py   -a 6
./disksim.py   -a 30
./disksim.py   -a 7,30,8
./disksim.py   -a 10,11,12,13,24,1
```
请回答每个磁盘请求序列的IO访问时间

```
./disksim.py -a 0

REQUESTS ['0']

Block:   0  Seek:  0  Rotate:165  Transfer: 30  Total: 195

TOTALS      Seek:  0  Rotate:165  Transfer: 30  Total: 195
```
```
./disksim.py -a 6

REQUESTS ['6']

Block:   6  Seek:  0  Rotate:345  Transfer: 30  Total: 375

TOTALS      Seek:  0  Rotate:345  Transfer: 30  Total: 375
```
```
./disksim.py -a 30

REQUESTS ['30']

Block:  30  Seek: 80  Rotate:265  Transfer: 30  Total: 375

TOTALS      Seek: 80  Rotate:265  Transfer: 30  Total: 375
```
```
./disksim.py -a 7,30,8

REQUESTS ['7', '30', '8']

Block:   7  Seek:  0  Rotate: 15  Transfer: 30  Total:  45
Block:  30  Seek: 80  Rotate:220  Transfer: 30  Total: 330
Block:   8  Seek: 80  Rotate:310  Transfer: 30  Total: 420

TOTALS      Seek:160  Rotate:545  Transfer: 90  Total: 795
```
```
./disksim.py -a 10,11,12,13,24,1

REQUESTS ['10', '11', '12', '13', '24', '1']

Block:  10  Seek:  0  Rotate:105  Transfer: 30  Total: 135
Block:  11  Seek:  0  Rotate:  0  Transfer: 30  Total:  30
Block:  12  Seek: 40  Rotate:320  Transfer: 30  Total: 390
Block:  13  Seek:  0  Rotate:  0  Transfer: 30  Total:  30
Block:  24  Seek: 40  Rotate:260  Transfer: 30  Total: 330
Block:   1  Seek: 80  Rotate:280  Transfer: 30  Total: 390

TOTALS      Seek:160  Rotate:965  Transfer:180  Total:1305
```

## 问题 2：请执行 SSTF磁盘调度策略

```
./disksim.py   -a 10,11,12,13,24,1

```
请回答每个磁盘请求序列的IO访问时间

```
./disksim.py -p SSTF -a 10,11,12,13,24,1

REQUESTS ['10', '11', '12', '13', '24', '1']

Block:  10  Seek:  0  Rotate:105  Transfer: 30  Total: 135
Block:  11  Seek:  0  Rotate:  0  Transfer: 30  Total:  30
Block:   1  Seek:  0  Rotate: 30  Transfer: 30  Total:  60
Block:  12  Seek: 40  Rotate:260  Transfer: 30  Total: 330
Block:  13  Seek:  0  Rotate:  0  Transfer: 30  Total:  30
Block:  24  Seek: 40  Rotate:260  Transfer: 30  Total: 330

TOTALS      Seek: 80  Rotate:655  Transfer:180  Total: 915
```

## 问题 3：请执行 SCAN, C-SCAN磁盘调度策略

```
./disksim.py   -a 10,11,12,13,24,1
```
请回答每个磁盘请求序列的IO访问时间

```
```