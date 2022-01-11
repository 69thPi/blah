import cv2 as cv
import numpy as np
from pappi import model, get_feed,set_ML, run_ID

# Load the model's saved weights.
model.load_weights('v1.h5')

while(True):
    frame = get_feed(200)
    display,_,__=set_ML(frame) #only for vision
    cv.imshow('vision',display) #totally un-necessary
    _ig,_na_,guess=run_ID(frame)
    print(guess)
    k=cv.waitKey(1) & 0xff
    if k==27:
        break
cv.destroyAllWindows()


