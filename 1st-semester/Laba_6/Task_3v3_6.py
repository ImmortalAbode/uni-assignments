from tkinter import *


class Frame(Tk):

    # Создание светофора
    def __init__(self):
        super().__init__()
        self.var = 0
        self.title("Traffic lights")

        self.c = c = Canvas(width=150, height=400, bg='black')
        self.c.pack()

        self.oval_r = c.create_oval(25, 30, 125, 130, fill='grey', outline='#EF9A9A', width=3)
        self.oval_y = c.create_oval(25, 150, 125, 250, fill='grey', outline='#FFCC00', width=3)
        self.oval_g = c.create_oval(25, 270, 125, 370, fill='grey', outline='light green', width=3)

        self.after(1000, self.blink)

    # Мигание светофора
    def blink(self):
        if self.var == 0:
            self.var = 1
            self.c.itemconfig(self.oval_r, fill='red')
            self.c.itemconfig(self.oval_g, fill='grey')
            self.after(1000, self.blink)
        elif self.var == 1:
            self.var = 2
            self.c.itemconfig(self.oval_r, fill='grey')
            self.c.itemconfig(self.oval_y, fill='orange')
            self.after(1000, self.blink)
        elif self.var == 2:
            self.var = 3
            self.c.itemconfig(self.oval_y, fill='grey')
            self.c.itemconfig(self.oval_g, fill='green')
            self.after(1000, self.blink)
        else:
            self.var = 0
            self.after(1000, self.blink)


root = Frame()

root.mainloop()
