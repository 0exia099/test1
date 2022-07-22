import hashlib
import getpass

login = input("login id? ")
pwd = getpass.getpass(prompt="암호 입력: ")

file = open("login.txt", "r")
encrypted = hashlib.sha256(pwd.encode()).hexdigest()

find = False

for line in file:
    uid, pw = line.split(":")
    pw = pw.strip()
    if uid == login:
        if encrypted == pw:
            print("로그인 성공")
            find = True
        else:
            find = True
            print("암호가 틀렸습니다.")
        break

if find == False:
    print("등록되지 않은 id")

file.close()