a = [('국어', 97),('영어',70),('수학', 71),('과학', 70),('한국사', 78)]
print(a)
print(sorted(a, key=lambda x:(x[1], x[0])))