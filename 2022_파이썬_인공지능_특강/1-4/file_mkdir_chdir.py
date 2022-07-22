import os

os.mkdir("tmp")
os.chdir("tmp")

for x in range(26):
    fname = chr(ord("a")+x)+".txt"
    file = open(fname, "w")
    file.write(chr(ord("a")+x))
    file.close()