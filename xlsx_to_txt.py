import openpyxl
from difflib import SequenceMatcher
import sys
import os

def main():
    script_dir = os.path.dirname(__file__) #<-- absolute dir the script is in
    data_rel_path = "data/past_companies.txt"
    data_abs_file_path = os.path.join(script_dir, data_rel_path)
    # sheet_rel_path = "sheet.xlsx"
    sheet_rel_path = "Book4.xlsx"
    sheet_abs_file_path = os.path.join(script_dir, sheet_rel_path)
    output_rel_path = "interim/sheet_contents.txt"
    output_abs_file_path = os.path.join(script_dir, output_rel_path)

    try:
        wrkbk = openpyxl.load_workbook(sheet_abs_file_path)
    except OSError:
       print("Could not open/read file: ", sheet_rel_path)
       sys.exit()
    try:
        past_data = open(data_abs_file_path, "r+")
    except OSError:
        print("Could not open/read file: ", data_rel_path)
        sys.exit()
    
    output = open(output_abs_file_path, "w+")
    sh = wrkbk.active

    # list_count = int(sys.argv[1])
    list_count = 2 # is this always true?
    lists = []                            # BUG: this line should work, but sometimes throws a list index out of range error
    # lists = [[]]

    for i in range(list_count):
        lists.append([])

    # iterate through excel and store data
    for i in range(1, sh.max_row+1):                # range starts from 1 because excel sheets start from 1
        for j in range(1, sh.max_column+1):
            cell_obj = sh.cell(row=i, column=j)
            cell = str(cell_obj.value)
            if cell == "Grand Total" or cell.startswith("List") or cell.startswith("LIST"):
                    continue
            elif cell != "None":
                lists[j-1].append(cell)             # j-1 because the loop starts at 1, since excel files start at 1 (otherwise lists[0] would be empty)

    for l in lists:
        for j in l:
            output.write(j)
            output.write("\n")
        output.write("\n")

    return list_count

main()