// 定义LED引脚
const int ledPin = 2;  

// 设置PWM属性
const int freq = 5000;          // 频率 5000Hz
const int resolution = 8;       // 分辨率 8位 (0-255)

// ======================
// 触摸开关相关定义
// ======================
#define TOUCH_PIN 4
#define THRESHOLD 500  // 触摸阈值

// 边缘检测变量（必须）
bool lastTouched = false;
// 速度档位：1慢 2中 3快（循环切换）
int speedGear = 1;
const int maxGear = 3;

// 呼吸速度（延时时间）
int delayTime = 12;  // 默认1档

void setup() {
  Serial.begin(115200);

  // 新版LED PWM绑定（你提供的原版代码）
  ledcAttach(ledPin, freq, resolution);
}

void loop() {
  // ======================
  // 1. 触摸边缘检测：切换档位
  // 仅在“按下瞬间”切换一次
  // ======================
  uint16_t touchVal = touchRead(TOUCH_PIN);
  bool isTouched = (touchVal < THRESHOLD);

  // 边缘检测：上一次没触摸，现在触摸 → 切换档位
  if (isTouched && !lastTouched) {
    speedGear++;
    if (speedGear > maxGear) {
      speedGear = 1;
    }

    // 根据档位设置呼吸速度
    switch (speedGear) {
      case 1: delayTime = 12; break;   // 慢
      case 2: delayTime = 6;  break;   // 中
      case 3: delayTime = 2;  break;   // 快
    }

    Serial.print("切换档位：");
    Serial.println(speedGear);
  }
  lastTouched = isTouched;


  // ======================
  // 2. 原版呼吸灯逻辑（根据档位变速）
  // ======================
  // 逐渐变亮
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    ledcWrite(ledPin, dutyCycle);   
    delay(delayTime);  // 使用档位延时
  }

  // 逐渐变暗
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(ledPin, dutyCycle);   
    delay(delayTime);  // 使用档位延时
  }

  Serial.println("呼吸周期完成");
}