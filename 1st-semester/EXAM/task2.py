from tkinter import *

root = Tk()

counter = IntVar()
counter.set(0)


def click_up():
    counter.set(counter.get() + 1)


frame = Frame(root)
frame.pack()

button = Button(frame, text='Увеличить значение', command=click_up)
button.pack()

label = Label(frame, textvariable=counter)
label.pack()

root.mainloop()
