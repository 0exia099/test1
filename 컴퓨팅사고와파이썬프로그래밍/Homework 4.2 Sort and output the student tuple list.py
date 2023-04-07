"""
 Project : Homework 4.2 Sort and output the student tuple list
 Author : 심상혁
 St_ID : 21812076
 Major : 컴퓨터공학과
 Date of first create : March 22, 2023
 Major features:
   -학생 정보를 가지는 튜플 리스트 생성
   -튜플을 오름차순(별도 기준 설정 없이) 출력, 학생 튜플을 학점 기준으로 역순 정렬 출력
 Date of last update : March 22, 2023
 Revised contesnt : 
   -v1.0 : March 22, 2023
        * first create
"""

# 학생 튜플 리스트 생성
students = [
('Kim, S.C.', 12001234, 'CE', 4.10),\
('Choi, Y.B.', 19003234, 'EE', 3.78),\
('Hong, C.H', 21001547, 'ICE', 4.13),\
('Yoon, J.H.', 17002571, 'ME', 3.55),\
('Lee, S.H.', 20003257, 'ICE', 4.45),\
('Kim, H.Y.', 19001234, 'CE', 4.17),\
('Lee, J.K', 18003234, 'EE', 3.78),\
('Park, S.Y.', 21001643, 'ICE', 4.13),\
('Jang, S.H.', 19002567, 'ME', 3.35),\
('Yeo, C.S', 20005243, 'CE', 4.45)]
# 학생 튜플 리스트 출력
for i in range(len(students)):
  (name, st_id, major, GPA) = students[i]
  print('students[{:2}] : name({:<8s}), st_id({:8d}), major({:<3s}), GPA({:5.2f})'\
    .format(i, name, st_id, major, GPA))

# 정렬 기준 설정 없이 오름차순 정렬 후 출력
sorted_students = sorted(students)
print('\nAfter sorting in increasing order :')
for i in range(len(sorted_students)):
  (name, st_id, major, GPA) = sorted_students[i]
  print('students[{:2}] : name({:<8s}), st_id({:8d}), major({:<3s}), GPA({:5.2f})'\
    .format(i, name, st_id, major, GPA))

# 학점 기준으로 역순으로 정렬하여 출력
sorted_students_GPA = sorted(students, key=lambda student: student[3], reverse=True)
print('\nAfter sorting according to GPA in decreasing order :')
for i in range(len(sorted_students_GPA)):
  (name, st_id, major, GPA) = sorted_students_GPA[i]
  print('students[{:2}] : name({:<8s}), st_id({:8d}), major({:<3s}), GPA({:5.2f})'\
    .format(i, name, st_id, major, GPA))