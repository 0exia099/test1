"""
 Project : Print deciaml, binary, octal, hexadecimal
 Author : 심상혁
 Date of first create : March 9, 2023
 Major features:
   -Decimal, binary, octal, and hexadecimal outputs for integers from 0 to 255
 Date of last update : March 9, 2023
 Revised contesnt : 
   -v1.0 : March 9, 2023
        * first create
"""

# ==============...출력
for i in range(35):
    print('=', end='')
print('\n Decimal  Binary  Octal Hexadecimal')

# --------------...출력
for i in range(35):
    print('-', end='')
print()

# 칸수에 맞춰 출력
for i in range(256):
    print('{0:8d} {0:08b} {0:#05o} {0:#04X}'.format(i))

# ==============...출력
for i in range(35):
    print('=', end='')
print()
