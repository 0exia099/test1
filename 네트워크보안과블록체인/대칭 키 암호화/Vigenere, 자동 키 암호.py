"""
 Project : Vigenere, 자동 키 암호
 Author : 심상혁
 Date of first create : April 3, 2023
 Major features:
   -영어 문장을 평문으로 입력받은 후, 입력받은 키를 이용한 Vigenere 암호 생성, 복호화
   -입력 받은 평문을 자동 키를 입력받아 자동 키 암호 생성, 복호화
 Date of last update : April 3, 2023
 Revised contesnt : 
   -v1.0 : April 3, 2023
        * first create
"""
plaintext = [alpha.upper() for alpha in input('평문 입력: ') if alpha.isalpha()]
vigenereKey = [ord(w.upper()) - ord('A') for w in input('Vigenere 암호? ') if w.isalpha()]

ciphertext = [chr((ord(word) - ord('A') + vigenereKey[i % len(vigenereKey)])%26 + ord('A')) for i, word in enumerate(plaintext)]
print(f"암호문: {''.join(w for w in ciphertext)}")

decryptionText = [chr((ord(word) - ord('A') - vigenereKey[i % len(vigenereKey)])%26 + ord('A')) for i, word in enumerate(ciphertext)]
print(f"평문: {''.join(w for w in decryptionText)}")

autoKey = int(input('자동 키 암호? '))

key = autoKey
autoCiphertext = []
for word in plaintext:
    autoCiphertext.append(chr((ord(word) - ord('A') + key)%26 + ord('A')))
    key = ord(word) - ord('A')
print(f"암호문: {''.join(w for w in autoCiphertext)}")

key = autoKey
autodecryptionText = []
for word in autoCiphertext:
    text = chr((ord(word) - ord('A') - key)%26 + ord('A'))
    autodecryptionText.append(text)
    key = ord(text) - ord('A')
print(f"평문: {''.join(w for w in autodecryptionText)}")
