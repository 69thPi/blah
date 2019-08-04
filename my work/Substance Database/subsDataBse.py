# Name: SUBSTANCE DATABASE
# Date:2- Aug -2019
# Time: 2:24PM (GMT+4)
#
#
import subs as idk
from subs import substance
from newSubs import new_win
from pickMe import pick
from infoDisp import info_win

t=substance()
u=substance() #u = unassigned child
idk.arr =[t,t,t,t,t,t,t,t,t,t,t,t,t,t,t]


dBfile = 'subs_dB.xlsx'
change=False


def initialize(): #load from textfile into array
    try:
        
        if change==True:
            print('a')
    except No_Database_Found:
        ig=input('Frist time with this program?(y/n)\n#~')
        if ig=='y':
            init_start()
        else:
            print("Oops! Database not found.")

#add a new substance into array
def add_subs():
    #TAKE INPUT
    new_win()
    #STORE INPUT INTO NEW CHILD 
    u.name=idk.txCnt[0]
    u.cont=idk.txCnt[1]
    u.form=idk.txCnt[2]
    u.mWt=idk.txCnt[3]
    u.fPt=idk.txCnt[4]
    u.bPt=idk.txCnt[5]
    u.cmnts=idk.txCnt[6]
    for i in range(7,len(idk.txCnt)):
        u.pfrm.append(idk.txCnt[i])
    #AND APPEND TO LOCAL LIST
    idk.arr.append(u)

def load_txarr():
    pick(1) #pick substance
    u=idk.arr[idk.selected_index]
    print(idk.selected_index)
    idk.txCnt=[u.name,u.cont,u.form,
               u.mWt,u.fPt,u.bPt,u.cmnts]
    for j in range(len(u.pfrm)):
        idk.txCnt.append(u.pfrm[j])
    #transfer all data to txCnt
    print(idk.txCnt)
    
#edit substance data    ##sub-Menu {identity, properties, performance params}
def edit_subs():
    load_txarr()
    pick(2) #pick params
    print(idk.selected_index)
    #use selected_index to select field
    
    #edit paramter of selected index
    #set selected_index to -1
    pass
    
def view_subs():
    load_txarr()
    info_win()


#save changes
def save():
    pass


def init_start():
    ig=input('\n\n\n=================\n\nWELCOME!\n\n=================You have not yet added any substances.\nWould you like to add now?(y/n)\n#~')
    if ig=='y':
        add_subs()
    else:
        print('quitting...')
        pass

def menu():
    print('\n\n==========================\n')
    print('              MENU\n')
    print('    Press            Option\n')
    print('      1             Add New\n')
    print('      2            View Data\n')
    print('      3            Edit Data')
    while(1):
        ig=input('\n#~')
        if int(ig)==1:
            add_subs()
            change=True
        elif int(ig)==2:
            view_subs()
        elif int(ig)==3:
            edit_subs()
            change=True
        else:
            print('\nInvalid Option') #if invalid option user enters again pass: skips through the remainder of the loop
            pass
        break

def flow():
    initialize()
    while(1):
        menu()
        ig=input('\nWould you like to return to menu?(y/n)\n#~')
        if ig!='y':
            break
    if change==True:
        save()
        

if __name__=='__main__':
    flow()


    
    
