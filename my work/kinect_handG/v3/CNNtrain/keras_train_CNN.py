import cv2 as cv
import numpy as np
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Dense, Flatten
from tensorflow.keras.utils import to_categorical
from tensorflow.random import normal
from tensorflow.keras.optimizers import Adam
from pappi import model

import matplotlib.pyplot as plt
import glob

folder=['five','four','flat','none','zero']

def changePath(root,val):
    path1=root+'/dataset1/'+val+'/*.jpg'
    print(path1)
    return path1

def get_img(typ='test'):
    file=[]
    label=[]
    for i in folder:
        path=changePath(typ,i)
        cnt=1
        for filepath in glob.iglob(path):
            read=cv.imread(filepath,cv.IMREAD_GRAYSCALE)
            read=(read/255) -.5
            file.append(read)
            if(i=='five'):
                label.append(4)
            elif(i=='four'):
                label.append(3)
            elif(i=='none'):
                label.append(2)
            elif(i=='flat'):
                label.append(1)
            elif(i=='zero'):
                label.append(0)
    return file,label

train_file,train_label=get_img(typ='train')
test_file,test_label=get_img()

fz=len(folder)

train_label=to_categorical(train_label,num_classes=fz)
test_label=to_categorical(test_label,num_classes=fz)

#train_file= np.array(train_file) #skip this by directly convert dims
train_file= np.expand_dims(train_file,axis=3)
train_label= np.array(train_label)
test_file= np.expand_dims(test_file,axis=3)
test_label= np.array(test_label)

print("train")
print(train_file.shape)
print(train_label.shape)
print("test")
print(test_file.shape)
print(test_label.shape)

model.compile(optimizer='Adam', loss = 'categorical_crossentropy',metrics = ['accuracy'])
model.fit(train_file,train_label,
        epochs=11, 
        validation_data=(test_file,test_label))
print(model.evaluate(test_file,test_label))
model.save_weights('v3.h5')
