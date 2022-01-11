import numpy as np
import cv2 as cv
import glob
from PIL import Image
import os

root='test'
subFol='/dataset2/'
folder=['five','four','flat','none','zero']

def changePath(root,val):
    path1=root+subFol+val+'/*.jpg'
    return path1

cnt=1
def resize(typ='test'):
    global cnt
    for i in folder:
        path=changePath(typ,i)
        for filepath in glob.iglob(path):
            read=cv.imread(filepath,0)
            moments = cv.moments(read)
            x = int(moments ["m10"] / moments["m00"])
            y = int(moments ["m01"] / moments["m00"])
            try:
                crop=read[y-200:y+170,x-135:x+180]
                im=Image.fromarray(crop)
                im.save(path[:-5]+str(cnt)+'.jpg','JPEG',quality=90)
                cnt+=1
            except:
                pass

def del_NA(typ='test'):
    for i in folder:
        path=changePath(typ,i)
        for filepath in glob.iglob(path):
            read=cv.imread(filepath,0)
            print(read.shape)
            if(read.shape[0]!=370 or read.shape[1]!=315):
                    os.remove(filepath)

def prepData():
    resize()
    del_NA()
    resize(root)
    del_NA(root)

def write_none():
    for i in range(5):
        blank=np.zeros((370,315))
        cv.imwrite(root+subFol+'none/'+str(i)+'.jpg',blank)
        
### 2 options
        #prepdata()
        #write_none()
write_none()
