import cv2 as cv
import numpy as np
import freenect as kinect
import pyautogui as py
from types import *


params = cv.SimpleBlobDetector_Params()


def set_params_min():
    params.filterByArea=False
    params.filterByCircularity=True
    params.filterByConvexity=True
    params.filterByInertia=True
    params.minCircularity=.3
    params.minConvexity=.1
    params.minInertiaRatio=.1

def get_points(frame):
    frame=255-frame
    detector= cv.SimpleBlobDetector_create(params)
    mask2=cv.blur(frame,(80,80))
    mask3=np.where(mask2<223,0,mask2) #minFilter
    mask3=np.where(mask3>223,255,mask3) #maxFilter
    keypoints= detector.detect(mask3)
    return keypoints,mask3

def get_feed(Tr=180):
    video,_ = kinect.sync_get_video(0,kinect.VIDEO_IR_10BIT)
    np.clip(video, 0, 2**10-1,video)
    video >>=2
    video=video.astype(np.uint8)
    mask1=np.where(video<Tr,0,video) #minFilter
    mask1=np.where(mask1>Tr,255,mask1) #maxFilter
    #mask1=255-mask1 #invert colors
    mask2=cv.medianBlur(mask1,9)
    mask2=cv.medianBlur(mask2,9)
    return mask2

del_x=del_y=x_old=y_old=0

def get_deltas(dots):
    global del_x,del_y
    global x_old,y_old
    if(len(dots)>0):
        coord=np.split(points[0],2)
        x=int(coord[0][0].item())
        y=int(coord[1][0].item())
        if(x!=x_old and y!=y_old):
                del_x=x-x_old
                del_y=y-y_old
                x_old=x
                y_old=y
    if(abs(del_x)>50 or abs(del_y)>50):
        del_x=del_y=0
    return del_x,del_y

set_params_min()

while(True):
    frame = get_feed(180)
    keypoints, _ig_=get_points(frame)
    points=cv.KeyPoint_convert(keypoints) #returns x,y local pixels top right origin
    dx,dy=get_deltas(points)
    py.move(-dx,dy)
    del_x=del_y=0
    im_with_keypoints = cv.drawKeypoints(frame, keypoints, np.array([]), (0,0,255,-1), cv.DRAW_MATCHES_FLAGS_DEFAULT)
    cv.imshow('frame',im_with_keypoints)
    k=cv.waitKey(1) & 0xff
    if k==27:
       break
cv.destroyAllWindows()
    
