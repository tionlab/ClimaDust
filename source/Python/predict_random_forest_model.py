import joblib
import pandas as pd
from sklearn.metrics import accuracy_score, confusion_matrix
import seaborn as sns
import matplotlib.pyplot as plt

model_path = 'random_forest_model.joblib'
model = joblib.load(model_path)

test_file_path = 'testest.csv'
df_test = pd.read_csv(test_file_path)

independent_vars = ['Tem', 'Hum', 'Pres']
dependent_var = 'S_PM10'

X_test = df_test[independent_vars]
y_test = df_test[dependent_var]
y_pred = model.predict(X_test)

accuracy = accuracy_score(y_test, y_pred)
print(f"Accuracy: {accuracy}")

conf_matrix = confusion_matrix(y_test, y_pred)

plt.figure(figsize=(10, 7))
sns.heatmap(conf_matrix, annot=True, fmt='d', cmap='Blues')
plt.xlabel('Predicted')
plt.ylabel('Actual')
plt.title('Confusion Matrix')
plt.show()

df_test['Predicted_' + dependent_var] = y_pred
output_file_path = 'predicted_testest.csv'
df_test.to_csv(output_file_path, index=False)

print(f"Predictions saved to {output_file_path}")

"""
Accuracy: 0.9090909090909091
Predictions saved to predicted_testest.csv
"""