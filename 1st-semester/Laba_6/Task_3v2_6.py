from tkinter import *
import time
import _thread


def rectangle_(event):
    _thread.start_new_thread(f1, ())


def f1():
    cnt = 3
    global oval1, oval2, oval3
    while cnt > 0:
        time.sleep(1)
        c.itemconfig(oval1, fill='red')
        time.sleep(1)
        c.itemconfig(oval1, fill='grey')
        cnt -= 1
    cnt = 3
    while cnt > 0:
        time.sleep(1)
        c.itemconfig(oval2, fill='orange')
        time.sleep(1)
        c.itemconfig(oval2, fill='grey')
        cnt -= 1
    cnt = 3
    while cnt > 0:
        time.sleep(1)
        c.itemconfig(oval3, fill='green')
        time.sleep(1)
        c.itemconfig(oval3, fill='grey')
        cnt -= 1
    _thread.exit()


root = Tk()
root.title("Traffic lights")

c = Canvas(width=200, height=420, bg='dark grey')
c.pack()

rectangle = c.create_rectangle(20, 25, 180, 410, fill='black')
oval1 = c.create_oval(50, 50, 150, 150, fill='grey', outline='#EF9A9A', width=3)
oval2 = c.create_oval(50, 170, 150, 270, fill='grey', outline='#FFCC00', width=3)
oval3 = c.create_oval(50, 290, 150, 390, fill='grey', outline='light green', width=3)

c.tag_bind(rectangle, '<Button-1>', rectangle_)
text = c.create_text(100, 10, font="Arial 10", text="Нажмите на светофор", fill='black')
root.mainloop()
