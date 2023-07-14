from tkinter import *

c = Canvas(width=460, height=460, bg='grey80')
c.pack()

oval = c.create_oval(30, 10, 130, 80)
rect = c.create_rectangle(180, 10, 280, 80)
triangle = c.create_polygon(330, 80, 380, 10, 430, 80, fill='grey80', outline='black')

c.move(rect, 0, 150)
c.itemconfig(triangle, outline="red", width=3)
c.coords(oval, 300, 200, 450, 450)


def move(event):
    c.move(rect, 0, 2)


c.bind('<Button-1>', move)

oval = c.create_oval(30, 10, 130, 80, tag='group1')
c.create_line(10, 100, 450, 100, tag='group1')


def color(event):
    c.itemconfig('group1', fill="red", width=3)


c.bind('<Button-3>', color)


def clean(event):
    c.delete('all')


c.bind('<Button-2>', clean)
mainloop()
