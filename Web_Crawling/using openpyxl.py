from openpyxl import load_workbook

Kinds = []
Kinds_num = []
Product = []
pcode = []

Kinds_num_list_num = -1
Kinds_num_num = 1

wb = load_workbook('Product.xlsx')
ws = wb.active

for i in range(2, 55):
  if ws.cell(i,1).value not in Kinds:
    Kinds.append(ws.cell(i,1).value)
    Kinds_num_list_num += 1
    Kinds_num_num = 1
    Kinds_num.append(Kinds_num_num)
    wb.create_sheet('{}'.format(ws.cell(i,1).value))
    wb.sheetnames[-1]
  else:
    Kinds_num[Kinds_num_list_num] += 1
  

print(Kinds)
print(Kinds_num)
print(Product)
print(pcode)
# print(ws.cell(i,3).value)