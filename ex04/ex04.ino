#define TOUCH_PIN 4
#define LED_PIN 2
#define THRESHOLD 500  

// 布尔状态变量：记录LED当前亮灭状态
bool ledState = false;

// 边缘检测变量：记录上一次是否触摸
bool lastTouched = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  Serial.begin(115200); 
}

void loop() {

  uint16_t touchValue = touchRead(TOUCH_PIN);
  // 判断当前是否正在触摸
  bool isTouched = (touchValue < THRESHOLD);

  
  if (isTouched == true && lastTouched == false) {
    // 翻转LED状态
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);

    
  }

  // 更新上一次状态，为下一次检测做准备
  lastTouched = isTouched;

  delay(100); 
}