// 定义LED引脚
const int ledPin = 26;

// 1Hz闪烁参数：周期1000ms，亮/灭各500ms
const unsigned long blinkInterval = 500;
// 记录上一次LED状态切换的时间
unsigned long previousMillis = 0;
// 记录当前LED状态（LOW=灭，HIGH=亮）
bool ledState = LOW;

void setup() {
  // 设置LED引脚为输出模式
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 获取当前系统运行的毫秒数
  unsigned long currentMillis = millis();

  // 非阻塞判断：时间差达到间隔则切换LED状态
  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis; 
    ledState = !ledState;            // 翻转LED状态（亮→灭/灭→亮）
    digitalWrite(ledPin, ledState);  // 输出状态到LED引脚
  }
}

