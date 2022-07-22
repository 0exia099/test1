def square(n):
    return n*n

def squareList(input_list):
    return list(map(square,input_list))

l1 = list(range(1,10))
l2 = list(range(1,50,5))
print(squareList(l1))
print(squareList(l2))