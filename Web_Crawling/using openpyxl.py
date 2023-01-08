

from openpyxl import load_workbook

wb = load_workbook('Product.xlsx')
ws = wb.active

for i in range(1, 55):
  print(ws.cell(i,1).value)


  
# print(ws.cell(i,3).value)