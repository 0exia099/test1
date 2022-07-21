from tkinter import*
window =Tk()

# button = Button(window, text="클릭하세요!",bg="yellow", fg = "blue", width = 80, height=2)
#맥에서는 버튼 색은 안바뀐다.
#아래는 버튼 배경에 색줘서 비슷하게 보이게 하는것
button = Button(window, text="클릭하세요!",highlightbackground="yellow", fg = "blue", width = 80, height=2)
button.pack()
window.mainloop()
