class Student:
    def __init__(self, id, name, grade) -> None:
        self.__id =id
        self.__name = name
        self.__grade = grade
        
    def __repr__(self):
        return f"({self.__id}, {self.__name}, {self.__grade})"

    def getId(self):
        return self.__id
    
    def getName(self):
        return self.__name
    
    def getGrade(self):
        return self.__grade    
        

        
s1 = Student(20152041, "kim", 3.7)
s2 = Student(20171132, "ahn", 3.2)
s3 = Student(20191234, "cho", 3.3)

li = [s1, s2, s3]

print(sorted(li,key=lambda x:x.getId()))
print(sorted(li, key=lambda x:x.getName()))
print(sorted(li, key=lambda x:x.getGrade(), reverse=True))