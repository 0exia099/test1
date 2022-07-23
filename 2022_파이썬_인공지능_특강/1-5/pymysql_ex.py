from tkinter import *
from tkinter.messagebox import showinfo
from tkinter import messagebox
import pymysql

def select():
    try:
        sql = "select * from student where sid = %s"
        val = (entry[0].get(),)
        mc.execute(sql,val)
        result = mc.fetchone()
        for x in range(1, num_field):
            entry[x].delete(0,END)
            entry[x].insert(0, result[x])
    except TypeError:
        messagebox.showerror("검색 오류", "존재하지 않는 레코드입니다.")
        reset()
    
def insert():
    sql = "insert into student values(%s,%s,%s,%s,%s,%s,%s,%s)"
    val = []
    for x in range(num_field):
        val.append(entry[x].get())
    mc.execute(sql,tuple(val))
    mydb.commit()
    showinfo("레코드 추가", f"{mc.rowcount}개의 레코드가 추가되었습니다.")
    return
    
def update():
    sql = "update student set addr=%s, grade=%s where sid=%s"
    val = (entry[5].get(), entry[7].get(), entry[0].get())
    mc.execute(sql,val)
    mydb.commit()
    showinfo("레코드 변경", f"{mc.rowcount}개의 레코드가 변경되었습니다.")
    return
    
def delete():
    sql = "delete from student where sid = %s"
    val = (entry[0].get(),)
    mc.execute(sql,val)
    mydb.commit()
    showinfo("레코드 삭제", f"{mc.rowcount}개의 레코드가 삭제되었습니다.")
    return
    
def reset():
    for x in range(num_field):
        entry[x].delete(0,END)
    entry[0].focus_set()

mydb = pymysql.connect(host='localhost', user='root', password='0exia099', database='StudentDB')
mc = mydb.cursor()

labels = ["학번", "이름","학과","지도교수","성별","주소","생일","학점"]
entry = []
label_font= ("Arial", 14, "bold")
window = Tk()
window.title("Student 테이블")
num_field = len(labels)
for x in range(num_field):
    Label(window, text=labels[x], font=label_font).grid(row=x, column=0)
    e1 = Entry(window, font=("Arial", 20, "bold"), fg="blue", width=25)
    e1.grid(row=x, column=1)
    entry.append(e1)
    
frame = Frame(window)
frame.grid(row=num_field, column=1)
Button(frame, text="검색",font=label_font,command=select).pack(side=LEFT)
Button(frame, text="추가",font=label_font,command=insert).pack(side=LEFT)
Button(frame, text="수정",font=label_font,command=update).pack(side=LEFT)
Button(frame, text="삭제",font=label_font,command=delete).pack(side=LEFT)
Button(frame, text="다시 입력",font=label_font,command=reset).pack(side=LEFT)

window.mainloop()