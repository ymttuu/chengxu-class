#include <WiFi.h>
#include <WebServer.h>

// ==================== 配置区 ====================
const char* ssid = "evan";
const char* password = "evanlulu";

const int LED_PIN = 2;          // LED引脚
const int TOUCH_PIN = 4;       // 触摸引脚 GPIO4
const int THRESHOLD = 500;       // 触摸灵敏度

// ==================== 全局状态 ====================
bool isArmed = false;    // 布防状态：false=撤防，true=布防
bool isAlarming = false; // 报警状态：是否正在报警

WebServer server(80);

// ==================== 网页 ====================
String getPage() {
  String status;
  if (isAlarming) status = "正在报警！";
  else if (isArmed) status = "已布防";
  else status = "已撤防";

  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>安防报警器</title>
</head>
<body style="text-align:center; margin-top:50px; font-family:Arial;">
  <h1>物联网安防报警器</h1>
  <h2 style="color:red;">)rawliteral" + status + R"rawliteral(</h2>
  
  <a href="/arm"><button style="padding:15px 30px; font-size:18px; margin:10px;">布防 (Arm)</button></a>
  <a href="/disarm"><button style="padding:15px 30px; font-size:18px; margin:10px;">撤防 (Disarm)</button></a>
</body>
</html>
)rawliteral";
  return html;
}

// ==================== 网页路由 ====================
void handleRoot() {
  server.send(200, "text/html; charset=UTF-8", getPage());
}

// 布防
void handleArm() {
  isArmed = true;
  isAlarming = false;
  digitalWrite(LED_PIN, LOW);
  Serial.println("系统：已布防");
  server.sendHeader("Location", "/");
  server.send(303);
}

// 撤防
void handleDisarm() {
  isArmed = false;
  isAlarming = false;
  digitalWrite(LED_PIN, LOW);
  Serial.println("系统：已撤防");
  server.sendHeader("Location", "/");
  server.send(303);
}

// ==================== 报警闪烁 ====================
void alarmFlash() {
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(100);
}

// ==================== 初始化 ====================
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // WiFi连接
  Serial.print("连接WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi连接成功");
  Serial.print("IP: http://");
  Serial.println(WiFi.localIP());

  // 网页路由
  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
  Serial.println("Web服务器已启动");
}

// ==================== 主循环 ====================
void loop() {
  server.handleClient();

  // 1. 如果正在报警 → 狂闪
  if (isAlarming) {
    alarmFlash();
    return;
  }

  // 2. 如果已布防，检测触摸
  if (isArmed) {
    int touchValue = touchRead(TOUCH_PIN);
    if (touchValue < THRESHOLD) {
      Serial.println("触发报警！");
      isAlarming = true; // 锁定报警
    }
  }
}
