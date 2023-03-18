import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QLabel, QLineEdit, QPushButton, QHBoxLayout
from PyQt5.QtCore import Qt, QMimeData
from PyQt5.QtGui import QDragEnterEvent, QDragMoveEvent, QDropEvent
import subprocess

class DragDropWidget(QWidget):
    def __init__(self):
        super().__init__()

        # Enable drag and drop
        self.setAcceptDrops(True)

        # Create a label to display the file names
        self.label = QLabel('Drop .xlsx file here')
        self.label.setAlignment(Qt.AlignCenter)

        # Create a textbox for user input
        self.textbox = QLineEdit()

        # Create a submit button
        self.submit_button = QPushButton('Search')

        # Add the label to the widget
        hbox = QHBoxLayout()
        hbox.addWidget(self.textbox)
        hbox.addWidget(self.submit_button)
        vbox = QVBoxLayout()
        vbox.addWidget(self.label)
        vbox.addLayout(hbox)
        self.setLayout(vbox)

        # Connect the submit button to a method
        self.submit_button.clicked.connect(self.handle_submit)


    def dragEnterEvent(self, event: QDragEnterEvent):
        # Accept the event if it contains URLs
        if event.mimeData().hasUrls():
            event.accept()
        else:
            event.ignore()

    def dragMoveEvent(self, event: QDragMoveEvent):
        # Accept the event if it contains URLs
        if event.mimeData().hasUrls():
            event.accept()
        else:
            event.ignore()

    def dropEvent(self, event: QDropEvent):
        # Get the list of URLs from the event and display the file names
        urls = event.mimeData().urls()
        file_names = [url.toLocalFile() for url in urls]
        xlsx_files = [file_name for file_name in file_names if file_name.endswith('.xlsx')]
        if xlsx_files:
            self.label.setText('\n'.join(xlsx_files))
            path_to_xlsx = xlsx_files[0]
            # Run the script with arguments
            subprocess.run(['python3', './xlsx_to_txt.py', path_to_xlsx])
        else:
            self.label.setText('No XLSX files dropped')
        # self.label.setText('\n'.join(file_names))
    
    def keyPressEvent(self, event):
        # Handle key presses in the text box
        if event.key() == 16777220:  # Enter key
            text = self.textbox.text()
            print(f'Text entered: {text}')
            self.textbox.setText('')

    def handle_submit(self):
        # Get the text from the text box and do something with it
        text = self.textbox.text()
        print(f'Text submitted: {text}')
        self.textbox.setText('')

if __name__ == '__main__':
    app = QApplication(sys.argv)
    widget = DragDropWidget()
    widget.resize(400, 300)
    widget.show()
    sys.exit(app.exec_())
