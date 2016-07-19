boolean checkWiFiConnection() {
  int count = 0;
  Serial.print("Waiting to connect to the specified WiFi network");
  while ( count < 30 ) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println();
      Serial.println("Connected!");
      blinkLed.green(&led, 1000, 1);
      return (true);
    }
    delay(500);
    Serial.print(".");
    blinkLed.blue(&led, 200, 1);
    count++;
  }
  Serial.println("Timed out.");
  blinkLed.red(&led, 1000, 1);
  return false;
}
