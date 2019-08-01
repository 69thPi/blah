import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import pyqtSlot,Qt

convo = [['hello sir',''],['','how are you']]

#append interpretations to the list
def UpdateText(content,name):
    if content!='':
        if name==1:
            convo[0].append('')
            convo[1].append(content)
        else:
            convo[0].append(content)
            convo[1].append('')
    

class MainWindow(QMainWindow):

    def __init__(self, parent=None):
        super().__init__()
        self.main_widget = DispWidget(self)
        self.setCentralWidget(self.main_widget)
        self.title = 'INTERPRETER'
        self.left = 350
        self.top = 200
        self.width = 600
        self.height = 400
        self.setFixedSize(self.width, self.height)
        self.Stat= self.statusBar()
        self.status = "Ready|"
        self.init_UI()
        
    #CONSTRUCTOR PARENT WINDOW
    def init_UI(self):
        self.setGeometry(self.left, self.top, self.width, self.height)
        self.Stat.showMessage(self.status)
        self.setWindowTitle(self.title)
        self.show()

    #TO UPDATE THE CONTENT OF THE SCREEN
    def refresh(self):
        self.main_widget.close()
        self.main_widget = DispWidget(self)
        self.setCentralWidget(self.main_widget)

    #TO DETECT ENTER OR ESC 
    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:
            self.close()
        if e.key() == Qt.Key_Return or e.key() == Qt.Key_Enter:
            self.main_widget.user_input()
            

#THE SCREEN, TEXTBOX AND BUTTON INSIDE
class DispWidget(QWidget):

    #WIDGET INIT
    def __init__(self,parent):
        super(DispWidget, self).__init__(parent)
        self.parent=parent
        self.initUI()
        
    #SET TEXT TO DISPLAY
    def createDisplay(self):
        grpBox = QGroupBox('',self)
        layout_groupbox = QVBoxLayout(grpBox)
        val=max(len(convo[0]),len(convo[1]))
        for i in range(0,val):
            if convo[0][i]!='':
                lbl= QLabel('John :'+convo[0][i],grpBox)
                lbl.setObjectName("JohnTxt")
                self.setStyleSheet("""
                #JohnTxt{
                    color: #000;
                    padding: 5px;
                    font-size: 15px;
                    background-color: #FFB300;
                    border-radius:2px;
                    }
                #USRTxt{
                    color: #000;
                    padding: 5px;
                    font-size: 15px;
                    background-color: #FF0266;
                    border-radius:2px;
                    }
                """)
                layout_groupbox.addWidget(lbl)
            if convo[1][i]!='':
                lbl= QLabel('Tanz :'+convo[1][i],grpBox)
                lbl.setObjectName("USRTxt")
                layout_groupbox.addWidget(lbl)
        layout_groupbox.addStretch(1)
        
        return grpBox

    #SET CONTAINER
    def createContainer(self):
        #SET SCROLL AREA
        self.scrollarea = QScrollArea(self)
        self.scrollarea.setFixedWidth(590)
        self.scrollarea.setWidgetResizable(True)
        self.scroll_bar = self.scrollarea.verticalScrollBar()
        self.scroll_bar.rangeChanged.connect(lambda: self.scroll_bar.setValue(self.scroll_bar.maximum()))
        #SET THE LABEL CONTAINER
        self.inwidget = QWidget()
        self.scrollarea.setWidget(self.inwidget)
        self.layout_SArea = QVBoxLayout(self.inwidget)
        self.layout_SArea.addWidget(self.createDisplay())
        self.layout_SArea.addStretch(1)
        
        
    #PARENT SCREEN WIDGET CONSTRUCTOR  
    def initUI(self):
        self.createContainer()
        self.textbox = QLineEdit(self)
        sendButton = QPushButton("SEND")
        sendButton.clicked.connect(self.user_input)
        
        #USER INPUT BAR
        hbox = QHBoxLayout()
        hbox.addWidget(self.textbox)
        hbox.addWidget(sendButton)

        #MAIN LAYOUT
        vbox = QVBoxLayout()
        vbox.addWidget(self.scrollarea)
        vbox.addLayout(hbox)

        #SET MAIN LAYOUT
        self.setLayout(vbox)    

        self.show()

    @pyqtSlot()
    def user_input(self):            # FOR SEND BUTTON PRESS or ENTER
        newMsg = self.textbox.text()
        UpdateText(newMsg,1)
        self.textbox.setText('')
        self.parent.refresh()

#MAIN CALL
if __name__ == '__main__':
        app = QApplication(sys.argv)
        ex = MainWindow()
        sys.exit(app.exec_())
    
