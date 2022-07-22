class MyEnumerate:
    def __init__(self, seq):
        self.seq = seq[:]
        self.index = 0
        
    def __iter__(self):
        return self
    
    def __next__(self):
        if self.index == len(self.seq):
            raise StopIteration
        else:
            self.index+=1
            return (self.index-1, self.seq[self.index-1])
        
for index, letter in MyEnumerate(['강감찬', '이순신', '을지문덕']):
    print(f"{index} : {letter}")
    
def myCounter(start,step):
    value = start
    while True:
        yield value
        value += step
        
for x in myCounter(1,2):
    print(x, end=" ")
    if x>100:
        break
    
print()


import math

def picalc():
    n = 1
    denom = 1
    sum = 0
    increment = 0
    while True:
        sum+=n/denom
        yield sum *2
        increment+=1
        n*=increment
        denom*=2*increment+1
        
g = picalc()
for _ in range(20):
    print(next(g))