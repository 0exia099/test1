class Vector2D:
    def __init__(self, a, b):
        self.__a = a
        self.__b = b
        
    def __str__(self):
        return f"({self.__a}, {self.__b})"
    
    def __repr__(self):#리스트 출력
        return f"({self.__a}, {self.__b})"
        
    def __add__(self, y):
        sum = Vector2D(self.__a+y.__a, self.__b+y.__b)
        return sum
    
    def __sub__(self, y):
        sub = Vector2D(self.__a-y.__a, self.__b-y.__b)
        return sub
    
    def __gt__(self, y):
        return self.__a**2+self.__b**2 > y.__a**2+y.__b**2
    
    def __eq__(self, y):
        return self.__a == y.__a and self.__b == y.__b
    
u = Vector2D(0,1)
v = Vector2D(1,0)
print(u+v)
print(u-v)
a = u+v
c = u-v
d = a-c
A = [c,d,u,v,a]
B = A
print(A)
print(sorted(A))
print(A==B)