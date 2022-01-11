import cv2 as cv
import numpy as np
import pyautogui as py
from pappi import model,get_feed,run_ID

# Load the model's saved weights.
model.load_weights('v1.h5')

del_x=del_y=x_old=y_old=0

def get_deltas(x,y):
    global del_x,del_y
    global x_old,y_old
    if(x!=x_old and y!=y_old):
            del_x=x-x_old
            del_y=y-y_old
            x_old=x
            y_old=y
    if(abs(del_x)<50 and abs(del_y)<50):
        if (abs(del_x)>15):
            del_x*=1
        if (abs(del_y)>15):
            del_x*=1
    else:
        del_x=del_y=0
    return del_x,del_y

saved=2
detect=False
cnt=0
while(True):
    frame = get_feed(200)
    x,y,count=run_ID(frame)
    print(count)
    if (saved!=count):
        saved=count
        detect=False
        cnt+=1
        if(cnt>2):
            cnt=0
            detect=True
    else:
        detect=False
    dx,dy=get_deltas(x,y)
    if (count==0):
            py.scroll(-.1*dy)
    else:
        py.move(-dx,dy)
        del_x=del_y=0
    if(detect):
        if (count==1):
            py.click(button='left')
            print('left click')
        elif (count==3):
            py.click(button='right')
            print('right click')
    frame=cv.resize(frame,(160,120),interpolation=cv.INTER_LINEAR)
    cv.imshow('frame',frame)
    k=cv.waitKey(1) & 0xff
    if k==27:
        break
cv.destroyAllWindows()

