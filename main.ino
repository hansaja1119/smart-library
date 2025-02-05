#include "WiFi.h"
#include "Firebase_ESP_Client.h"
#include "DHT.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Wi-Fi credentials
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_SSID_PASSWORD"

// Firebase credentials
#define API_KEY "YOUR_API_KEY"
#define DATABASE_URL "YOUR_DB_LINK/"
#define USER_EMAIL "User_Email"
#define USER_PASSWORD "User_Password"

// Pin Definitions
#define TRIG_PIN 5
#define ECHO_PIN 18
#define DHT_PIN 26
#define LDR_PIN 34
#define RED_LED 13
#define GREEN_LED 12
#define BUZZER_PIN 14
#define LAMP_PIN 25

// Constants
#define DHT_TYPE DHT11
#define LDR_THRESHOLD 500
#define TEMP_THRESHOLD 30

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

// Initialize DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  // Initialize Serial
  Serial.begin(115200);

  // Initialize Sensors and Outputs
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LAMP_PIN, OUTPUT);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  // Configure Firebase
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;

  Firebase.reconnectNetwork(true);
  fbdo.setBSSLBufferSize(4096, 1024);
  fbdo.setResponseSize(2048);
  Firebase.begin(&config, &auth);
  Firebase.setDoubleDigits(5);
  config.timeout.serverResponse = 10 * 1000;
}

void loop() {
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 2000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    // Read Sensor Data
    float distance = readUltrasonic();
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();
    int ldrValue = analogRead(LDR_PIN);

    // Update Seat Status
    bool isOccupied = (distance < 20);
    digitalWrite(RED_LED, isOccupied ? HIGH : LOW);
    digitalWrite(GREEN_LED, isOccupied ? LOW : HIGH);

    // Control Reading Lamp
    int brightness = map(ldrValue, 0, 4095, 255, 0);
    if(isOccupied){
      analogWrite(LAMP_PIN, brightness);
    }else{
      analogWrite(LAMP_PIN, 0);
    }

    // Check Environmental Conditions
    if (temp > TEMP_THRESHOLD || ldrValue < LDR_THRESHOLD) {
      digitalWrite(BUZZER_PIN, HIGH);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
    }

    // Send Data to Firebase
    Firebase.RTDB.setBool(&fbdo, F("/library/seatOccupied"), isOccupied);
    Firebase.RTDB.setFloat(&fbdo, F("/library/temperature"), temp);
    Firebase.RTDB.setFloat(&fbdo, F("/library/humidity"), humidity);
    Firebase.RTDB.setInt(&fbdo, F("/library/lightLevel"), ldrValue);
    Firebase.RTDB.setInt(&fbdo, F("/library/lampBrightness"), brightness);

    // Print Data to Serial Monitor
    Serial.printf("Seat Occupied: %s\n", isOccupied ? "Yes" : "No");
    Serial.printf("Temperature: %.2f°C\n", temp);
    Serial.printf("Humidity: %.2f%%\n", humidity);
    Serial.printf("Light Level: %d\n", ldrValue);
    Serial.printf("Lamp Brightness: %d\n", brightness);
  }
}

// Helper Function to Read Ultrasonic Sensor
float readUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2; // Convert to cm
}
