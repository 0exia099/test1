import hashlib
import getpass

login = input("login id? ")
pwd = getpass.getpass(prompt="암호 등록: ")

file = open("login.txt", "a")
encrypted = hashlib.sha256(pwd.encode()).hexdigest()
print(f"{login}:{encrypted}", file=file)
file.close()