import pandas as pd

file_path = 'train.csv'

df = pd.read_csv(file_path)

mapping = {'Good': 0, 'Normal': 1, 'Bad': 2, 'Worst': 3}

df['S_PM2.5'] = df['S_PM2.5'].map(mapping)
df['S_PM10'] = df['S_PM10'].map(mapping)

df.to_csv('encoded_file.csv', index=False)