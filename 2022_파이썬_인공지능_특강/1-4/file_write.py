outfile = open("output.txt", "w")
outfile.write("김영희\n")
outfile.close()

with open("output.txt", "w") as f:
    f.write("김영희\n")
    f.write("최자영\n")