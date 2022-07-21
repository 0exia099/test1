list1 = []
list2 = []
list3 = list1

print(list1 == list2)
print(list1 is list2)
print(list1 is list3)

list3 = list3+list2
print(list1 is list3)
print(list1 == list3)