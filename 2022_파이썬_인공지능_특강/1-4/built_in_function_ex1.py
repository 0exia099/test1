n = int(input("양의 정수 : "))
print([x for x in range(1,n+1) if x%3==0])
print(len([x for x in range(1,n+1) if x%3==0]))
print(sum([1 for x in range(1,n+1) if x%3==0]))