#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "evan";
const char* password = "evanlulu";
const int LED_PIN = 2;

WebServer server(80);

String makePage() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>实验2</title>
</head>
<body style="font-family:Arial; text-align:center; margin-top:50px;">

  <h1>LED 亮度控制</h1>
  <p>当前亮度：<span id="val">0</span></p>

  <input type="range" min="0" max="255" value="0" id="slider" style="width:80%; height:30px;">
  
  <br><br>

  <a href="/on"><button style="padding:10px 20px;">点亮 LED</button></a>
  <a href="/off"><button style="padding:10px 20px;">熄灭 LED</button></a>

  <script>
    const slider = document.getElementById('slider');
    const val = document.getElementById('val');

    slider.addEventListener('input', function() {
      val.innerText = this.value;
      fetch('/set?bright=' + this.value);
    });
  </script>
</body>
</html>
)rawliteral";
  return html;
}

void handleRoot() {
  server.send(200, "text/html; charset=UTF-8", makePage());
}

void handleOn() {
  analogWrite(LED_PIN, 255);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  analogWrite(LED_PIN, 0);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleSet() {
  int bright = server.arg("bright").toInt();
  analogWrite(LED_PIN, bright);
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, 0);

  WiFi.begin(ssid, password);
  Serial.print("连接WiFi中...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi 连接成功！");
  Serial.print("IP 地址：");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.on("/set", handleSet);
  server.begin();
}

void loop() {
  server.handleClient();
}