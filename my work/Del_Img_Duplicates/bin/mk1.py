import numpy as np
from pathlib import Path
import cv2


#store all files in lcation
#keep one parent file open and check with the remaining in the path
#if other copy exists delete child.
#keep on doing this ill parent is the last elment in the list

allImgFiles = []
cwd = Path.cwd() #stores the nameof all the folder
try:
    for n in  cwd.iterdir():
        if str(Path(n).suffix) == '.jpg' or str(Path(n).suffix) == '.png' or str(Path(n).suffix) == '.gif':
            allImgFiles.append(Path(n).name)
    if len(allImgFiles)==0:
        print("No image file detected!")
    else:
        print(str(len(allImgFiles))+ " image files detected.")
except:
    print("Path Problem.")

#print the image file names
#for i in allImgFiles:
#    print(i)

#do the compare function:
#count of all teh files
cnt= len(allImgFiles)
#parent loop

for p in range(0,cnt):
    parent = cv2.imread(allImgFiles[p])
    for c in range(p+1,cnt):
        child = cv2.imread(allImgFiles[c])
        #compare images if sizes are same
        if parent.shape == child.shape:
            diff=cv2.subtract(parent,child)
            b,g,r = cv2.split(diff)
        #if same images then delete the child
        if cv2.countNonZero(b)==0 and cv2.countNonZer(g)==0 and cv2.countNonZero(r)==0:
            fileDel=child
        print(Path(cwd.parent/fileDel), " deleted!")
        Path(cwd.parent/fileDel).unlink()
        
