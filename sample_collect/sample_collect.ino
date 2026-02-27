#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int buttonPin = 13;

const int sampleRate = 50;      // Hz
const float sampleTime = 0.5;   // seconds
const int totalSamples = sampleRate * sampleTime;  // 25 samples
const int interval = 1000 / sampleRate;  // 20ms

void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.begin();
  mpu.initialize();

  pinMode(buttonPin, INPUT_PULLUP);

  Serial.println("ax,ay,az");   // CSV header
  Serial.println("Ready. Press button to record...");
}

void loop() {

  if (digitalRead(buttonPin) == LOW) {
    delay(50);  // 简单防抖

    Serial.println("ax,ay,az");  // 每次采样前打印 header

    for (int i = 0; i < totalSamples; i++) {
      int16_t ax, ay, az;
      mpu.getAcceleration(&ax, &ay, &az);

      Serial.print(ax);
      Serial.print(",");
      Serial.print(ay);
      Serial.print(",");
      Serial.println(az);

      delay(interval);
    }

    Serial.println();   // 空行分隔
    Serial.println("Done. Press again.");
    
    delay(500);  // 防止重复触发
  }
}