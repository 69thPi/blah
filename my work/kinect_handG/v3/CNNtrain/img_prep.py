import numpy as np
import cv2 as cv
import glob
from PIL import Image
import os

folder=['none']#['five','four','three','flat','two','one','zero']

def changePath(root,val):
    path1=root+'/'+val+'/*.jpg'
    return path1

cnt=1
def get_img(typ='test'):
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

def get_img2(typ='train'):
    for i in folder:
        path=changePath(typ,i)
        for filepath in glob.iglob(path):
            read=cv.imread(filepath,0)
            print(read.shape)
            if(read.shape[0]!=370 or read.shape[1]!=315):
                    os.remove(filepath)
def write_none():
    for i in range(15):
        crop=np.zeros((370,315))
        cv.imwrite('train/none/'+str(i)+'.jpg',crop)
        


