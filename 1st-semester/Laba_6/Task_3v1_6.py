from tkinter import *


class TrafficLights:
    def __init__(self):
        root = Tk()
        root.title("Traffic lights")

        self.c = Canvas(width=200, height=400, bg='dark grey')
        self.c.pack()

        self.var = IntVar()
        self.var.set(0)
        rad_red = Radiobutton(root, text='Зажечь красный', variable=self.var, value=0, command=self.blink)
        rad_red.pack()
        rad_orange = Radiobutton(root, text='Зажечь оранжевый', variable=self.var, value=1, command=self.blink)
        rad_orange.pack()
        rad_green = Radiobutton(root, text='Зажечь зелёный', variable=self.var, value=2, command=self.blink)
        rad_green.pack()

        self.c.create_rectangle(20, 10, 180, 390, fill='black')
        self.oval1 = self.c.create_oval(50, 30, 150, 130, fill='red', outline='#EF9A9A', width=3)
        self.oval2 = self.c.create_oval(50, 150, 150, 250, fill='grey', outline='#FFCC00', width=3)
        self.oval3 = self.c.create_oval(50, 270, 150, 370, fill='grey', outline='light green', width=3)

        root.mainloop()

    def blink(self):
        var = self.var.get()
        if var == 0:
            self.c.itemconfig(self.oval1, fill='red')
            self.c.itemconfig(self.oval2, fill='grey')
            self.c.itemconfig(self.oval3, fill='grey')
        elif var == 1:
            self.c.itemconfig(self.oval1, fill='grey')
            self.c.itemconfig(self.oval2, fill='orange')
            self.c.itemconfig(self.oval3, fill='grey')
        elif var == 2:
            self.c.itemconfig(self.oval1, fill='grey')
            self.c.itemconfig(self.oval2, fill='grey')
            self.c.itemconfig(self.oval3, fill='green')


TrafficLights()
