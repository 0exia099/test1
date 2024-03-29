import hashlib
from bitmap import BitMap

class BloomFilter:
    def __init__(self, m, k):
        self.m = m
        self.k = k
        self.n = 0
        self.bf = BitMap(m)
    
    def getPositions(self, item):
        return [int((hashlib.sha256("".join([item, str(i)]).encode())).hexdigest(),16)%self.m for i in range(1,self.k+1)]
    
    def add(self, item):
        for i in self.getPositions(item):
            self.bf.set(i)
        self.n += 1
        return
    
    def contains(self, item):
        for i in self.getPositions(item):
            if not self.bf.test(i):
                return False
        return True
    
    def reset(self):
        for i in range(self.m):
            self.bf.reset(i)
        self.n = 0
        return
    
    def __repr__(self):
        return f'M = {self.m}, F = {self.k}\nBitMap = {self.bf}\n항목의 수 = {self.n}, 1인 비트수 = {self.bf.count()}'
        
if __name__ == "__main__":
    bf = BloomFilter(53,3)
    for ch in "AEIOU":
        bf.add(ch)
    print(bf)
    for ch in "ABCDEFGHIJ":
        print(ch, bf.contains(ch))