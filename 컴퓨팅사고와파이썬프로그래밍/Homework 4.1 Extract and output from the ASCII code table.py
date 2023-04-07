"""
 Project : Homework 4.1 Extract and output from the ASCII code table
 Author : 심상혁
 St_ID : 21812076
 Major : 컴퓨터공학과
 Date of first create : March 22, 2023
 Major features:
   -ASCII 코드표에서 숫자, 알파벳 대문자, 알파벳 소문자 추출하여 리스트에 추가
   -리스트의 길이와 원소들 출력
 Date of last update : March 22, 2023
 Revised contesnt : 
   -v1.0 : March 22, 2023
        * first create
"""

# ASCII 코드표에서 숫자, 알파벳 대문자, 소문자 추출하여 리스트 생성
L_digits = [chr(_) for _ in range(ord('0'), ord('9')+1)]
L_upper = [chr(_) for _ in range(ord('A'), ord('Z')+1)]
L_lower = [chr(_) for _ in range(ord('a'), ord('z')+1)]
# 길이와 원소 출력
print('L_digits (size :{}) : {}'.format(len(L_digits), L_digits))
print('L_upper case alphabets (size :{}) : {}'.format(len(L_upper), L_upper))
print('L_lower case alphabets (size :{}) : {}'.format(len(L_lower), L_lower))
