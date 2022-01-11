import cv2 as cv
from pappi import get_feed

root='test'
subFol='/dataset2/'

c=0
while(True):
    frame = get_feed(200)       
    cv.imshow('frame',frame)
    k=cv.waitKey(1) & 0xff
    if k==27:
            break
    if k==ord('0'):
        cv.imwrite(root+subFol+"zero/%d.jpg"%c,frame)
        c+=1
    if k==ord('4'):
        cv.imwrite(root+subFol+"four/%d.jpg"%c,frame)
        c+=1
    if k==ord('5'):
        cv.imwrite(root+subFol+"five/%d.jpg"%c,frame)
        c+=1
    if k==ord('f'):
        cv.imwrite(root+subFol+"flat/%d.jpg"%c,frame)
        c+=1
cv.destroyAllWindows()

    
#to add 'none' samples==> see img_prep.y
