import pandas as pd
import numpy as np

file_path = 'ldl.csv'
df = pd.read_csv(file_path)

numeric_columns = df.select_dtypes(include=[np.float64, np.float32, np.int64, np.int32])

correlation_with_type = numeric_columns.corrwith(df['P_PM10'])

sorted_corr = correlation_with_type.abs().sort_values(ascending=False)

print("P_PM10 변수와의 상관계수의 절댓값이 큰 순서대로 나열:")
for index in sorted_corr.index:
    correlation_value = correlation_with_type[index]
    sign = "+" if correlation_value >= 0 else "-"
    print(f"{index: <30}{abs(correlation_value):.6f} ({sign})")

"""
P_PM10 변수와의 상관계수의 절댓값이 큰 순서대로 나열:
P_PM10                        1.000000 (+)
Pres                          0.186190 (+)
Tem                           0.082812 (+)
Hum                           0.047368 (+)

P_PM2.5 변수와의 상관계수의 절댓값이 큰 순서대로 나열:
P_PM2.5                       1.000000 (+)
Pres                          0.379990 (+)
Hum                           0.364136 (+)
Tem                           0.009446 (-)
"""