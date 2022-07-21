import math
class Circle:
    def __init__(self, radius=10):
        self.radius = radius
    
    def getArea(self):
        return self.radius**2*math.pi
    
    def getPerimeter(self):
        return self.radius*2*math.pi
    
circle = Circle(10)
print(f"원의 면적 {circle.getArea()}")
print(f"원의 둘레 {circle.getPerimeter()}")

class Car:
    def __init__(self, speed, color, model):
        self.speed = speed
        self.color = color
        self.model = model
        
    def drive(self):
        self.speed = 60
        
myCar = Car(0, "blue", "E-class")

print("자동차 객체를 생성하였습니다.")
print("자동차의 속도는", myCar.speed)
print("자동차의 색상은", myCar.color)
print("자동차의 모델는", myCar.model)
myCar.drive()
print("자동차의 속도는", myCar.speed)

class Student:
    def __init__(self, name=None, age = 0):
        self.__name = name #__가 붙은 변수는 private
        self.__age =age
        
    def getAge(self):   #getter
        return self.__age
    
    def getName(self):
        return self.__name
    
    def setAge(self, age):   #setter
        self.__age = age
        
    def setName(self, name):
        self.__name = name
        
obj=Student("Hong", 20)
print(obj.getName())


class BankAccount:
    def __init__(self):
        self.__balance = 0
    
    def withdraw(self, ammount):
        if self.__balance<ammount:
            print("잔액이 부족합니다.")
            return
        else:
            self.__balance -= ammount
            print(f"통장에서 {ammount}가 출금 되었습니다.")
            return
        
    def deposit(self, ammount):
        self.__balance += ammount
        print(f"통장에 {ammount}가 입급되었습니다.")
        return
    
    def report(self):
        print(f"통장의 잔액은 {self.__balance}입니다.")
        return
    
    def getBalance(self):
        return self.__balance
    
    def setBalance(self, ammount):
        self.__balance = ammount
        return
    
    def __str__(self):   #해당 인스턴스를 출력할때 사용되는 메소드
        return f"잔고 = {self.__balance}" #문자열 리턴
    
account = BankAccount()
account.deposit(100)
account.withdraw(70)
account.report()
print(account)