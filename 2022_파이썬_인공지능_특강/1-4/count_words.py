##
#	이 프로그램은 파일 안의 단어들의 개수를 센다.
#

filename = input("파일명을 입력하세요: ").strip()
infile = open(filename, "r") # 파일을 연다.

freqs = {}

# 파일의 각 줄에 대하여 문자를 추출한다. 각 문자를 사전에 추가한다. 
for line in infile:
    for word in line.split():		# 양쪽 끝의 공백 문자를 제거한다.
        if word in freqs:		# 문자열 안의 각 문자에 대하여 
            freqs[word] += 1		# 딕셔너리의 횟수를 증가한다. 
        else:				# 처음 나온 문자이면
            freqs[word] = 1		# 딕셔너리의 횟수를 1로 초기화한다. 

print(sorted(freqs.items()))
infile.close()