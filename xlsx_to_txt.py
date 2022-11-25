import openpyxl
from difflib import SequenceMatcher
import sys

def main():
    wrkbk = openpyxl.load_workbook("/Users/brianmatzelle/projects/string_sorting/sheet.xlsx")
    output = open("/Users/brianmatzelle/projects/string_sorting/interim/sheet_contents.txt","w+")
    
    sh = wrkbk.active

    list_count = int(sys.argv[1])
    lists = [[]]
    for i in range(list_count):
        lists.append([])

    # iterate through excel and store data
    for i in range(1, sh.max_row+1):
        for j in range(1, sh.max_column+1):
            cell_obj = sh.cell(row=i, column=j)
            cell = str(cell_obj.value)
            if cell == "Grand Total":
                    continue
            if cell != "None":
                lists[j].append(cell)

    for l in lists:
        if l:
            for j in l:
                output.write("\n")
                output.write(j)
            output.write("\n")
    return list_count

main()