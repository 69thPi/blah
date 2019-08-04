import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import pyqtSlot,Qt,QSize
import subs

class ChWidget(QWidget):
    #WIDGET INIT
    def __init__(self,parent=None):
        super().__init__()
        self.initUI()

    #SET TEXT TO DISPLAY
    def createList(self):
        head=[]
        if subs.foo==1:
            for i in range(len(subs.arr)):
                head.append(subs.arr[i].name)
        else:
            head = ['Name','Content','State','Molar Weight','Freezing Point',
                     'Boiling Point','Comments','Performance']    
        self.setStyleSheet("""
        #ops{
            font-size:15px;
            }
        """)
        list = QListWidget()
        for i in range(len(head)): 
            item = QListWidgetItem(list)
            item.setSizeHint(QSize(200,30))
            item_widget=QLabel()
            item_widget.setText('  '+head[i])
            list.addItem(item)
            list.setItemWidget(item, item_widget)               
            item_widget.setObjectName('ops')
        list.itemPressed.connect(lambda:self.find_index(list.currentRow()))
        return list

         
    #PARENT SCREEN WIDGET CONSTRUCTOR  
    def initUI(self):
        self.setGeometry(500, 200, 275, 400)
        self.setWindowTitle('Pick One')
        self.setToolTip('Pick Any One')
       
        lay=QVBoxLayout(self)
       
        lay.addWidget(self.createList())
        #SET MAItLayout(lay)    
        self.show()

    @pyqtSlot()
    def find_index(self,a):
        subs.selected_index=int(a)
        self.close()

def pick(f):
    subs.foo=f
    app = QApplication(sys.argv)
    ex = ChWidget()
    app.exec_()
    

#MAIN CALL
if __name__ == '__main__':
    pick(2)    
    
