import cv2 as cv
import numpy as np
from tensorflow.keras.utils import to_categorical
from tensorflow.keras.optimizers import Adam
from pappi import model
import glob

folder=['five','four','flat','none','zero']

def changePath(root,subFol,dat='dataset2'):
    path=root+'/'+dat+'/'+subFol+'/*.jpg'
    return path

def get_img(typ='test'):
    file=[] #array of images
    label=[] #cooresponding labels
    for everyFile in folder:
        path=changePath(typ,everyFile)
        cnt=1
        for filepath in glob.iglob(path):
            read=cv.imread(filepath,cv.IMREAD_GRAYSCALE)
            read=(read/255) -.5 #median values
            file.append(read)
            if(everyFile=='five'):
                label.append(4)
            elif(everyFile=='four'):
                label.append(3)
            elif(everyFile=='none'):
                label.append(2)
            elif(everyFile=='flat'):
                label.append(1)
            elif(everyFile=='zero'):
                label.append(0)
    return file,label

fz=len(folder) #IMP:: the numeric labels shouldnt extend beyond this number

#Retrieve CNN training and testing datasets
train_file,train_label=get_img(typ='train')
test_file,test_label=get_img()

print(len(train_file))
# convert labels to full probability values([1.0 .0],[.0 1.0])
train_label=to_categorical(train_label,num_classes=fz)
test_label=to_categorical(test_label,num_classes=fz)
#convert to np.array and expand dimentions for input to CNN
#train_file= np.array(train_file) #skip this by directly convert dims
train_file= np.expand_dims(train_file,axis=3)
train_label= np.array(train_label)
test_file= np.expand_dims(test_file,axis=3)
test_label= np.array(test_label)

#verify (SampleCount,width,height,value)=(XX,370,315,1)
print("train")
print(train_file.shape)
print(train_label.shape)
print("test")
print(test_file.shape)
print(test_label.shape)
print('[...............................................]')


#to append model
model.load_weights('v1.h5')

#compile the model
model.compile(optimizer='Adam', loss = 'categorical_crossentropy',metrics = ['accuracy'])
#train the model
model.fit(train_file,train_label,
        epochs=20, 
        validation_data=(test_file,test_label))
#print accuracy of the model
print(model.evaluate(test_file,test_label))
#save model parameters aka optimal weights
model.save_weights('v3.h5')
