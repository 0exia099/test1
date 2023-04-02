"""
 Project : Fernet사용
 Author : 심상혁
 Date of first create : April 3, 2023
 Major features:
   -파이썬의 Fernet 라이브러리를 사용하여 외부 파일을 암호화하여 외부 파일에 저장
   -외부 파일의 암호화된 내용을 복호화하여 결과 출력
 Date of last update : April 3, 2023
 Revised contesnt : 
   -v1.0 : April 3, 2023
        * first create
"""

from cryptography.fernet import Fernet

key = Fernet.generate_key()

f = Fernet(key)
with open('data.txt', 'rb') as file:
    text = file.read()
    token = f.encrypt(text)
    with open('encrypted.txt', 'wb') as encrypted:
        encrypted.write(token)

f = Fernet(key)
with open('encrypted.txt', 'rb') as file:
    token = file.read()
    d = str(f.decrypt(token), 'utf-8')
    print(f'복호화: {d}')
