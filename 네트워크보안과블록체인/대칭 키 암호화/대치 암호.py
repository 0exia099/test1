"""
 Project : 대치 암호
 Author : 심상혁
 Date of first create : April 3, 2023
 Major features:
   -알파벳을 랜덤으로 배치하여 딕셔너리를 만들어 대치 암호 만들기
 Date of last update : April 3, 2023
 Revised contesnt : 
   -v1.0 : April 3, 2023
        * first create
"""
import random

E = {chr(ord('a') + i):chr(ord('a') + num) for i, num in enumerate(random.sample(range(26),26))}
D = {v:k for k, v in E.items()}

plaintext = input('평문 입력: ').lower()

ciphertext = [E[word] if word.isalpha() else ' ' for word in plaintext]
print(f"암호문: {''.join(w for w in ciphertext)}")

decryptionText = [D[word] if word.isalpha() else ' ' for word in ciphertext]
print(f"복호문: {''.join(w for w in decryptionText)}")
