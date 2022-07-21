class Course:
    def __init__(self, name, degree):
        self.name= name
        self.degree = degree
        
    def __repr__(self):
        return f"({self.name}, {self.degree})"

class Department:
    def __init__(self, name):
        self.name = name
        self.courses = []
        
    def __str__(self):
        return f"학과이름={self.name}, 개설과목={self.courses}"
    
    def add_course(self, cname, degree):
        co = Course(cname, degree)
        self.courses.append(co)
        return co
    
class Student:
    def __init__(self, name, num):
        self.name = name
        self.num = num
        self.courses = []
        
    def __str__(self):
        return f"학과이름={self.name}, 학번={self.num}, 수강과목={self.courses}"
    
    def enroll(self, course):
        self.courses.append(course)
        return course
        
dept = Department("컴퓨터공학과")
c1 = dept.add_course("대학생활의설계", 1)
c2 = dept.add_course("인공지능", 3)
c3 = dept.add_course("파이썬프로그래밍", 3)
print(dept)

st = Student("홍길동", 2020001)
st.enroll(c2)
st.enroll(c3)
print(st)