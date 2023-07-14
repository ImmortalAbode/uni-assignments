from tkinter import *

root = Tk()
c = Canvas(root, width=300, height=300)


def rectangle(event):
    c.create_rectangle((5, 10, 100, 250), fill="red")


def clean(event):
    c.delete('all')


c.bind("<Button-1>", rectangle)
c.bind("<Button-3>", clean)

c.pack()
root.mainloop()
