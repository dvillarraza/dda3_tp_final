/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-mqtt-publish-dht11-dht22-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include "DHT.h"
#include <WiFi.h>
extern "C" {
  #include "freertos/FreeRTOS.h"
  #include "freertos/timers.h"
}
#include <AsyncMqttClient.h>

#define WIFI_SSID "diac"
#define WIFI_PASSWORD "Diac22139"

// Raspberry Pi Mosquitto MQTT Broker
#define MQTT_HOST IPAddress(192, 168, 0, 65)
// For a cloud MQTT broker, type the domain name
//#define MQTT_HOST "example.com"
#define MQTT_PORT 1883

// Temperature MQTT Topics
#define MQTT_PUB_TEMP "ESP32_2/dht/temperature"
#define MQTT_PUB_HUM  "ESP32_2/dht/humidity"
#define MQTT_PUB_TEMP_HUM "ESP32_2/dht/temp_hum"
#define MQTT_PUB_LED "ESP32_2/status/led"
#define MQTT_SUB_LED  "ESP32_2/led"

// Digital pin connected to the DHT sensor
#define DHTPIN 4

// Led builtin
#define LED_BUILTIN 2

// Uncomment whatever DHT sensor type you're using
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)   

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Variables to hold sensor readings
float temp;
float hum;

AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

unsigned long previousMillis = 0;   // Stores last time temperature was published
const long interval = 10000;        // Interval at which to publish sensor readings

void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void WiFiEvent(WiFiEvent_t event) {
  Serial.printf("[WiFi-event] event: %d\n", event);
  switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      connectToMqtt();
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
      xTimerStart(wifiReconnectTimer, 0);
      break;
  }
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
  uint16_t packetIdSub = mqttClient.subscribe(MQTT_SUB_LED, 2);
  Serial.print("Subscribing at QoS 2, packetId: ");
  Serial.println(packetIdSub);
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  Serial.println("Publish received.");
  Serial.print("  topic: ");
  Serial.println(topic);
//  Serial.print("  qos: ");
//  Serial.println(properties.qos);
//  Serial.print("  dup: ");
//  Serial.println(properties.dup);
//  Serial.print("  retain: ");
//  Serial.println(properties.retain);
//  Serial.print("  len: ");
//  Serial.println(len);
//  Serial.print("  index: ");
//  Serial.println(index);
  Serial.print("  payload: ");
  String str_payload = String(payload).substring(0, len);
  Serial.println(str_payload);  
//  Serial.print("  total: ");
//  Serial.println(total);
  if (str_payload.equals("on")) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("============> led on\n");

  } else if (str_payload.equals("off")) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("============> led off\n");
  }

  String str_payload1 = String(digitalRead(LED_BUILTIN));

  // Publish an MQTT message on topic esp32/dht/humidity
  uint16_t packetIdPub4 = mqttClient.publish(MQTT_PUB_LED, 1, true, String(str_payload1).c_str());                            
  Serial.printf("Publishing on topic %s at QoS 1, packetId %i: \n", MQTT_PUB_LED, packetIdPub4);
  Serial.printf("=====> Message LED: %s \n", str_payload1);


}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
  if (WiFi.isConnected()) {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttPublish(uint16_t packetId) {
  Serial.print("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void setup() {

  // Configure pins of buttons and leds
  pinMode(LED_BUILTIN, OUTPUT);  

  Serial.begin(115200);
  Serial.println();

  dht.begin();
  
  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));

  WiFi.onEvent(WiFiEvent);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  // If your broker requires authentication (username and password), set them below
  //mqttClient.setCredentials("REPlACE_WITH_YOUR_USER", "REPLACE_WITH_YOUR_PASSWORD");
  connectToWifi();
}

void loop() {
  unsigned long currentMillis = millis();
  // Every X number of seconds (interval = 10 seconds) 
  // it publishes a new MQTT message
  if (currentMillis - previousMillis >= interval) {
    // Save the last time a new reading was published
    previousMillis = currentMillis;
    // New DHT sensor readings
    hum = dht.readHumidity();
    // Read temperature as Celsius (the default)
    temp = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    //temp = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(temp) || isnan(hum)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    
    // Publish an MQTT message on topic esp32/dht/temperature
    uint16_t packetIdPub1 = mqttClient.publish(MQTT_PUB_TEMP, 1, true, String(temp).c_str());                            
    Serial.printf("Publishing on topic %s at QoS 1, packetId: %i\n", MQTT_PUB_TEMP, packetIdPub1);
    Serial.printf("=====> Message: %.2f \n", temp);

    // Publish an MQTT message on topic esp32/dht/humidity
    uint16_t packetIdPub2 = mqttClient.publish(MQTT_PUB_HUM, 1, true, String(hum).c_str());                            
    Serial.printf("Publishing on topic %s at QoS 1, packetId %i: \n", MQTT_PUB_HUM, packetIdPub2);
    Serial.printf("=====> Message: %.2f \n", hum);

    String str_payload = String(temp) + ", " + String(hum);

    // Publish an MQTT message on topic esp32/dht/humidity
    uint16_t packetIdPub3 = mqttClient.publish(MQTT_PUB_TEMP_HUM, 1, true, String(str_payload).c_str());                            
    Serial.printf("Publishing on topic %s at QoS 1, packetId %i: \n", MQTT_PUB_TEMP_HUM, packetIdPub3);
    Serial.printf("=====> Message temp: %.2f  hum: %.2f\n", temp, hum);

    String str_payload1 = String(digitalRead(LED_BUILTIN));

    // Publish an MQTT message on topic esp32/dht/humidity
    uint16_t packetIdPub4 = mqttClient.publish(MQTT_PUB_LED, 1, true, String(str_payload1).c_str());                            
    Serial.printf("Publishing on topic %s at QoS 1, packetId %i: \n", MQTT_PUB_LED, packetIdPub4);
    Serial.printf("=====> Message LED: %s \n", str_payload1);

  }
}