class View:
    def __init__(self, items):
        self.set = set(items)
        
    def similarity(self, other):
        return len(self.set & other.set)/len(self.set|other.set)
    
    def __repr__(self):
        return f"{self.set}"

file_name, rnum, cnum = input("파일 이름, 추천인 수, 추천 콘텐츠 수? ").split()
#file_name = "v.txt"

rnum = int(rnum)
cnum = int(cnum)

file=open(file_name, "r")
uvmap = {}
for line in file:
    item = line.split()
    uvmap[item[0]] = View(item[1:])
    
file.close()
while True:
    user = input("사용자 이름?")
    if user == 'q':
        break
    
    target = uvmap[user]
    candidate = sorted(uvmap.items(), key=lambda x:x[1].similarity(target), reverse=True)[1:cnum+1]
    print(candidate)

