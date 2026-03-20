// 定义LED引脚
const int ledPin = 26;

// SOS时间参数（可按需调整）
const unsigned long shortOn = 200;    // 短闪亮灯时间
const unsigned long shortOff = 200;  // 短闪熄灭时间
const unsigned long longOn = 600;     // 长闪亮灯时间
const unsigned long longOff = 200;    // 长闪熄灭时间
const unsigned long sosPause = 2000;  // 整组SOS后长停顿时间

// 定义SOS状态机的每个阶段
enum SOSState {
  SHORT1_ON, SHORT1_OFF,
  SHORT2_ON, SHORT2_OFF,
  SHORT3_ON, SHORT3_OFF,
  LONG1_ON,  LONG1_OFF,
  LONG2_ON,  LONG2_OFF,
  LONG3_ON,  LONG3_OFF,
  SHORT4_ON, SHORT4_OFF,
  SHORT5_ON, SHORT5_OFF,
  SHORT6_ON, SHORT6_OFF,
  SOS_PAUSE
};

SOSState currentState = SHORT1_ON;  // 初始状态：第一个短闪点亮
unsigned long previousMillis = 0;   // 记录上一次状态切换的时间戳

void setup() {
  // 设置LED引脚为输出模式
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 获取当前系统运行的毫秒数
  unsigned long currentMillis = millis();

  // 状态机：逐阶段执行SOS闪烁逻辑
  switch (currentState) {
    // 第一组短闪：亮→灭
    case SHORT1_ON:
      if (currentMillis - previousMillis >= shortOn) {
        digitalWrite(ledPin, LOW);
        previousMillis = currentMillis;
        currentState = SHORT1_OFF;
      } else {
        digitalWrite(ledPin, HIGH);
      }
      break;
    case SHORT1_OFF:
      if (currentMillis - previousMillis >= shortOff) {
        digitalWrite(ledPin, HIGH);
        previousMillis = currentMillis;
        currentState = SHORT2_ON;
      } else {
        digitalWrite(ledPin, LOW);
      }
      break;

    // 第二组短闪：亮→灭
    case SHORT2_ON:
      if (currentMillis - previousMillis >= shortOn) {
        digitalWrite(ledPin, LOW);
        previousMillis = currentMillis;
        currentState = SHORT2_OFF;
      } else {
        digitalWrite(ledPin, HIGH);
      }
      break;
    case SHORT2_OFF:
      if (currentMillis - previousMillis >= shortOff) {
        digitalWrite(ledPin, HIGH);
        previousMillis = currentMillis;
        currentState = SHORT3_ON;
      } else {
        digitalWrite(ledPin, LOW);
      }
      break;

    // 第三组短闪：亮→灭
    case SHORT3_ON:
      if (currentMillis - previousMillis >= shortOn) {
        digitalWrite(ledPin, LOW);
        previousMillis = currentMillis;
        currentState = SHORT3_OFF;
      } else {
        digitalWrite(ledPin, HIGH);
      }
      break;
    case SHORT3_OFF:
      if (currentMillis - previousMillis >= shortOff) {
        digitalWrite(ledPin, HIGH);
        previousMillis = currentMillis;
        currentState = LONG1_ON;
      } else {
        digitalWrite(ledPin, LOW);
      }
      break;

    // 第一组长闪：亮→灭
    case LONG1_ON:
      if (currentMillis - previousMillis >= longOn) {
        digitalWrite(ledPin, LOW);
        previousMillis = currentMillis;
        currentState = LONG1_OFF;
      } else {
        digitalWrite(ledPin, HIGH);
      }
      break;
    case LONG1_OFF:
      if (currentMillis - previousMillis >= longOff) {
        digitalWrite(ledPin, HIGH);
        previousMillis = currentMillis;
        currentState = LONG2_ON;
      } else {
        digitalWrite(ledPin, LOW);
      }
      break;

    // 第二组长闪：亮→灭
    case LONG2_ON:
      if (currentMillis - previousMillis >= longOn) {
        digitalWrite(ledPin, LOW);
        previousMillis = currentMillis;
        currentState = LONG2_OFF;
      } else {
        digitalWrite(ledPin, HIGH);
      }
      break;
    case LONG2_OFF:
      if (currentMillis - previousMillis >= longOff) {
        digitalWrite(ledPin, HIGH);
        previousMillis = currentMillis;
        currentState = LONG3_ON;
      } else {
        digitalWrite(ledPin, LOW);
      }
      break;

    // 第三组长闪：亮→灭
    case LONG3_ON:
      if (currentMillis - previousMillis >= longOn) {
        digitalWrite(ledPin, LOW);
        previousMillis = currentMillis;
        currentState = LONG3_OFF;
      } else {
        digitalWrite(ledPin, HIGH);
      }
      break;
    case LONG3_OFF:
      if (currentMillis - previousMillis >= longOff) {
        digitalWrite(ledPin, HIGH);
        previousMillis = currentMillis;
        currentState = SHORT4_ON;
      } else {
        digitalWrite(ledPin, LOW);
      }
      break;

    // 第四组短闪（SOS第三段短闪1）：亮→灭
    case SHORT4_ON:
      if (currentMillis - previousMillis >= shortOn) {
        digitalWrite(ledPin, LOW);
        previousMillis = currentMillis;
        currentState = SHORT4_OFF;
      } else {
        digitalWrite(ledPin, HIGH);
      }
      break;
    case SHORT4_OFF:
      if (currentMillis - previousMillis >= shortOff) {
        digitalWrite(ledPin, HIGH);
        previousMillis = currentMillis;
        currentState = SHORT5_ON;
      } else {
        digitalWrite(ledPin, LOW);
      }
      break;

    // 第五组短闪（SOS第三段短闪2）：亮→灭
    case SHORT5_ON:
      if (currentMillis - previousMillis >= shortOn) {
        digitalWrite(ledPin, LOW);
        previousMillis = currentMillis;
        currentState = SHORT5_OFF;
      } else {
        digitalWrite(ledPin, HIGH);
      }
      break;
    case SHORT5_OFF:
      if (currentMillis - previousMillis >= shortOff) {
        digitalWrite(ledPin, HIGH);
        previousMillis = currentMillis;
        currentState = SHORT6_ON;
      } else {
        digitalWrite(ledPin, LOW);
      }
      break;

    // 第六组短闪（SOS第三段短闪3）：亮→灭
    case SHORT6_ON:
      if (currentMillis - previousMillis >= shortOn) {
        digitalWrite(ledPin, LOW);
        previousMillis = currentMillis;
        currentState = SHORT6_OFF;
      } else {
        digitalWrite(ledPin, HIGH);
      }
      break;
    case SHORT6_OFF:
      if (currentMillis - previousMillis >= shortOff) {
        digitalWrite(ledPin, LOW);
        previousMillis = currentMillis;
        currentState = SOS_PAUSE;
      } else {
        digitalWrite(ledPin, LOW);
      }
      break;

    // SOS整组播放完毕后的长停顿
    case SOS_PAUSE:
      if (currentMillis - previousMillis >= sosPause) {
        previousMillis = currentMillis;
        currentState = SHORT1_ON;  // 重置状态，循环播放SOS
      } else {
        digitalWrite(ledPin, LOW);  // 保持熄灭
      }
      break;
  }

  // 此处可添加其他代码，不受SOS闪烁逻辑阻塞
}