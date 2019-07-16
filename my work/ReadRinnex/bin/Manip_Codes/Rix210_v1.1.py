import os
from pathlib import Path

#locate the Nav Data Files
par_folder = Path.cwd().parent
Dat_fol = Path(par_folder)/'GPS_Nav_Dat'
print(Dat_fol)
cnt=0
for n in Dat_fol.iterdir():
    print(Path(n).name)
    cnt=cnt+1
print("number of files = ",cnt)
