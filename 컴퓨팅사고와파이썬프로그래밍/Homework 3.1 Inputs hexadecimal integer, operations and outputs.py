"""
 Project : Homework 3.1 Inputs hexadecimal integer, operations and outputs
 Author : 심상혁
 St_ID : 21812076
 Major : 컴퓨터공학과
 Date of first create : March 17, 2023
 Major features:
   -2개의 16진수 데이터 문자열력을 한줄로 입력받고 정수 변환
   -두 16진수 값을 10진수, 2진수로 출력 및 bit-wise AND, bit-wise OR, bit-wise XOR 값 출력
 Date of last update : March 17, 2023
 Revised contesnt : 
   -v1.0 : March 17, 2023
        * first create
"""

# 두 16진수 입력
a, b = input('input two hexadecimal numbers (예: 0xA3 0x3A) : ').split()
a, b = int(a, 16), int(b, 16)   # int형으로 변환
# 형식에 맞춰 출력
print('a = {0:#04x} = {0:4d} = {0:#010b}'.format(a))
print('b = {0:#04x} = {0:4d} = {0:#010b}'.format(b))
print('a & b = {0:#04X} = {0:4d} = {0:#010b}'.format(a & b))
print('a | b = {0:#04X} = {0:4d} = {0:#010b}'.format(a | b))
print('a ^ b = {0:#04X} = {0:4d} = {0:#010b}'.format(a ^ b))
