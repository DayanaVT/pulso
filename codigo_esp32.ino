
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "NOMBRE_DE_TU_WIFI";
const char* password = "CONTRASEÑA_DE_TU_WIFI";

const char* serverName = "http://192.168.1.100:3000/api/evento";

const int buttonPin = 12;
int lastButtonState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");
}

void loop() {
  int currentState = digitalRead(buttonPin);
  if (currentState == LOW && lastButtonState == HIGH) {
    Serial.println("Botón presionado");

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");

      unsigned long timestamp = millis();
      String json = "{\"boton\": 1, \"timestamp\": " + String(timestamp) + "}";

      int httpResponseCode = http.POST(json);
      Serial.println("Código de respuesta: " + String(httpResponseCode));
      http.end();
    }
    delay(200);
  }
  lastButtonState = currentState;
}
