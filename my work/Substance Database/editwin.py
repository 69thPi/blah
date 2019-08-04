# Name: Edit Window
# Date:2- Aug -2019
# Time: 3:09PM (GMT+4.5)
#
#

import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QPushButton, QTextEdit,
                             QHBoxLayout, QVBoxLayout)
from PyQt5.QtCore import pyqtSlot


content = 'None' #set global across files

def set_content(a):
    content = a
 

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
        textbox = QTextEdit(self)
        textbox.setText(content)
        
        hbox = QHBoxLayout()
        hbox.addStretch(2)
        hbox.addWidget(save)
        hbox.addStretch(1)
        hbox.addWidget(cancel)
        hbox.addStretch(2)

        self.vbox = QVBoxLayout()
        self.vbox.addWidget(textbox)
        self.vbox.addLayout(hbox)
    
    def initUI(self):
        self.setGeometry(350, 200, 600, 400)
        self.setWindowTitle('Edit')
        self.createContainer()
        self.setLayout(self.vbox)
        self.show()

    @pyqtSlot()
    def save(self):
        #update and return content
        self.close()
    def cancel(self):
        self.close()


#call to open window
def edit_win(ty=1):
    if ty==1:
        app = QApplication(sys.argv)
        ex = mainWidget()
        app.exec_()   
