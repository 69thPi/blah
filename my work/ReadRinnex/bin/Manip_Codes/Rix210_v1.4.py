from pathlib import Path


Nav_files = []
try:
    #locate the Nav Data Files from the parent folder (one level up of CWD)
    Dat_fol = Path(Path.cwd().parent)/'GPS_Nav_Dat'
    cnt=0
    for n in Dat_fol.iterdir():
        Nav_files.append(Path(n).name)
    if len(Nav_files)==0:
        print("Nav Data Empty!")
    else:
        print("Nav Data Located!")
except:
    print("Oops! Nav Data not Located..")


for n in Dat_fol.iterdir():
        Nav_files.append(Path(n).name)

j=0
for i in Nav_files:
    j+=1
    print('file ',j,':',i)
