import matplotlib.pyplot as plt
import numpy as np

rang, inter=3 ,1

class LineBuilder:
    def __init__(self, line):
        self.line = line
        self.xs = list(line.get_xdata())
        self.ys = list(line.get_ydata())
        self.xs.append(0)
        self.ys.append(0)
        self.cid = line.figure.canvas.mpl_connect('button_press_event', self)

    def __call__(self, event):
        if event.inaxes!=self.line.axes: return
        self.xs[1]=event.xdata
        self.ys[1]=event.ydata
        x_res, y_res = self.xs,self.ys
        # do the req calcs

        #set them all and draw again
        self.line.set_data(self.xs, self.ys)
        self.line.figure.canvas.draw()
        
class LineFollower:
    def __init__(self, line):
        self.line = line
        self.xs = list(line.get_xdata())
        self.ys = list(line.get_ydata())
        self.xs.append(0)
        self.ys.append(0)
        self.cid = line.figure.canvas.mpl_connect('button_press_event', self)

    def __call__(self, event):
        if event.inaxes!=self.line.axes: return
        self.xs[1]=event.xdata
        self.ys[1]=event.ydata
        x_res, y_res = self.xs,self.ys
        # import the required coord

        #set them all and draw again
        self.line.set_data(self.xs, self.ys)
        self.line.figure.canvas.draw()

fig, ax = plt.subplots()
plt.axis([-rang,rang,-rang,rang])
plt.grid()

#empty lines
line, = ax.plot([0], [0])  
v1, = ax.plot([0.86], [0.5])
v2, = ax.plot([-0.86], [0.5])
v3, = ax.plot([0], [-.98])
#Net velocity vector line call
linebuilder = LineBuilder(line)
#Wheel vector line call
vector1 = LineFollower(v1)
vector2 = LineFollower(v2)
vector3 = LineFollower(v3)



#decoration
dots=[[0,.86,-.86,0],[0,.5,.5,-.98]]
shape=[[.14,.93,.78,-.78,-.93,-.14,.14],[-.98,.37,.62,.62,.37,-.98,-.98]]
plt.plot(shape[0],shape[1])
plt.plot(dots[0],dots[1],'ro')
plt.gca().set_aspect('equal',adjustable='box')#maintain aspect ratio
plt.show()
