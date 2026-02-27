#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    bool isOpen;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println(myData.isOpen);
  if (myData.isOpen == true){
    digitalWrite(12, HIGH);
  }
  else if (myData.isOpen == false){
    digitalWrite(12, LOW);
  }
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  delay(3000);
  Serial.println();
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  pinMode(12, OUTPUT);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
}
 
void loop() {
  delay(100);
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}