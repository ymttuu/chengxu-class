// 定义两个LED引脚（必须是ESP32支持PWM的引脚）
const int ledPinA = 2;   // 灯A
const int ledPinB = 4;   // 灯B

// 设置PWM属性（两个通道使用相同参数）
const int freq = 5000;          // 频率 5000Hz
const int resolution = 8;       // 分辨率 8位 (0-255)

void setup() {
  Serial.begin(115200);

  // 绑定两个LED引脚，自动分配独立PWM通道
  ledcAttach(ledPinA, freq, resolution);
  ledcAttach(ledPinB, freq, resolution);
}

void loop() {
  // 核心：反相渐变
  // A从0→255（变亮），B从255→0（变暗）
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    ledcWrite(ledPinA, dutyCycle);                // 灯A亮度增加
    ledcWrite(ledPinB, 255 - dutyCycle);         // 灯B亮度减少（反相）
    delay(10);
  }

  // A从255→0（变暗），B从0→255（变亮）
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(ledPinA, dutyCycle);
    ledcWrite(ledPinB, 255 - dutyCycle);
    delay(10);
  }
  
  Serial.println("双闪渐变周期完成");
}
