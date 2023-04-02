"""
 Project : Turtle drawing of a rectangle
 Author : 심상혁
 Date of first create : March 6, 2023
 Major features:
   -draw a rectangle with the width and length entered
 Date of last update : March 8, 2023
 Revised contesnt : 
   -v1.0 : March 6, 2023
        * first create
   -v1.1 : March 8, 2023
        * revised the comment
"""
import turtle

# 가로 입력
width_str = input("width of rectangle = ")
width = int(width_str)    # 입력받은 가로를 int형으로 변경
# 세로 입력
length_str = input("length of rectangle = ")
length = int(length_str)    # 입력받은 세로를 int형으로 변경
# 시작좌표(사각형의 왼쪽 위)
start_width = 0 - (width / 2)
start_length = 0 + (length / 2)
# 시작좌표를 기준으로 사각형의 꼭짓점 리스트 생성
rectangle = [(start_width, start_length),   # 왼쪽 위
             (start_width + width, start_length),   # 오른쪽 위
             (start_width + width, start_length - length),    # 오른쪽 아래
             (start_width, start_length - length)]    # 왼쪽 아래
t = turtle.Turtle() # 터틀 객체 생성
t.shape("turtle"); t.color("red"); t.width(5); t.speed(1)
t.up(); t.goto(0, 0); t.down()  # 펜을 들고 0,0으로 이동
# 사각형 꼭짓점 리스트를 이용해 사각형을 그린다
for i in range(len(rectangle)):
    x, y = rectangle[i]
    if i == 0:
        t.up(); t.goto(x, y); t.down()
    else:
        t.goto(x, y)
sx, sy = rectangle[0]
t.goto(sx, sy)
# 다 그린 후 펜을 들고 0,0으로 이동
t.up(); t.goto(0, 0); t.down()
