class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        
    def __str__(self):
        return f"({self.x}, {self.y})"
    
class Point3D(Point):
    def __init__(self, x, y, z):
        super().__init__(x,y)
        self.z = z
        
    def __str__(self):
        return f"({self.x}, {self.y}, {self.z})"
    
p1 = Point(20, 30)
print(p1)
p2 = Point3D(20,30,40)
print(p2)