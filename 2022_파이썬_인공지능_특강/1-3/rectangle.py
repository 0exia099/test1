class Rectangle:
    def __init__(self,x,y,w,h):
        self.x = x
        self.y = y
        self.w = w
        self.h = h
        
    def __str__(self):
        return f"좌측 하단: ({self.x}, {self.y}), 너비와 높이: {self.w}*{self.h}"
    
    def __gt__(self, other):
        return self.w*self.h>other.w*other.h
    
    def overlap(self, other):
        if self.x >= other.x +other.w or other.x>=self.x+self.w:
            return False
        if self.y >= other.y+other.h or other.y >=self.y +self.h:
            return False
        return True

r1 = Rectangle(0,0,10,10)
r2 = Rectangle(5,5,10,5)
print(r1)
print(r2)
print("r1 >r2:", r1>r2)
print("r1와 r2 겹침:", r1.overlap(r2))