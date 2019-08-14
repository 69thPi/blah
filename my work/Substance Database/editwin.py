# Name: Edit Window
# Date:2- Aug -2019
# Time: 3:09PM (GMT+4.5)
#
#

import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QPushButton, QTextEdit,
                             QHBoxLayout, QVBoxLayout)
from PyQt5.QtCore import pyqtSlot
import subs

def set_content():
    if subs.selected_index==1:
        a=''
        """for i in txCnt[1]:
            a+=i[0]+':'+i[1]+'%;' # FIX THIS PART TO EDIT ELEMENTS"""
    else:
        a = subs.txCnt[subs.selected_index]
    return a
 

class mainWidget(QWidget):
    def __init__(self,parent=None):
        super().__init__()
        self.initUI()

    def createContainer(self):
        #USER INPUT BAR
        save = QPushButton("SAVE")
        cancel = QPushButton("Cancel")
        save.clicked.connect(self.save)
        cancel.clicked.connect(self.cancel)
        self.textbox = QTextEdit(self)
        self.textbox.setText(set_content())
        
        hbox = QHBoxLayout()
        hbox.addStretch(2)
        hbox.addWidget(save)
        hbox.addStretch(1)
        hbox.addWidget(cancel)
        hbox.addStretch(2)

        self.vbox = QVBoxLayout()
        self.vbox.addWidget(self.textbox)
        self.vbox.addLayout(hbox)
    
    def initUI(self):
        self.setGeometry(350, 200, 600, 400)
        self.setWindowTitle('Edit')
        self.createContainer()
        self.setLayout(self.vbox)
        self.show()

    @pyqtSlot()
    def save(self):
        subs.eDat=self.textbox.toPlainText()
        self.close()
    def cancel(self):
        self.close()


#call to open window
def edit_win():
        app = QApplication(sys.argv)
        ex = mainWidget()
        app.exec_()

if __name__=='__main__':
    edit_win()
