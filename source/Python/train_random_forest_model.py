import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, confusion_matrix
import joblib
import seaborn as sns
import matplotlib.pyplot as plt

train_file_path = 'train_data.csv' 
test_file_path = 'test_data.csv'   
df_train = pd.read_csv(train_file_path)
df_test = pd.read_csv(test_file_path)

independent_vars = ['Tem', 'Hum', 'Pres']
dependent_var = 'S_PM10'

X_train = df_train[independent_vars]
y_train = df_train[dependent_var]

rf_model = RandomForestClassifier(n_estimators=100, random_state=42)

rf_model.fit(X_train, y_train)

model_filename = 'random_forest_model.joblib'
joblib.dump(rf_model, model_filename)
print(f"모델 {model_filename} 저장됨.")

X_test = df_test[independent_vars]
y_test_true = df_test[dependent_var]
y_pred = rf_model.predict(X_test)

accuracy = accuracy_score(y_test_true, y_pred)
print(f"모델 정확도: {accuracy}")

conf_matrix = confusion_matrix(y_test_true, y_pred)

# 혼동행렬 시각화
plt.figure(figsize=(8, 6))
sns.heatmap(conf_matrix, annot=True, fmt="d", cmap="Blues", xticklabels=rf_model.classes_, yticklabels=rf_model.classes_)
plt.xlabel('Predicted')
plt.ylabel('True')
plt.title('Confusion Matrix')
plt.show()