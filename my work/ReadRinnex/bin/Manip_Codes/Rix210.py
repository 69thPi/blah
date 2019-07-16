import os

#get current working directory
cwd = os.getcwd()
print(cwd,".. is the current directory")
try:
    os.chdir('..')
    os.chdir('.\\GPS_Nav_Dat')
    print("Data Dir found!")
    #change the directory
    # '..' to go up one step
    # '.\\subfolder' to go down from current folder
    # 'C:\\diff_folder\\Diff_Sub_folder' to change entire diectory
except:
    print("Resource directory not found!")

#prints all files in current directory  
from pathlib import Path

flist=[]
for i in Path().iterdir():
        print(i)
        flist.append(i)

# stores all the required files as a tuple
#   arr_txt = [x for x in os.listdir() if x.endswith('.17N')]
#   print(arr_txt, sep=' ')



