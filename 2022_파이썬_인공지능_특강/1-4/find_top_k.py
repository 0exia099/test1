import nltk

from nltk.corpus import stopwords

#nltk.download('stopwords')
stop_words = stopwords.words('english')

stop_words.append('though')

#file_name, minlen, k = input("입력? ").split()
#minlen, k = int(minlen), int(k)
file_name = "mobydick.txt"
minlen = 5
k = 10
ofile = open(file_name, "r")
d={}
for line in ofile:
    for word in line.lower().split():
        if len(word)<minlen or word in stop_words:
            continue
        d[word] = d.get(word,0)+1
            

ofile.close()
result=sorted(d.items(), key=lambda x:x[1], reverse=True)[:k]
print(result)


import re

file = open(file_name, "r")
text = file.read().lower()

freq = {}
for sentence in re.split("[.?!]", text):
    words = sorted(sentence.split())
    for x in range(len(words) - 1):
        if len(words[x]) < minlen or words[x] in stop_words:
            continue
        for y in range(x+1, len(words)):
            if len(words[y]) < minlen or words[y] in stop_words or words[x] == words[y]:
                continue
            freq[(words[x], words[y])] = freq.get((words[x], words[y]), 0) + 1
file.close()
results = sorted(freq.items(), key=lambda x:x[1], reverse=True)[:k]
print(results)
