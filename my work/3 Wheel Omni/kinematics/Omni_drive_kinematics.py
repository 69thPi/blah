import matplotlib.pyplot as plt
from numpy import power,sqrt

#edit this value to change the x,y limit
range_lim=3

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
        x_res, y_res = self.xs[1],self.ys[1]
        # convert to (v, theta)
        global v,sint,cost
        v=sqrt(power(x_res,2)+power(y_res,2))
        sint=y_res/v
        cost=x_res/v
        #set and draw again
        print('V_res=',v)
        self.line.set_label('v_res')
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
        # solve for weights
        # v1=v*(-.33*cost + .58*sint)
        # v2=v*(-.33*cost - .58*sint)
        # v3=v*(0.66*cost)
        # scale unit vector & set position offsets
        # vector 1= [v1*(-.5)+0.86,v1*(0.86)+.5]
        # vector 2= [v2*(-.5)-.86,v2*(-.866)+.5]
        # vector 3= [v3, -.98]
        
        if(self.xs[0]>0): #vector 1
            v1=v*(-.33*cost + .58*sint)
            self.xs[1]=(v1*-.5)+0.86
            self.ys[1]=(v1*0.86)+.5
            print('v1 = ',v1)
            self.line.set_label('vector 1')
        elif(self.xs[0]<0): #vector 2
            v2=v*(-.33*cost - .58*sint)
            self.xs[1]=(v2*-.5)-.86
            self.ys[1]=(v2*-.86)+.5
            print('v2 =',v2)
            self.line.set_label('vector 2')
        else:                  #vector 3
            v3=v*(0.66*cost)
            self.xs[1]=v3
            self.ys[1]=-.98
            print('v3 = ',v3)
            print('------------------------')
            self.line.set_label('vector 3')
            ax.legend()
        #re-set them all and draw again
        self.line.set_data(self.xs, self.ys)
        self.line.figure.canvas.draw()

fig, ax = plt.subplots()
plt.axis([-range_lim,range_lim,-range_lim,range_lim])
plt.grid()
plt.gca().set_aspect('equal',adjustable='box')#maintain aspect ratio

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
dots=[[0,.86,-.86,0],[0,.5,.5,-.98]] #wheel vector origin
shape=[[.14,.93,.78,-.78,-.93,-.14,.14],[-.98,.37,.62,.62,.37,-.98,-.98]] #bot outline
plt.axvline(x=0, color='#A9A9A9') #y axis
plt.axhline(y=0, color='#A9A9A9') #x aixs

plt.plot(shape[0],shape[1])
plt.plot(dots[0],dots[1],'ro')
plt.show()
