from tkinter import *


# Осуществление движения машины
def move():
    root.after(100, move)
    c.move(oval1, 5, 0)
    c.move(oval2, 5, 0)
    c.move(rectangle, 5, 0)
    c.move(polygon1, 5, 0)
    c.move(polygon2, 5, 0)
    x1, y1, x2, y2 = c.coords(rectangle)
    if x1 > root_width:
        c.itemconfig(text, state='normal')


root = Tk()
root.title('Short_video')
c = Canvas(width=800, height=375, bg='white')
c.pack()

root_width = 800

# Создание фона
c.create_rectangle(0, 0, 800, 150, fill='light blue')
c.create_rectangle(0, 150, 800, 200, fill='green')
c.create_rectangle(0, 200, 800, 350, fill='grey')
c.create_rectangle(0, 350, 800, 375, fill='green')

# Создание солнца
c.create_oval(600, 20, 650, 70, fill='yellow', outline='orange')
c.create_line(625, 70, 625, 110, fill='yellow')
c.create_line(650, 45, 700, 45, fill='yellow')
c.create_line(625, 0, 625, 20, fill='yellow')
c.create_line(550, 45, 600, 45, fill='yellow')
c.create_line(620, 50, 590, 80, fill='yellow')
c.create_line(635, 55, 660, 85, fill='yellow')
c.create_line(605, 30, 580, 0, fill='yellow')
c.create_line(640, 30, 660, 0, fill='yellow')

# Создание полос
c.create_rectangle(650, 260, 750, 290, fill='white')
c.create_rectangle(500, 260, 600, 290, fill='white')
c.create_rectangle(350, 260, 450, 290, fill='white')
c.create_rectangle(200, 260, 300, 290, fill='white')
c.create_rectangle(50, 260, 150, 290, fill='white')

# Создание машины
oval1 = c.create_oval(30, 290, 60, 320, fill='black', outline='dark grey')
oval2 = c.create_oval(120, 290, 150, 320, fill='black', outline='dark grey')
rectangle = c.create_rectangle(20, 260, 90, 290, fill='dark blue', outline='black')
polygon1 = c.create_polygon(90, 220, 110, 220, 160, 270, 160, 290, 90, 290, fill='dark blue', outline='black')
polygon2 = c.create_polygon(100, 230, 110, 230, 140, 260, 100, 260, fill='light blue', outline='grey')

text = c.create_text(300, 100, font="Arial 20", fill='black', text="Машина уехала, расходимся :)", state='hidden')
root.after(100, move)
root.mainloop()
