# Name: Info Display Window
# Date:2- Aug -2019
# Time: 5:53PM (GMT+4.5)
#
#

import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QPushButton, QTextEdit,
                             QHBoxLayout, QVBoxLayout, QGroupBox, QGridLayout)
from PyQt5.QtCore import pyqtSlot
import subs


class mainWidget(QWidget):
    def __init__(self,parent=None):
        super().__init__()
        self.initUI()

    def createContainer(self):
        #USER INPUT BAR
        grpBox = QGroupBox(subs.txCnt[0],self)
        layout_groupbox = QGridLayout(grpBox)

        content1='Content:<br/>'
        for i in range(len(subs.txCnt[1])):
            content1+=str(subs.txCnt[1][i][0])+' : '+str(subs.txCnt[1][i][1])+'%<br/>'

        content2='Properties:<br/>'+'State:'+str(subs.txCnt[2])+'<br/>Molar Weight:'+str(subs.txCnt[3])+'<br/>Freezing Point:'+str(subs.txCnt[4])+'<br/>Boiling Point:'+str(subs.txCnt[5])+'<br/>Comments:'+str(subs.txCnt[6])
        
        content3='Performance parameters:<br/>'
        for k in range(7,len(subs.txCnt)):
            content3+=str(subs.txCnt[k])+'<br/>'

        ok = QPushButton("OK")
        ok.clicked.connect(self.cancel)

        vbox2 = QVBoxLayout()
        vbox2.addStretch(1)
        vbox2.addWidget(ok)
        
        layout_groupbox.addWidget(QTextEdit(content1),0,0)
        layout_groupbox.addWidget(QTextEdit(content2),0,1)
        layout_groupbox.addWidget(QTextEdit(content3),1,0)        
        layout_groupbox.addLayout(vbox2,1,1)
        

        self.vbox = QVBoxLayout()
        self.vbox.addWidget(grpBox)
    
    def initUI(self):
        self.setGeometry(350, 200, 600, 400)
        self.setWindowTitle('Information')
        self.createContainer()
        self.setLayout(self.vbox)
        self.show()

    @pyqtSlot()
    def cancel(self):
        self.close()


#call to open window
def info_win():
    app = QApplication(sys.argv)
    ex = mainWidget()
    app.exec_()

if __name__=='__main__':
    info_win()
