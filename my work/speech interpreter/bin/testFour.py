import sys
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets  import QStatusBar, QMainWindow, QApplication, QWidget,QHBoxLayout, QVBoxLayout, QPushButton, QSlider, QLCDNumber, QLabel

class MyMainWindow(QMainWindow):

    def __init__(self, parent=None):
        super().__init__()
        self.main_widget = FormWidget(self)
        self.setCentralWidget(self.main_widget)
        self.init_UI()

    def init_UI(self):
        self.statusBar().showMessage('Ready')
        self.setGeometry(200, 100, 300, 300)
        self.setWindowTitle('Central Widget')
        self.show()

class FormWidget(QWidget):

    def __init__(self, parent):
        super(FormWidget, self).__init__(parent)
        self.init_UI()

    def init_UI(self):
        hbox = QHBoxLayout()
        button_1 = QPushButton('Button 1', self)
        button_1.clicked.connect(self.buttonClicked)
        hbox.addWidget(button_1)
        button_2 = QPushButton('Button 2', self)
        button_2.clicked.connect(self.buttonClicked)
        hbox.addWidget(button_2)
        self.setLayout(hbox)
        self.setGeometry(200, 100, 300, 300)
        self.setWindowTitle('Slider and LCD')
        self.show()

    def buttonClicked(self):
        sender = self.sender()
        self.statusBar.showMessage(sender.text() + ' was clicked')

if __name__ == '__main__':
    APP = QApplication(sys.argv)
    ex = MyMainWindow()
    sys.exit(APP.exec_())
