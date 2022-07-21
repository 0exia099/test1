class Animal:
    def __init__(self, age):
        self.age = age
        
class Cat(Animal):
    def __init__(self, name, age, breed):
        super().__init__(age)
        self.name = name
        self.breed = breed
        
    def __str__(self):
        return f"이름={self.name}, 나이={self.age}, 종={self.breed}"
    
    def __gt__(self, other):
        return self.age > other.age
    
def get_oldest_cat(*args):
    return max(args)

c1 = Cat("야옹이", 4, "페르시안")
c2 = Cat("나비", 2, "아비시니안")
c3 = Cat("프린세스", 5, "러시안블루")
print("가장 나이 많은 고양이:", get_oldest_cat(c1,c2,c3))

for item in sorted([c1,c2,c3]):
    print(item)