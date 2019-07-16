import numpy as np
from pathlib import Path
import cv2

allImgFiles = []
cwd = Path.cwd() #stores the nameof all the folder
           
try:
    for n in  cwd.iterdir():
        if str(Path(n).suffix) == '.jpg' or str(Path(n).suffix) == '.png' or str(Path(n).suffix) == '.gif':
            allImgFiles.append(Path(n).name)
    cnt=len(allImgFiles)
    if cnt == 0:
        print("No image file detected!")
    else:
        print(cnt, " image files detected.")
except:
    print("Path Problem.")

#number of files deleted
p,d=0,0

while (p < len(allImgFiles)):
    parent=cv2.imread(allImgFiles[p])
    print("comparing ",allImgFiles[p])
    c=p+1
    while(c<len(allImgFiles)):
        child=cv2.imread(allImgFiles[c])
        print(round(c/len(allImgFiles)*100,3),"%..")
        if parent.shape == child.shape:         #if shape exists
            b,g,r = cv2.split(cv2.subtract(parent,child))
            if cv2.countNonZero(b)==0 and cv2.countNonZero(g)==0 and cv2.countNonZero(r)==0:        #if same images then store child path
                print(allImgFiles[c],"deleted")
                Path(allImgFiles[c]).unlink()
                allImgFiles.remove(allImgFiles[c])
                d+=1
            else:
                c+=1
        else:
            c+=1
    p+=1

print(d, 'files deleted')


        
