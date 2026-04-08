#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "evan";
const char* password = "evanlulu";

const int TOUCH_PIN = T0;

WebServer server(80);

String getHtml() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>实时触摸仪表盘</title>
  <style>
    body{text-align:center;font-family:Arial;margin-top:80px;}
    #value{font-size:80px;font-weight:bold;color:#007bff;}
  </style>
</head>
<body>
  <h1>实时触摸传感器值</h1>
  <div id="value">--</div>

  <script>
    async function update() {
      try {
        let res = await fetch("/data");
        let val = await res.text();
        document.getElementById("value").innerText = val;
      } catch(e) {}
    }
    setInterval(update, 150);  // 150ms刷新一次
  </script>
</body>
</html>
)rawliteral";
  return html;
}

void handleRoot() {
  server.send(200, "text/html", getHtml());
  server.client().stop(); // 关键：立即关闭连接，防止卡死
}

void handleData() {
  int val = touchRead(TOUCH_PIN);
  server.send(200, "text/plain", String(val));
  server.client().stop(); // 关键：关闭连接
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

void loop() {
  server.handleClient();
}