const int MOTION_SENSOR_PIN = 3;  // Motion sensor output pin
const int LED = 7;                 // LED pin
const int TEMP_SENSOR_PIN = A0;    // Temperature sensor pin

void setup() {
  Serial.begin(9600);  // Initialize serial communication

  pinMode(MOTION_SENSOR_PIN, INPUT);  // Set motion sensor pin to input
  pinMode(LED, OUTPUT);               // Set LED pin to output
  
  attachInterrupt(digitalPinToInterrupt(MOTION_SENSOR_PIN), motionDetected, CHANGE);  // Attach motion sensor interrupt
}

void loop() {
  float temperature = readTemperature();  // Read temperature from sensor
  
  Serial.print("Temp: ");  // Display temperature
  Serial.print(temperature);
  Serial.println(" °C");
  
  if (temperature > 25.0) {  // Check for high temperature
    Serial.println("High temp detected!");
  }

  delay(2000);  // Delay for displaying temperature readings
}

void motionDetected() {
  if (digitalRead(MOTION_SENSOR_PIN) == HIGH) {
    Serial.println("LED ON Motion detected!");  // Turn on LED
    digitalWrite(LED, HIGH);
  } else {
    Serial.println("LED OFF Motion stopped!");  // Turn off LED
    digitalWrite(LED, LOW);
  }

  delay(500);  // Add delay for interrupt debounce
}

float readTemperature() {
  int sensorValue = analogRead(TEMP_SENSOR_PIN);  // Read analog value from temperature sensor
  float voltage = (sensorValue / 1024.0) * 5.0;  // Convert analog value to voltage
  float temperature = (voltage - 0.5) * 100.0;  // Convert voltage to temperature in degrees Celsius
  return temperature;
}
