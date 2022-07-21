from tkinter import*
window = Tk()
window.title("data")

def process():
    print(f"이름={e1.get()}, 직업={e2.get()}, 나이={e2.get()}")

def re_input():
    e1.delete(0, END)
    e2.delete(0, END)
    e3.delete(0, END)
    e1.focus_set()

Label(window , text="이름", padx = 10).grid(row=0, column=0)
e1 = Entry(window)
e1.grid(row=0, column=1, columnspan=2)

Label(window , text="직업", padx=10).grid(row=1, column=0)
e2 = Entry(window)
e2.grid(row=1, column=1, columnspan=2)

Label(window , text="나이", padx=10).grid(row=2, column=0)
e3 = Entry(window)
e3.grid(row=2, column=1, columnspan=2)

Button(window, text="처리", command=process).grid(row=3, column=1, sticky=W+E)
Button(window, text="다시입력", command=re_input).grid(row=3, column=2, sticky=W+E)

window.mainloop()