#include <WiFi.h>
#include <ArduinoMqttClient.h>
#include <HardwareSerial.h>

HardwareSerial STM32(2);

// WiFi
const char *ssid = "POCO F6";
const char *password = "01234567";

// MQTT Broker
const char *broker = "10.167.33.179";
const int port = 1883;

const char *topic = "industrial/safety";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

void setup()
{
    Serial.begin(115200);

    STM32.begin(115200, SERIAL_8N1, 16, 17);

    Serial.print("Connecting to WiFi");

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi Connected");

    Serial.print("ESP32 IP : ");
    Serial.println(WiFi.localIP());

    Serial.print("Connecting MQTT...");

    if (!mqttClient.connect(broker, port))
    {
        Serial.println(" Failed");

        while (1);
    }

    Serial.println(" Connected");
}

void loop()
{
    mqttClient.poll();

    if (STM32.available())
    {
        String data = STM32.readStringUntil('\n');

        Serial.println(data);

        mqttClient.beginMessage(topic);
        mqttClient.print(data);
        mqttClient.endMessage();

        Serial.println("Published");
    }
}