import cv2 as cv
import numpy as np

kernel_l = np.array([[1, 0, -1],
                   [2, 0, -2],
                   [1, 0, -1]])
kernel_out = np.array([[-1, -1, -1],
                   [-1, 8, -1],
                   [-1, -1, -1]])


def get_img():
    disp=cv.imread('1.jpg')
    dst = cv.filter2D(disp, -1, kernel_l)
    cv.imshow('abc', dst)
    cv.waitKey(0)
    cv.destroyAllWindows()

while(1):
    get_img()
