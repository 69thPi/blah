class substance:
    def __init__(self):
        self.name='foo'
        self.cont=[['oxygen',50],['carbon',50]]
        self.form='L'
        self.mWt = 0
        self.fPt = 0
        self.bPt = 0 
        self.cmnts = 'None'
        self.pfrm = ['Isp','thrust','time']

arr=[]
txCnt=['',[],'','','','','',''] #transfer content from GUI to variables
selected_index=0
foo=0 #holds what to select in pickMe substance or property
