#가장 긴 단어 출력

file_name = input("파일 이름을 입력: ")
infile = open(file_name, "r")

max_word = ""

for line in infile:
    for word in line.split():
        if len(word)>len(max_word):
            max_word = word

print(max_word, len(max_word))
infile.close()