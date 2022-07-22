
import pickle

def dump(fname, container):
    ofile = open(fname, "ab")
    pickle.dump(container,ofile)
    ofile.close()
    
dump("pf.dat", ('A', 'B', 'C'))
dump("pf.dat", {"aaa", "bbb","ccc"})
dump("pf.dat", {1:"aaa", 2:"bbb",3:"ccc"})

pfile = open("pf.dat", "rb")

L=[]

try:
    while True:
        L.append(pickle.load(pfile))
except EOFError:
    pass

print(L)
pfile.close()