#include <SPI.h>
#include <Arduino.h>
#include <WiFi.h>
#include <FS.h>
#include <SD.h>

String getEncryptionType(int encryption) {
  switch (encryption) {
    case WIFI_AUTH_OPEN:
      return "Open";
    case WIFI_AUTH_WEP:
      return "WEP";
    case WIFI_AUTH_WPA_PSK:
      return "WPA_PSK";
    case WIFI_AUTH_WPA2_PSK:
      return "WPA2_PSK";
    case WIFI_AUTH_WPA_WPA2_PSK:
      return "WPA/WPA2_PSK";
    case WIFI_AUTH_WPA2_ENTERPRISE:
      return "WPA2_Enterprise";
    case WIFI_AUTH_WPA3_PSK:
      return "WPA3_PSK";
    case WIFI_AUTH_WPA2_WPA3_PSK:
      return "WPA2/WPA3_PSK";
    default:
      return "Unknown";
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

}

void loop() {
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("No Networks Found");
  }
  else {
    Serial.printf("%d Networks Found\n---------------------------------------------------------\n", n);
  }

  for (int i = 0; i < n; ++i) {
    String wifiScanResults = "";
    wifiScanResults += String(i+1) + " | ";
    wifiScanResults += WiFi.SSID(i) + " | ";
    wifiScanResults += WiFi.BSSIDstr(i) + " | ";
    wifiScanResults += getEncryptionType(WiFi.encryptionType(i));

    Serial.println(wifiScanResults);
  }
  delay(5000);
}
