import pandas as pd

filename = "PRoduct.xlsx"
df = pd.read_excel(filename, engine='openpyxl')

print(df)