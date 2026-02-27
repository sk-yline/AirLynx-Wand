#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(3000);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();   // 强制初始化 WiFi 硬件
  delay(100);

  Serial.println("MAC:");
  Serial.println(WiFi.macAddress());
}

void loop() {
  // put your main code here, to run repeatedly:

}
