import random
from tkinter import*

window = Tk()
window.title("dice")
window.geometry("300x300")
def dice():
    label["text"] = str(random.randint(1,6))

label = Label(window, text="1", fg="red", font=("Arial", 100, "bold"))
label.pack(side=LEFT, padx=75)
button = Button(window, text="굴리기", fg="blue", font=("Arial", 20, "bold"), height=2, width=30, command=dice)
button.pack(side=RIGHT)

window.mainloop()