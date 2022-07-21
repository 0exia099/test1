
from tkinter import *

# 이벤트 처리 함수를 정의한다. 
def process1():
    tf = float(e1.get())		# e1에서 문자열을 읽어서 부동소수점형으로 변경
    tc = (tf-32.0)*5.0/9.0		# 화씨 온도를 섭씨 온도로 변환한다. 
    e2.delete(0, END)			# 처음부터 끝까지 지운다.
    e2.insert(0, str(tc))		# tc 변수의 값을 문자열로 변환하여 추가한다.
    
def process2():
    tc = float(e2.get())		# e2에서 문자열을 읽어서 부동소수점형으로 변경
    tf = (tc*9.0)/5.0+32.0		# 섭씨 온도를 화씨 온도로 변환한다. 
    e1.delete(0, END)			# 처음부터 끝까지 지운다.
    e1.insert(0, str(tf))		# tc 변수의 값을 문자열로 변환하여 추가한다.
    
def reset_process():
    e1.delete(0,END)
    e2.delete(0,END)

window  = Tk()

Label(window , text="화씨").grid(row=0, column=0)
Label(window, text="섭씨").grid(row=1, column=0)

e1 = Entry(window)
e2 = Entry(window)
e1.grid(row=0, column=1)
e2.grid(row=1, column=1)

Button(window, text="화씨->섭씨", command=process1).grid(row=2, column=0, sticky=W+E)
Button(window, text="섭씨->화씨", command=process2).grid(row=2, column=1, sticky=W+E)

Button(window, text="Reset", command=reset_process).grid(row=3, column=0, columnspan=2, sticky=W+E)
window.mainloop()