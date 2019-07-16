from pathlib import Path
from calc_xyz import gCtric

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

def filter_1(a):                #use:: convert "Double" precision scientific string values to float
    mag = float(a[1:-4])        #magnitude
    ex = int(a[-2:])            #exponential power
    if a[-3] == '+':
        mag *= pow(10,ex)
    elif a[-3] == '-':
        mag /= pow(10,ex)
    if a[0]=='-':               #negative value adjustment
        return mag * -1
    else:
        return mag

#folder to store new data
Fldr_Gc = Path(Dat_fol)/'GC'  #Folder::Geocentric coord

if Fldr_Gc.exists():
    print("path exists")
else:
    Fldr_Gc.mkdir()
    print("Path Created!")

end=1#len(Nav_files)
for cnt in range(0,end):
    tgt_nm = Nav_files[cnt][:-4]+'-gc.txt' #new target name ext = -gc.txt
    tgt = Path(Fldr_Gc)/tgt_nm
    print(tgt)
    target = open(str(tgt), 'w')
    main_header = "----------------------------------COORIDINATES-----------------------------------\n\tX\t\t\tY\t\t\tZ\t\t   t   \n"
    target.write(main_header)
    with Path((Dat_fol)/Nav_files[cnt]).open('r') as dat_file:
        while True:
            if 'END OF HEADER' in dat_file.readline():
                break;
        #Reading frames (8 lines) till EOF
        lr=0 #line read count
        val = [] #store values in order
        while True:
            line = dat_file.readline()
            lr+=1  #one line read
            #if lr == 27: #for <=8 ignores the condition
            #    break
            
            if line != '':
                #group data framewise and then valuewise store to list
                if(lr%8==1):                        #line 1
                    #yy = int(line[3:5])        #yy 
                    #month = int(line[6:8])     #mm
                    #dd = int(line[9:11])       #dd
                    #val.append([yy,month,dd])      ##to use date##
                    hh = int(line[12:14])       #hh
                    mm = int(line[15:17])       #mm
                    ss = float(line[18:22])     #ss 
                    val.append([hh,mm,ss])            #t
                elif(lr%8==2):                      # line 2
                    val.append(filter_1(line[23:41])) #CRS
                    val.append(filter_1(line[42:60])) #DEL_n
                    val.append(filter_1(line[61:79])) #Mo 
                elif(lr%8==3 or lr%8==4 or lr%8==5):#line 3 , 4 , 5
                    val.append(filter_1(line[4:22]))  #CUC    #Toe    #I_0
                    val.append(filter_1(line[23:41])) #e      #CIC    #CRC
                    val.append(filter_1(line[42:60])) #CUS    #OMEGA  #omega
                    val.append(filter_1(line[61:79])) #rt_a   #CIS    #OMEGA_dot
                elif(lr%8==6):                      # line 6
                    val.append(filter_1(line[4:22]))  #i_dot
                elif(lr%8==7): #line 7
                    continue
                elif(lr%8==0): #line 8
                    #one frame read
                    #call calc_coord method and transfer list
                    x = gCtric(val)
                    sep = '\t'  #for .csv file change to ','
                    disp = str(x[0])+sep+str(x[1])+sep+str(x[2])+sep+str(x[3])
                    target.write(disp)
                    target.write('\n')
                    val = [] #empty array for next frame
            else:
                break
    dat_file.close()
    print(Nav_files[cnt]," converted...")
    target.close()
print("Conversion completed! \nPls check ../GPS_Nav_Dat/Coord.txt for Geocentric Co-Ordinates.")
