#include <WiFi.h>
#include <esp_now.h>

//副板地址：F4:2D:C9:70:EA:7C
uint8_t broadcastAddress[] = {0xF4, 0x2D, 0xC9, 0x70, 0xEA, 0x7C};

typedef struct struct_message {
  bool isOpen;
} struct_message;

struct_message myData;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(3000);
  Serial.println();

  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Serial.print("Pin13: ");
  // Serial.print(digitalRead(13));
  // Serial.print("  Pin14: ");
  // Serial.println(digitalRead(14));
  // delay(200);
  if (digitalRead(13) == LOW){
    myData.isOpen = true;
  }
  else if (digitalRead(14) == LOW){
    myData.isOpen = false;
  }


  
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
  Serial.print("MyData.isOpen = ");
  Serial.println(myData.isOpen);
    //打印发送状态
  if (result == ESP_OK){
    Serial.println("Sent with success");
  }
  else{
    Serial.println("Sent failed");
  }

  delay(100);
}