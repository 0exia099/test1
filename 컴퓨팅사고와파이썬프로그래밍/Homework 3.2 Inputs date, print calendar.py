"""
 Project : Homework 3.2 Inputs date, print calendar
 Author : 심상혁
 St_ID : 21812076
 Major : 컴퓨터공학과
 Date of first create : March 17, 2023
 Major features:
   -연, 월, 일을 3개의 정수로 입력받음
   -해당 달의 달력을 출력
 Date of last update : March 17, 2023
 Revised contesnt : 
   -v1.0 : March 17, 2023
        * first create
"""
# 본 프로그램을 위한 지식
# 윤년 : 해당 년도가 4로 나누어떨어지며 100으로 나누어떨어지지 않는 년도.
#        또는 400으로 나누어떨어지는 년도.
# 매 년의 1월 1일의 요일 : 1년의 1월 1일은 월요일이고 2년의 1월 1일은 화요일,
#       3년은 수요일, 4년은 목요일, 5년은 토요일 ... 이다.
#       기본적으로 매년 한 요일씩 늘어나지만 윤년의 다음년도의 경우는 두 요일씩 늘어난다.
#       이는 365 % 7 가 1이라 매년 한 요일씩 늘어나지만 윤년은 366일이라 두 요일씩 늘어난다.

# 숫자에 따른 달 영문 딕셔너리
month_idx = {'1':'January', '2':'February', '3':'March', '4':'April', 
         '5':'May', '6':'June', '7':'July', '8':'August', 
         '9':'September', '10':'October', '11':'November', '12':'December'}
# 각 달의 일수 리스트
month_day = [31,28,31,30,31,30,31,31,30,31,30,31]
# 요일 이름 튜플
week = ('SUN', 'MON', 'TUE', 'WED', 'THR', 'FRI', 'SAT')

# 윤년계산 함수
def is_leap_year(year):
    if (((year%4) == 0) and (year%100 != 0)) or (year%400 == 0):
        return True
    else:
        return False

# 연, 월, 일 입력
date = input('input year month day : ').split()

# 입력값을 int형으로 변형
year = int(date[0])
month = int(date[1])
day = int(date[2])

# 입력년도의 1월 1일의 요일 구하기(1년부터 이전 년도까지의 계산으로)
# 달력 출력에 일요일이 젤 처음이므로 일요일에 0값을 대입되게 한다
idx = 1 # 1년은 월요일 시작
for i in range(1, year):
    if is_leap_year(i):
        idx += 2
    else:
        idx += 1
# idx % 7은 입력 년도의 1월1일의 요일(0 == 일요일)

# 해당 년도가 윤년인지 확인하여 해당 년도의 2월달 일수 설정
if is_leap_year(year):
    month_day[1] = 29
else:
    month_day[1] = 28

# (idx + 올해의 입력 전월까지 일수) % 7 = 입력 달 1일의 요일(0 == 일요일)
# 1월 1일이 idx에 포함되어있기 때문에 입력 전달까지 일수를 더하면 입력달 1일이 된다.
for i in range(month - 1):
    idx += month_day[i]
    
# 달력 출력을 위해 앞의 빈칸을 포함한 전체 일 내용리스트
this_month = [' ' for blank in range(idx%7)] + [str(i + 1) for i in range(month_day[month-1])]

# 출력
print('Input yr_mn_dy_strings : ', date)
print('\n{} of Year {}'.format(month_idx[date[1]], date[0]))
print('='*28)   # ===...출력
# 요일 출력
for w in week:
    print(' {}'.format(w), end='')
print()
print('-'*28, end='')   # ---...출력(아래 일 출력 후 줄바꿈을 맞추기위해 여기에서 줄바꿈 안함)
for i in range(len(this_month)):
    if i % 7 == 0:  # 일요일 칸이면 줄바꿈
        print()
    print(' {:>3s}'.format(this_month[i]), end='')
print()
print('='*28)   # ===...출력
