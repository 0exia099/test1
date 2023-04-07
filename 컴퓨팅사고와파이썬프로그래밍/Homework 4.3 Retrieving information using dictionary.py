"""
 Project : Homework 4.3 Retrieving information using dictionary
 Author : 심상혁
 St_ID : 21812076
 Major : 컴퓨터공학과
 Date of first create : March 22, 2023
 Major features:
   -10개 국가에 대하여 문자열 자료형의 국가 이름과 수도를 입력받아 이름을 key, 수도를 value로 딕셔너리 구성
   -딕셔너리에 항목 추가 시 중복여부 기능 포함
   -딕셔너리 구성 후 국가 이름을 입력받아 해당 국가의 수도를 출력
 Date of last update : March 22, 2023
 Revised contesnt : 
   -v1.0 : March 22, 2023
        * first create
"""

dict_nation_capital = {}
count = 0
# 10개의 국가 정보 입력받기
while count < 10: # 최대 10번
  input_nation_capital = input('Input nation and its capital (. to quit) : ')
  if input_nation_capital == '.': # '.'입력시 정보 입력 종료
    break
  else:
    nation, capital = input_nation_capital.split()
    if dict_nation_capital.get(nation, 0) != 0: # 이미 존재하는 정보일경우 알림
      print('This nation and its capital already exist in the dictionary')
    else:
      dict_nation_capital[nation] = capital
      count += 1
# 구성된 딕셔너리 출력
print('dict_nation_capital :  {}'.format(dict_nation_capital))
    
# 국가 이름을 입력받아 수도 출력
while True:
  input_nation = input('Input nation to find its capital (. to quit) : ')
  if input_nation == '.':
    break
  else:
    dic_capital = dict_nation_capital.get(input_nation, 0)
    if dic_capital == 0:
      print('{} does not exist in the dictionary'.format(input_nation))
    else:
      print('The capital of {} is {}'.format(input_nation, dic_capital))