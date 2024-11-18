import pandas as pd

file_path = 'data.csv'
df = pd.read_csv(file_path)

original_rows = len(df)
df_cleaned = df.dropna()
cleaned_rows = len(df_cleaned)
rows_difference = original_rows - cleaned_rows

print(f"작업 후 행의 수: {cleaned_rows}\\n기존 행의 수: {original_rows}\\n변동된 행의 수: {rows_difference}")
output_file_path = 'dropna_data.csv'
df_cleaned.to_csv(output_file_path, index=False)

"""
작업 후 행의 수: 408
기존 행의 수: 408
변동된 행의 수: 0
"""