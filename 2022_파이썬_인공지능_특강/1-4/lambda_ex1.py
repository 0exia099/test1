def squareList(input_list):
    return list(map(lambda y:y*y,input_list))

def squareEventList(input_list):
    return list(map(lambda y:y*y,filter(lambda x:x%2==0, input_list)))

l1 = list(range(1,10))
l2 = list(range(1,50,5))

print(squareList(l1))
print(squareList(l2))

print(squareEventList(l1))
print(squareEventList(l2))