def make_shingle_set(fname,k):
    sset = set()
    ofile = open(fname, "r")
    text = ofile.read().split()
    for i in range(len(text)-k+1):
        sset.add(tuple(text[i:i+k]))
    return sset

# def make_shingle_map(fname, k):
#     smap = {}
#     ofile = open(fname, "r")
#     text = ofile.read().split()
#     for i in range(len(text)-k+1):
#         smap[tuple(text[i:i+k])] = smap.get(tuple(text[i:i+k]),0)+1
#     return smap

file_name1, file_name2 = input("두개의 파일 이름: ").split()
shingle_num = int(input("Shingle의 수(k): "))

# file_name1 = "d1.txt"
# file_name2 = "d2.txt"
# shingle_num = 5

s1 = make_shingle_set(file_name1, shingle_num)
s2 = make_shingle_set(file_name2, shingle_num)

print("문자열 집합을 이용한 유사도=",len(s1&s2)/len(s1|s2))

# s1 = make_shingle_map(file_name1, shingle_num)
# s2 = make_shingle_map(file_name2, shingle_num)

# print("문자열 map을 이용한 유사도=",)