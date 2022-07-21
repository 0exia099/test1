import turtle

class Shape:
    def __init__(self,x,y,color):
        self.t = turtle.Turtle()
        self.t.up()
        self.t.goto(x,y)
        self.t.down()
        self.t.color(color)
    
    def draw(self):
        pass
        
class Rectangle(Shape):
    def __init__(self, x, y, len, color):
        super().__init__(x,y,color)
        self.len = len
        
    def draw(self):
        for _ in range(4):
            self.t.forward(self.len)
            self.t.left(90)
            
class Circle(Shape):
    def __init__(self, x, y, radius, color):
        super().__init__(x, y, color)
        self.radius = radius
        
    def draw(self):
        self.t.circle(self.radius)
        
r1 = Rectangle(-50,-50, 200, "red")
r2 = Rectangle(160,120,150,"blue")
c1 = Circle(-120,-100,120,"green")
r1.draw()
r2.draw()
c1.draw()

turtle.mainloop()
turtle.bye()
        
    