import pickle
import random

A = []

for _ in range(10):
    num = random.randint(1,100)
    A.append(num)
    print(num, end=" ")
print()
ofile = open( "pf.dat", "wb" )
pickle.dump( A, ofile )
ofile.close()

B = []

ofile = open("pf.dat", "rb")
obj = pickle.load(ofile)
print(obj)
ofile.close()