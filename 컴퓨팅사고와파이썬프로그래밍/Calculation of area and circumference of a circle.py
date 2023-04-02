# Project : Calculation of area and circumference of a circle
# Author : Sang-Hyeok Sim
# Date of first create : March 6, 2023
# Major features:
#   -input radius
#   -output area, circumference
# Date of last update : March 6, 2023
# Revised contesnt : 
#   -Null

import math

# 여러개 출력을 위해 while문 사용
while(True):    # True를 주어 if문을 통한 break까지 계속 반복
    # 반지름 입력
    radius_str = input("input radius of circle = ")
    radius = int(radius_str)    # 입력받은 반지름을 int형으로 변경

    if radius == 0: # 입력 반지름이 0인경우 while문 종료
        break

    # math.pi를 이용하여 원주율을 구해 반지름, 넓이, 원둘레 출력
    print("circle of radius ({}) : area ({:.4f}), circumference ({:.4f})"\
          .format(radius, (radius ** 2) * math.pi, 2 * radius * math.pi))
    

