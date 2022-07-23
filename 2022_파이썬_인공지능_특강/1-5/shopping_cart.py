from collections import Counter

#file_name, conf, supp = input("파일 이름, 신뢰도, 지지도를 입력하세요: ").split()
file_name = "large.txt"
conf = 0.4
supp = 0.1
conf = float(conf)
supp = float(supp)
file = open(file_name,"r")
freq = {}
n=0
for line in file:
    n += 1
    items = sorted([int(x) for x in line.split()][2:])
    for x in range(len(items)-1):
        for y in range(x+1,len(items)):
            freq[(items[x], items[y])] = freq.get((items[x], items[y]), 0) + 1

limit = int(n*supp)+1
candidate = sorted(filter(lambda x:x[1]>=limit, freq.items()), key=lambda x:x[1], reverse=True)
print(candidate)