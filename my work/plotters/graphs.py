'''
name :plots vs pressure gradient
date : 24/8/19
time : 8:30PM
author : tanmay
'''

import matplotlib.pyplot as plt

press = []
p_rat = []
vel = []
temp = []
rho =[]
mach =[]
area =[]

'''
P1= float(input('chamber pressure:'))
T1= float(input('chamber temperature:'))
P0= float(input('Ambient pressure:'))
inc = float(input('increment:'))
gam = float(input('gamma:'))
R= float(input('R:'))
m_dot = float(input('mass flow rate:'))

'''

P1= 2.068
T1= 2222.0
P0= .101325
inc = .01
gam = 1.3
R= 345.7
m_dot = 1.0

tmp = P1

while True:
    
    press.append(round(tmp,5))
    p_rat.append(round(tmp/P1,2))
    tmp-=inc
    if tmp<P0:
        break

for i in range(2,len(p_rat)):
    box1 = pow(p_rat[i],(gam-1)/gam)
    box2 = 2 * gam * R * T1 * (1/(gam-1)) * (1-box1)
    v=pow(box2,0.5)
    t=T1*box1
    r=(press[i]*1000000)/(R*t)
    box3= pow(R*gam*t,0.5) #local speed of sound
    m = v/box3
    a = m_dot / (r*v) *1000
    vel.append(round(v,2))
    temp.append(round(t,2))
    rho.append(round(r,2))
    mach.append(round(m,2))
    area.append(round(a,2))

p_rat.pop(0)
p_rat.pop(1)

plt.figure(figsize=(20,20)) #oversize 20 in
plt.subplots_adjust(left=0.07,right=0.97,wspace=0.3)

plt.subplot(231)
plt.plot(p_rat,vel,label='vel')
plt.xlabel('Py/P1')
plt.ylabel('Vel (m/s)')
plt.gca().invert_xaxis()

plt.subplot(232)
plt.plot(p_rat,temp,label='temp')
plt.xlabel('Py/P1')
plt.ylabel('Temp (K)')
plt.gca().invert_xaxis()

plt.subplot(233)
plt.plot(p_rat,rho,label='rho')
plt.xlabel('Py/P1')
plt.ylabel('Rho (kg/m3)')
plt.gca().invert_xaxis()

plt.subplot(234)
plt.plot(p_rat,mach,label='mach')
plt.gca().invert_xaxis()
plt.xlabel('Py/P1')
plt.ylabel('Mach')

plt.subplot(2,3,5)
plt.plot(p_rat,area,label='area')
plt.gca().invert_xaxis()
plt.xlabel('Py/P1')
plt.ylabel('Area (cm2)')

plt.show()

print('---inlet ---')
print('Temp=',temp[0])
print('Mach=',mach[0])
print('Rho=',rho[0])
print('Area=',area[0])

print('----exit----')
print('Temp=',temp[-1])
print('Mach=',mach[-1])
print('Rho=',rho[-1])
print('Area=',area[-1])




