import pandas as pd
from sklearn.model_selection import train_test_split

file_path = 'encoded_file.csv'
df = pd.read_csv(file_path)

# 학습(train) 데이터와 테스트(test) 데이터로 나누기
df_train, df_test = train_test_split(df, test_size=0.2, random_state=42)

print(f"학습 데이터 크기: {df_train.shape}")
print(f"테스트 데이터 크기: {df_test.shape}")

train_file_path = 'train_data.csv'
test_file_path = 'test_data.csv'
df_train.to_csv(train_file_path, index=False)
df_test.to_csv(test_file_path, index=False)

"""
학습 데이터 크기: (326, 7)
테스트 데이터 크기: (82, 7)
"""