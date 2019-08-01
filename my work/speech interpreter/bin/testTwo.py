import sys
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow, QPushButton,QScrollArea, QLineEdit, QLabel
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import pyqtSlot


pc_l=["a","a"]
user_l=["b","b","b"]

class App(QMainWindow):

    def __init__(self):
        super().__init__()
        self.title = 'Speech Display'
        self.left = 350
        self.top = 200
        self.width = 600
        self.height = 400
        self.setFixedSize(self.width, self.height)
        self.status = "ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
        self.initUI()

    def createDisplay(self):
        grpBox = QGroupBox('',self)
        layout_groupbox = QVBoxLAyout(grpBox)
        dispLen=max(len(pc_l),len(user_l))
        for i in range(dispLen):
            lbl= QLabel(user_l,grpBox)
            layout_groupbox.addWidget(lbl)
        layout_groupbox.addStretch(1)
        return grpBox

    def createContainter(self):
        self.scrollarea = QScrollArea(self)
        self.scrollarea.setFixedWidth(500)
        self.scrollarea.setWidgetResizable(True)

        widget = QWidget()
        self.scrollarea.setWidget(widget)
        self.layout_SArea = QVBoxLayout(widget)
        self.layout_SArea.addWidget(self.createDisplay())
        self.layout_SArea.addStretch(1)
            
        
    def initUI(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        self.label = QLabel ('',self)
        self.label.setObjectName("DispTxt")
        self.label.move(10,10)
        self.label.resize(580,330)

        self.setStyleSheet("""
            #DispTxt{
                color: #000;
                padding: 5px;
                font-size: 20px;
                background-color: #FFB300;
                border-radius:5px;
                }
        """)
        scrollArea = QScrollArea()
        scrollArea.setWidget(self.label)

        self.textbox = QLineEdit(self)
        self.textbox.move(10,350)
        self.textbox.resize(470,30)
        
        button = QPushButton('SEND',self)
        button.setToolTip('Sends the Message')
        button.move(490,350)
        button.clicked.connect(self.on_click)
        
        self.statusBar().showMessage(self.status)
        
        self.show()

    @pyqtSlot()
    def on_click(self):
        newMsg = self.label.text() + " \n " + "USER:" + self.textbox.text()
        self.label.setText(newMsg)
        self.textbox.setText('')
    
if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())
