import tensorflow as tf
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.utils import to_categorical
import pandas as pd

# Load your data
data = pd.read_csv('your_data.csv')  # make sure to provide the correct path to your dataset
X = data.drop('Label', axis=1)
y = data['Label']

# Split data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Scale features (Feature scaling is important for neural network convergence)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# Convert labels to one-hot encoding
y_train_categorical = to_categorical(y_train)
y_test_categorical = to_categorical(y_test)

# Build the model
model = Sequential([
    Dense(y_train_categorical.shape[1], activation='softmax', input_shape=(X_train_scaled.shape[1],))
])

# Compile the model
model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])

# Train the model
model.fit(X_train_scaled, y_train_categorical, epochs=100, validation_data=(X_test_scaled, y_test_categorical))

# Evaluate the model
loss, accuracy = model.evaluate(X_test_scaled, y_test_categorical)
print("Test Accuracy: {:.2f}".format(accuracy))
