from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Dense, Flatten
import freenect as kinect
import numpy as np
import cv2 as cv

#CNN model
model = Sequential([
  Conv2D(9, (3,3), input_shape=(370, 315, 1)),
  MaxPooling2D(pool_size=4),
  Conv2D(1, (3,3), activation='relu'),
  MaxPooling2D(pool_size=4),
  Flatten(),
  Dense(units=512, activation='relu'),
  Dense(units=128, activation='relu'),
  Dense(units=64, activation='relu'),
  Dense(units=5, activation='softmax'),
])

#get direct feed from kinect
def get_feed(Tr=180):
    feed,_ = kinect.sync_get_video(0,kinect.VIDEO_IR_10BIT)
    np.clip(feed, 0, 2**10-1,feed)
    feed >>=2
    mask0=feed.astype(np.uint8)
    mask1=np.where(mask0<Tr,0,mask0)   #minFilter
    mask1=np.where(mask1>Tr,255,mask1) #maxFilter
    mask2=cv.medianBlur(mask1,9)       #remove random noise
    mask2=cv.medianBlur(mask2,9)       #remove random noise
    return mask2

#get center of gesture made
def get_moments(inp_feed):
    moments=cv.moments(inp_feed)
    x = int(moments ["m10"] / moments["m00"])
    y = int(moments ["m01"] / moments["m00"])
    return x,y

#localise motion: eliminate delta due to gesture change
#conclusin: too stable, not enough DoF
def reduce_wobble(feed):
    feed=255-feed
    mask0=cv.blur(feed,(80,80))
    mask1=np.where(mask0<223,0,mask0)
    mask1=np.where(mask1>223,255,mask1)
    try:
        x,y=get_moments(mask1)
        return x,y
    except:
        return 0,0
#set streamsize for CNN  
def set_ML(inp_feed): #median and cropped
    try:
        x,y=get_moments(inp_feed)
        crop=inp_feed[y-200:y+170,x-135:x+180]
        crop= (crop/255) -.5
        if crop.shape[0]==370 and crop.shape[1]==315:
            return crop,x,y
        else:
            return np.zeros((370,315)),x,y
    except:
        return np.zeros((370,315)),0,0 #no data

#ID's the gesture made
def run_ID(surface):
    CNN_feed,x,y=set_ML(surface)
    lst=[]
    lst.append(CNN_feed)
    lst=np.expand_dims(lst, axis=3)
    predictions=model.predict(lst)
    guess=np.argmax(predictions,axis=1)
    return x,y,int(guess[0])

def gesture_mapping(guess):
    if (guess==4):
        print('five')
    elif (guess==3):
        print('four')
    elif (guess==2):
        print('none')
    elif (guess==1):
        print('flat')
    elif (guess==0):
        print('zero')
