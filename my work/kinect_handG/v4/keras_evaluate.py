import cv2 as cv
from pappi import model, get_feed,set_ML, run_ID,gesture_mapping

# Load the model's saved weights.
model.load_weights('v3.h5')

while(True):
    frame = get_feed(200)
    display,_,__=set_ML(frame) #only for vision
    cv.imshow('vision',display) #totally un-necessary
    _ig,_na_,guess=run_ID(frame)
    gesture_mapping(guess)
    k=cv.waitKey(1) & 0xff
    if k==27:
        break
cv.destroyAllWindows()


