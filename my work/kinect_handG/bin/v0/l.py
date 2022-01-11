import cv2 as cv
import numpy as np
import freenect as kinect
import pyautogui as py
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Dense, Flatten

num_filters = 8
filter_size = 3
pool_size = 2

# Build the model.
model = Sequential([
  Conv2D(num_filters, filter_size, input_shape=(480, 640, 1)),
  MaxPooling2D(pool_size=pool_size),
  Flatten(),
  Dense(7, activation='softmax'),
])

# Load the model's saved weights.
model.load_weights('cnn.h5')


def get_feed(Tr=180):
    video,_ = kinect.sync_get_video(0,kinect.VIDEO_IR_10BIT)
    np.clip(video, 0, 2**10-1,video)
    video >>=2
    video=video.astype(np.uint8)
    mask1=np.where(video<Tr,0,video) #minFilter
    mask1=np.where(mask1>Tr,255,mask1) #maxFilter
    mask2=cv.medianBlur(mask1,9)
    mask2=cv.medianBlur(mask2,9)
    mask2= (mask2/255) -.5
    return mask2

while(True):
    frame = get_feed(200)
    cv.imshow('vision',frame)
    lst=[]
    lst.append(frame)
    lst=np.expand_dims(lst,axis=3)
    predictions=model.predict(lst)
    guess=np.argmax(predictions,axis=1)
    print((str(guess[0])))

    k=cv.waitKey(1) & 0xff
    if k==27:
        break
cv.destroyAllWindows()


