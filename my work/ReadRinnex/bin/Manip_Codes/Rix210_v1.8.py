from pathlib import Path
#import mod2

Nav_files = []  #to store the names of all the GPS Nav Messages in the dir

try:
    #locate the Nav Data Folder from the parent folder (one level up of CWD)
    Dat_fol = Path(Path.cwd().parent)/'GPS_Nav_Dat'
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
    with Path((Dat_fol)/Nav_files[0]).open('r') as dat_file:
        while True:
            if 'END OF HEADER' in dat_file.readline():
                break;
        #Reading frames (8 lines) till EOF
        lr=0 #line read count
        val = [] #store values in order
        while True:
            line = dat_file.readline()
            lr+=1  #one line read
            #for one frame read
            #if lr == 9:
            #        break
            if line != '':
                #group data framewise and then valuewise store to list
                if(lr%8==1): #line 1
                    val.append(line[3:19])  #t
                elif(lr%8==2): # line 2
                    val.append(line[23:41]) #CRS
                    val.append(line[42:60]) #DEL_n
                    val.append(line[61:79]) #Mo 
                elif(lr%8==3 or lr%8==4 or lr%8==5): #line 3 , 4 , 5
                    val.append(line[4:22])  #CUC    #Toe    #I_0
                    val.append(line[23:41]) #e      #CIC    #CRC
                    val.append(line[42:60]) #CUS    #OMEGA  #omega
                    val.append(line[61:79]) #rt_a   #CIS    #OMEGA_dot
                elif(lr%8==6): # line 6
                    val.append(line[4:22])  #i_dot
                elif(lr%8==7): #line 7
                    continue
                elif(lr%8==0): #line 8
                    #one frame read
                    #call calc_coord method and transfer list
                    for i in val:
                        print(i)
                    print(len(val))
                    coord = mod(val) #val paased as argv
                    #store coord as array of size 12 one array for each hour
                    #filter using Sig_Str and leave out one element
                    #combine all readngs list to get coord, with time in txt file
                    val = [] #empty array for next frame
            else:
                break
    dat_file.close()
