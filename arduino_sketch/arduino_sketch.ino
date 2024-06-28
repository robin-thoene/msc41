#include <LiquidCrystal_I2C.h>

#define ULTRASONIC_SENSOR_ECHO_PIN 3
#define ULTRASONIC_SENSOR_TRIGGER_PIN 2
#define TEMPERATURE_SENSOR_PIN A0

float currentDistance = -1.0;
float currentTemp = -1.0;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // Initialize the LCD.
  lcd.init();
  // Turn on the backlight.
  lcd.backlight();
  // Define the pin modes as needed.
  pinMode(ULTRASONIC_SENSOR_TRIGGER_PIN, OUTPUT);
  pinMode(ULTRASONIC_SENSOR_ECHO_PIN, INPUT);
}

void loop() {
  // Get the current values.
  currentDistance = getDistanceInCm();
  currentTemp = getTemp();
  // Print the current values to the LCD.
  printMeasurementsToLcd(currentDistance, currentTemp);
  // Wait til the next measurement.
  delay(300);
}

void printMeasurementsToLcd(float distance, float temp) {
  // Ensure the LCD is cleared before printing new values.
  lcd.clear();
  // Print the distance on the first row.
  lcd.setCursor(0,0);
  lcd.print("D = ");
  lcd.print(distance);
  lcd.print(" cm");
  // Print the temperature on the second row.
  lcd.setCursor(0,1);
  lcd.print("T = ");
  lcd.print(temp);
  lcd.print(" C");
}

float getDistanceInCm() {
  float distanceInCm = -1.0;
  // Ensure that the trigger pin is set to low when start to measure.
  digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  // Start the measuring.
  digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, LOW);
  // Get the travel time of the echo.
  int travelTime = pulseIn(ULTRASONIC_SENSOR_ECHO_PIN, HIGH);
  // Calculate the distance in centimeters using the travel time, measured in microseconds.
  // The factor 0.03435 is used because that is how far ultrasonic travels in one microsecond.
  // The result is divided by 2, because the ultrasonic travels to the object and back to the sensor,
  // but we are only interested in the distance to the object.
  distanceInCm = (travelTime * 0.03435) / 2;
  return distanceInCm;
}

float getTemp() {
  float value = -1.0;
  value = analogRead(TEMPERATURE_SENSOR_PIN);
  return (5.0 * value) / (1024 * 0.01);
}
