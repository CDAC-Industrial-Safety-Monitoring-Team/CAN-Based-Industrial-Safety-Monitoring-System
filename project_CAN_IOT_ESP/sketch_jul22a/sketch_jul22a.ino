void setup() {
 
  Serial.begin(115200);

    // RX = GPIO16, TX = GPIO17
    STM32.begin(115200, SERIAL_8N1, 16, 17);

    Serial.println("ESP32 Ready");

}

void loop() {
  while (STM32.available())
    {
        String data = STM32.readStringUntil('\n');

        Serial.print("Received: ");
        Serial.println(data);
    }

}
