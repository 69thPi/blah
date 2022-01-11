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
    if(abs(del_x)<50 and abs(del_y)<50):
        if (abs(del_x)>15):
            del_x*=1
        if (abs(del_y)>15):
            del_x*=1
    else:
        del_x=del_y=0
    return del_x,del_y

def fngr(frame):
    _,contours, _ig = cv.findContours(frame, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    if (len(contours)>0):
        contours=max(contours, key=lambda x: cv.contourArea(x))
        hull = cv.convexHull(contours, returnPoints=False)
        if len(hull) > 3:
            defects = cv.convexityDefects(contours, hull)
            cnt = 0
            if type(defects) != type(None):
                for i in range(defects.shape[0]):
                    s, e, f, d = defects[i, 0]
                    start = tuple(contours[s, 0])
                    end = tuple(contours[e, 0])
                    far = tuple(contours[f, 0])
                    angle = calculateAngle(far, start, end)
                    if angle <= np.pi/2:
                        cnt += 1
            #return True, cnt
        return False, 0
    
def calculateAngle(far, start, end):
    a = np.sqrt((end[0] - start[0])**2 + (end[1] - start[1])**2)
    b = np.sqrt((far[0] - start[0])**2 + (far[1] - start[1])**2)
    c = np.sqrt((end[0] - far[0])**2 + (end[1] - far[1])**2)
    angle = np.arccos((b**2 + c**2 - a**2) / (2*b*c))
    return angle

set_params_min()

while(True):
    frame = get_feed(200)       
    finger_count=fngr(frame)
    #print(finger_count)
    if(finger_count!=0):
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


'''
https://medium.com/analytics-vidhya/hand-detection-and-finger-counting-using-opencv-python-5b594704eb08

https://becominghuman.ai/real-time-finger-detection-1e18fea0d1d4

https://www.pyimagesearch.com/2018/07/23/simple-object-tracking-with-opencv/

'''

    
