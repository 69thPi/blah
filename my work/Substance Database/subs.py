class substance:
    def __init__(self):
        self.name='foo'
        self.cont=[['sample 1',50],['sample 2',50]]
        self.form='L'
        self.mWt = 0
        self.fPt = 0
        self.bPt = 0 
        self.cmnts = 'None'
        self.pfrm = ['Isp','thrust','time']
    def ed(self):
        if selected_index==0 :
            self.name=eDat
        elif selected_index==2 :
            self.form=eDat
        elif selected_index==3 :
            self.mWt=eDat
        elif selected_index==4 :
            self.fPt=eDat
        elif selected_index==5 :
            self.bPt=eDat
        elif selected_index==6 :
            self.cmnts=eDat

arr=[]
txCnt=['',[],'','','','','',''] #transfer content from GUI to variables
selected_index=0
foo=0 #holds what to select in pickMe substance or property
into = []
eDat=''
