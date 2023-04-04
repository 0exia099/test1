"""
 Project : Float data input and statistical analysis
 Author : 심상혁
 Date of first create : March 9, 2023
 Major features:
   -10개의 실수 데이터를 한줄에 입력(공백으로 구분)
   -입력값을 문자열, 실수로 출력 후 평균, 분산, 표준편차 출력
 Date of last update : March 9, 2023
 Revised contesnt : 
   -v1.0 : March 9, 2023
        * first create
"""
import math     #math.sqrt()를 사용하기 위한 math

TARGET_NUM_DATA = 10

for i in range(2):  # 2번 반복
    # 입력값에 split으로 공백 구분(슬라이싱을 사용해 10개만 가져오게 한다)
    float_strings = input('input 10 float data (separated in space) = ').split(sep=' ')[:TARGET_NUM_DATA]
    L_data = list(map(float, float_strings))    # float형의 리스트로 변경
    
    avg = sum(L_data)/len(L_data)   # 평균 구하기
    # 분산 구하기
    vsum = 0
    for i in L_data:
        vsum = vsum + (avg - i)**2  # (평균 - 값)의 제곱의 합
    var = vsum / len(L_data)
    
    std = math.sqrt(var)    # math의 sqrt로 분산의 제곱근 = 표준편차
    # 구한 항목들 출력
    print('float_strings = {}'.format(float_strings))
    print('L_data = {}'.format(L_data))
    print('avg = {}, var = {}, std = {}\n'.format(avg, var, std))
