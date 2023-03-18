import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QLabel
from PyQt5.QtCore import Qt, QMimeData
from PyQt5.QtGui import QDragEnterEvent, QDragMoveEvent, QDropEvent
import subprocess

class DragDropWidget(QWidget):
    def __init__(self):
        super().__init__()

        # Set up the widget to accept drop events
        self.setAcceptDrops(True)

        # Create a label to display the file names
        self.label = QLabel('Drop files here')
        self.label.setAlignment(Qt.AlignCenter)

        # Add the label to the widget
        layout = QVBoxLayout()
        layout.addWidget(self.label)
        self.setLayout(layout)

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

if __name__ == '__main__':
    app = QApplication(sys.argv)
    widget = DragDropWidget()
    widget.resize(400, 300)
    widget.show()
    sys.exit(app.exec_())
