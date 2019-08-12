# Name: Edit Window
# Date:2- Aug -2019
# Time: 6:13PM (GMT+4.5)
#
#

import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import pyqtSlot,Qt
import subs as ik

into = []

class MainWindow(QMainWindow):

    def __init__(self, parent=None):
        super().__init__()
        self.main_Widget = mainWidget(self)
        self.setCentralWidget(self.main_Widget)
        self.init_UI()
        
    #CONSTRUCTOR PARENT WINDOW
    def init_UI(self):
        self.setGeometry(350, 100, 600, 600)
        self.setWindowTitle('New Entry')
        self.show()

    #TO UPDATE THE CONTENT OF THE SCREEN
    def refresh(self):
        self.main_Widget.close()
        self.main_Widget = mainWidget(self)
        self.setCentralWidget(self.main_Widget)


class mainWidget(QWidget):

    def __init__(self,parent=None):
        super(mainWidget, self).__init__(parent)
        self.parent=parent
        self.initUI()

        
    def createDisp(self):
        self.grpBox = QGroupBox('',self)
        self.Vbox = QVBoxLayout(self.grpBox)
        if len(into)!=0:
            for i in range(len(into)):
                self.txt1 = QLineEdit(into[i][0])
                self.txt2 = QLineEdit(into[i][1])
                lay_htemp = QHBoxLayout()
                lay_htemp.addWidget(self.txt1)
                lay_htemp.addWidget(self.txt2)
                self.Vbox.addLayout(lay_htemp)
        self.txt1 = QLineEdit('')
        self.txt2 = QLineEdit('')
        lay_htemp = QHBoxLayout()
        lay_htemp.addWidget(self.txt1)
        lay_htemp.addWidget(self.txt2)
        self.Vbox.addLayout(lay_htemp)
        return self.grpBox

    def save_val(self):
        ik.txCnt[0]=self.inp1.text()
        ik.txCnt[2]=self.inp3.text()
        ik.txCnt[3]=self.inp4.text()
        ik.txCnt[4]=self.inp5.text()
        ik.txCnt[5]=self.inp6.text()
        ik.txCnt[6]=self.inp7.text()
        ik.txCnt[7]=self.inp8.toPlainText()
        
        
    def set_val(self):
        ik.txCnt=[]
        ik.txCnt.append(self.inp1.text())
        into.append([self.txt1.text(),self.txt2.text()])#//add last added element
        ik.txCnt.append(into)# add into
        ik.txCnt.append(self.inp3.text())
        ik.txCnt.append(self.inp4.text())
        ik.txCnt.append(self.inp5.text())
        ik.txCnt.append(self.inp6.text())
        ik.txCnt.append(self.inp7.text())
        yuck=self.inp8.toPlainText()+','
        bl=''
        for i in yuck:
            if i!=',':
                bl+=i
            else:
                ik.txCnt.append(bl)
                bl=''

    def createContainer(self):
        #FIRST NAME LAYOUT
        self.hbox1 = QHBoxLayout()
        lbl = QLabel('Name          =',self)
        self.inp1 = QLineEdit(str(ik.txCnt[0]))
        self.inp1.setToolTip('Enter the name of the substance')
        self.hbox1.addWidget(lbl)
        self.hbox1.addWidget(self.inp1)

        #CONSTITUENTS LAYOUT
        self.hbox2 = QHBoxLayout()
        lbl = QLabel('Constituents  =',self)
        self.scroll  = QScrollArea(self)
        self.scroll.setFixedWidth(350)
        self.scroll.setWidgetResizable(True)
        self.scroll_bar = self.scroll.verticalScrollBar()
        self.scroll_bar.rangeChanged.connect(lambda: self.scroll_bar.setValue(self.scroll_bar.maximum()))
        add = QPushButton("Add")
        add.clicked.connect(self.renew)

        #add lineEdits for name and percent
        self.scroll.setWidget(self.createDisp())
        self.hbox2.addWidget(lbl)
        self.hbox2.addWidget(self.scroll)
        self.hbox2.addWidget(add)

        # subs form LAYOUT
        self.hbox3 = QHBoxLayout()
        lbl = QLabel('State                   =',self)
        self.inp3 = QLineEdit(str(ik.txCnt[2]))
        self.inp3.setToolTip('Enter the state of the substance')
        self.hbox3.addWidget(lbl)
        self.hbox3.addWidget(self.inp3)

        # subs weight LAYOUT
        self.hbox4 = QHBoxLayout()
        lbl = QLabel('Weight                =',self)
        self.inp4 = QLineEdit(str(ik.txCnt[3]))
        self.inp4.setToolTip('Enter the weight of the substance')
        self.hbox4.addWidget(lbl)
        self.hbox4.addWidget(self.inp4)

        # subs freezin pt LAYOUT
        self.hbox5 = QHBoxLayout()
        lbl = QLabel('Freezing Point   =',self)
        self.inp5 = QLineEdit(str(ik.txCnt[4]))
        self.inp5.setToolTip('Enter the freezing point of the substance')
        self.hbox5.addWidget(lbl)
        self.hbox5.addWidget(self.inp5)

        # subs boiling point LAYOUT
        self.hbox6 = QHBoxLayout()
        lbl = QLabel('Boiling Point      =',self)
        self.inp6 = QLineEdit(str(ik.txCnt[5]))
        self.inp6.setToolTip('Enter the boiling point of the substance')
        self.hbox6.addWidget(lbl)
        self.hbox6.addWidget(self.inp6)

        # subs remarks LAYOUT
        self.hbox7 = QHBoxLayout()
        lbl = QLabel('Comments         =',self)
        self.inp7= QLineEdit(str(ik.txCnt[6]))
        self.inp7.setToolTip('Remarks...')
        self.hbox7.addWidget(lbl)
        self.hbox7.addWidget(self.inp7)

        #PERFORMANCE
        self.hbox8 = QHBoxLayout()
        lbl = QLabel('Performance     =\n Parameters',self)
        self.inp8= QTextEdit(str(ik.txCnt[7]))
        self.inp8.setToolTip('in order seperated by commas::[abc,def,ghi..]')
        self.hbox8.addWidget(lbl)
        self.hbox8.addWidget(self.inp8)

        
        #SAVE/CANCEL BAR LAYOUT
        save = QPushButton("SAVE")
        cancel = QPushButton("Cancel")
        save.clicked.connect(self.save)
        cancel.clicked.connect(self.cancel)
        
        self.hbox = QHBoxLayout()
        self.hbox.addStretch(2)
        self.hbox.addWidget(save)
        self.hbox.addStretch(1)
        self.hbox.addWidget(cancel)
        self.hbox.addStretch(2)

        #ADD ALL WIDGETS
        self.vbox = QVBoxLayout()
        self.vbox.addLayout(self.hbox1)
        self.vbox.addLayout(self.hbox2)
        self.vbox.addLayout(self.hbox3)
        self.vbox.addLayout(self.hbox4)
        self.vbox.addLayout(self.hbox5)
        self.vbox.addLayout(self.hbox6)
        self.vbox.addLayout(self.hbox7)
        self.vbox.addLayout(self.hbox8)
        self.vbox.addLayout(self.hbox)
    
    def initUI(self):
        self.createContainer()
        self.setLayout(self.vbox)
        self.show()

    @pyqtSlot()
    def save(self):
        self.set_val()
        self.parent.close()
    def cancel(self):
        self.parent.close()
    def renew(self):
        self.save_val()
        self.elm=self.txt1.text()
        self.perc=self.txt2.text()
        if self.elm!='':
            into.append([self.elm,self.perc])
        self.parent.refresh()
           


#MAIN CALL
def new_win():
        app = QApplication(sys.argv)
        ex = MainWindow()
        app.exec_()

if __name__=='__main__':
    new_win()
    
