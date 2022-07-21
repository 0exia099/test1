class Rocket:
    def __init__(self, x = 0, y = 0):
        self.__x = x
        self.__y = y
        
    def __str__(self):
        return f"로켓의 위치 = ({self.__x}, {self.__y})"
    
    def moveUp(self):
        self.__y += 1
        return
    
    def goto(self, x, y):
        self.__x = x
        self.__y = y
        
    def getX(self):
        return self.__x
    
    def getY(self):
        return self.__y
    
    def setX(self, x):
        self.__x = x
        return
    
    def setY(self, y):
        self.__y = y
        return
    
myRocket = Rocket()
print(myRocket)
myRocket.moveUp()
print(myRocket)
myRocket.goto(100,200)
print(myRocket)