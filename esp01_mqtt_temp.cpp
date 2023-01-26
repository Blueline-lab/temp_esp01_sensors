#include "DHT.h"
#include "PubSubClient.h" // Connect and publish to the MQTT broker
#include "ESP8266WiFi.h"  // Enables the ESP8266 to connect to the local network 
#define DHTPIN 2       // Pin connected to the DHT sensor.

#define DHTTYPE DHT11  // DHT11 , DHT22
DHT dht(DHTPIN, DHTTYPE);

// WiFi
const char* ssid = "";                 
const char* wifi_password = ""; 

// MQTT
const char* mqtt_server = "192.168.1.105";  // IP of the MQTT broker
const char* humidity_topic = "home/cuisine/humidite";
const char* temperature_topic = "home/cuisine/temperature";
const char* mqtt_username = ""; // MQTT username
const char* mqtt_password = ""; // MQTT password
const char* clientID = ""; // MQTT client ID

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient); 


// Custom function to connet to the MQTT broker via WiFi
void connect_MQTT(){
  WiFi.begin(ssid, wifi_password);
}
void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  connect_MQTT();
  Serial.setTimeout(1000);
  
  float h = dht.readHumidity();
  delay(1000);
  float t = dht.readTemperature();
  delay(1000);

  // PUBLISH to the MQTT Broker (topic = Temperature, defined at the beginning)
  
  client.connect(clientID, mqtt_username, mqtt_password);
  delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
  client.publish(temperature_topic, String(t).c_str());
  delay(100);
  client.connect(clientID, mqtt_username, mqtt_password);
  delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
  client.publish(humidity_topic, String(h).c_str());
  
  client.disconnect();  // disconnect from the MQTT broker
  delay(1000*60);       // print new values every 1 Minute
}
