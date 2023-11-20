#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>

const char *ssid = "SUA_REDE_WIFI";
const char *password = "SUA_SENHA_WIFI";

Servo servo1, servo2, servo3, servo4;

const int servo1Pin = 2;  // GPIO para o servo 1
const int servo2Pin = 4;  // GPIO para o servo 2
const int servo3Pin = 16; // GPIO para o servo 3
const int servo4Pin = 17; // GPIO para o servo 4

AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);

  server.on("/setservos", HTTP_POST, [](AsyncWebServerRequest *request)
            {
    String message;
    if (request->hasParam("servo1") && request->hasParam("servo2") && request->hasParam("servo3") && request->hasParam("servo4")) {
      int servo1Value = request->getParam("servo1")->value().toInt();
      int servo2Value = request->getParam("servo2")->value().toInt();
      int servo3Value = request->getParam("servo3")->value().toInt();
      int servo4Value = request->getParam("servo4")->value().toInt();

      servo1.write(servo1Value);
      servo2.write(servo2Value);
      servo3.write(servo3Value);
      servo4.write(servo4Value);

      message = "Servos definidos para: Servo1=" + String(servo1Value) + " Servo2=" + String(servo2Value) +
                " Servo3=" + String(servo3Value) + " Servo4=" + String(servo4Value);
    } else {
      message = "Parâmetros ausentes!";
    }

    request->send(200, "text/plain", message); });

  server.begin();
}

void loop() {}