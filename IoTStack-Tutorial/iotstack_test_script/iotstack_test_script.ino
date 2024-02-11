#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>


// Replace these with your network credentials
const char* ssid = "MST-PSK-N";
const char* password = "YOUR_PASSWORD";

// MQTT Broker settings
const char* mqtt_server = "127.0.0.1";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

void setup_wifi() {
  delay(100);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming MQTT messages here
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("outTopic", "hello world"); // Test message
      client.subscribe("inTopic"); // Subscribe to topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;

    // Dummy data for demonstration
    float temp = 24.5; // Example temperature
    float pressure = 1013.25; // Example pressure
    float humidity = 40.0; // Example humidity
    float gas = 200.0; // Example gas value

    StaticJsonDocument<200> doc;
    doc["t"] = temp;
    doc["p"] = pressure;
    doc["h"] = humidity;
    doc["g"] = gas;

    char output[256];
    serializeJson(doc, output);
    
    Serial.println("Publishing dummy data...");
    client.publish("/home/sensors", output);
  }
}
