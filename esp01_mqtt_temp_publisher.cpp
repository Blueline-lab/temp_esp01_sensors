#include "DHT.h"
#include "PubSubClient.h" // Connect and publish to the MQTT broker
#include "ESP8266WiFi.h"  // Enables the ESP8266 to connect to the local network (via WiFi)
#define DHTPIN 2       // Pin connected to the DHT sensor

#define DHTTYPE DHT11  // DHT11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

// WiFi
const char* ssid = "Wifi";                 // Your personal network SSID
const char* wifi_password = "93435208"; // Your personal network password

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
  Serial.setTimeout(2000);
  
  float h = dht.readHumidity();
  delay(3000);
  float t = dht.readTemperature();

  // MQTT can only transmit strings
  String hs="Hum: "+String((float)h)+" % ";
  String ts="Temp: "+String((float)t)+" C ";

  // PUBLISH to the MQTT Broker (topic = Temperature, defined at the beginning)
  if (client.publish(temperature_topic, String(t).c_str())) {
    
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(temperature_topic, String(t).c_str());
  }

  // PUBLISH to the MQTT Broker (topic = Humidity, defined at the beginning)
  if (client.publish(humidity_topic, String(h).c_str())) {
    
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(humidity_topic, String(h).c_str());
  }
  client.disconnect();  // disconnect from the MQTT broker
  delay(1000*120);       // print new values every 1 Minute
}