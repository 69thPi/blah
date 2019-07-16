from pathlib import Path

Nav_files = []
try:
    #locate the Nav Data Files from the parent folder (one level up of CWD)
    Dat_fol = Path(Path.cwd().parent)/'GPS_Nav_Dat'
    cnt=0
    for n in Dat_fol.iterdir():
        if Path(n).name.endswith('N'):
            Nav_files.append(Path(n).name)
    if len(Nav_files)==0:
        print("Nav Data Empty!")
    else:
        print("Nav Data Located!")
except:
    print("Oops! Nav Data not Located..")
end=len(Nav_files)
for cnt in range(0,end):
    with Path((Dat_fol)/Nav_files[cnt]).open() as dat_file:
        #print(dat_file.read())
        print(Nav_files[cnt], 'read\n')
        dat_file.close()
        cnt+=1

        

