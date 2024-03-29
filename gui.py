import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QLabel, QLineEdit, QPushButton, QHBoxLayout, QToolButton
from PyQt5.QtCore import Qt, QMimeData
from PyQt5.QtGui import QDragEnterEvent, QDragMoveEvent, QDropEvent, QClipboard, QIcon
import subprocess 

def find_id(database_strings, alias):
    for database_string in database_strings:
        id = []
        id.append(database_string[:7])
        database_lower = database_string.lower()
        alias_lower = alias.lower()
        if alias_lower in database_lower:
            id.append(database_string)
            return id
    nothing = []
    nothing.append("#######")
    nothing.append("None found.")
    return nothing
        

class GUI(QWidget):
    def __init__(self):
        super().__init__()
        
        self.setWindowTitle('UBS Sorting Hat')
        self.database_strings = []

        # Enable drag and drop
        self.setAcceptDrops(True)

        # Create a label to display the file names
        self.label = QLabel('Drop .xlsx files here')
        self.label.setAlignment(Qt.AlignCenter)

        # Create a textbox for user input
        self.textbox = QLineEdit()

        # Create a submit button
        self.submit_button = QPushButton('Search')

        # Create ID label
        self.id = QLabel('ID: _______')
        self.id.setAlignment(Qt.AlignCenter)
        self.id.setTextInteractionFlags(Qt.TextSelectableByMouse)

        # Create Company label
        self.company = QLabel('Data: ')
        self.company.setAlignment(Qt.AlignCenter)
        self.company.setWordWrap(True)
        self.company.setTextInteractionFlags(Qt.TextSelectableByMouse)

        # Create copy button
        self.copy_button = QToolButton()

        # Set the icon for the button
        self.copy_icon = QIcon('copy.png')
        self.copy_button.setIcon(self.copy_icon)

        # Connect the button click event to the copy function
        self.copy_button.clicked.connect(self.copy)

        self.errorWarn = QLabel('')
        self.errorWarn.setAlignment(Qt.AlignCenter)

        # Add the label to the widget
        hbox = QHBoxLayout()
        hbox.addWidget(self.textbox)
        hbox.addWidget(self.submit_button)
        vbox = QVBoxLayout()
        vbox.addWidget(self.label)
        vbox.addWidget(self.id)
        vbox.addWidget(self.copy_button)
        vbox.addWidget(self.company)
        vbox.addWidget(self.errorWarn)
        vbox.addLayout(hbox)
        self.setLayout(vbox)

        # Connect the submit button to a method
        self.submit_button.clicked.connect(self.handle_submit)

        try:
            sorted_companies = open("./data/sorted_companies.txt", "r")
            for line in sorted_companies:
                self.database_strings.append(line)
        except OSError:
            self.errorWarn.setText(f"Error: no sheets have been loaded yet...")


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
            subprocess.run(['python3', './scripts/xlsx_to_txt.py', path_to_xlsx])
        else:
            self.label.setText('No XLSX files dropped')
    
    def keyPressEvent(self, event):
        # Handle key presses in the text box
        if event.key() == 16777220:  # Enter key
            text = self.textbox.text()
            self.textbox.setText('')

            # Find the company ID using only a company alias
            company_alias = text
            company_id = find_id(self.database_strings, company_alias)
            self.id.setText(f"ID: {company_id[0]}")
            self.company.setText(f"Data: {company_id[1]}")

    def handle_submit(self):
        # Get the text from the text box and do something with it
        text = self.textbox.text()
        self.textbox.setText('')

        # Find the company ID using only a company alias
        company_alias = text
        company_id = find_id(self.database_strings, company_alias)
        self.id.setText(f"ID: {company_id[0]}")
        self.company.setText(f"Data: {company_id[1]}")


    def copy(self):
        # Get the application clipboard
        clipboard = QApplication.clipboard()

        # Get the text from the label
        text = self.company.text()

        # Set the text to the clipboard
        clipboard.setText(text, QClipboard.Clipboard)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    widget = GUI()
    widget.resize(640, 480)
    widget.show()
    sys.exit(app.exec_())
