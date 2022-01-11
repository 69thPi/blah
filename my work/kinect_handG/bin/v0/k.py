import cv2 as cv
import numpy as np
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Convolution2D, Conv2D, MaxPooling2D, Dense, Flatten, BatchNormalization
from tensorflow.keras.utils import to_categorical
from tensorflow.random import normal
from tensorflow.keras.optimizers import Adam

import matplotlib.pyplot as plt
import glob

folder=['five','four','three','two','one','zero','flat']

def changePath(root,val):
    path1=root+'/'+val+'/*.jpg'
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
                label.append(5)
            elif(i=='four'):
                label.append(4)
            elif(i=='three'):
                label.append(3)
            elif(i=='two'):
                label.append(2)
            elif(i=='one'):
                label.append(1)
            elif(i=='zero'):
                label.append(0)
            elif(i=='flat'):
                label.append(6)
    return file,label

train_file,train_label=get_img(typ='train')
test_file,test_label=get_img()


train_label=to_categorical(train_label,num_classes=7)
test_label=to_categorical(test_label,num_classes=7)

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


num_filters = 8
filter_size = 3
pool_size = 2

model = Sequential([
  Conv2D(num_filters, filter_size, input_shape=(480, 640, 1)),
  MaxPooling2D(pool_size=pool_size),
  Flatten(),
  Dense(units=7, activation='softmax'),
])

model.compile(optimizer='Adam', loss = 'categorical_crossentropy',metrics = ['accuracy'])
#model.fit(train_file,train_label,
#        epochs=13, 
#        validation_data=(test_file,test_label))
#print(model.evaluate(test_file,test_label))
#model.save_weights('cnn.h5')
