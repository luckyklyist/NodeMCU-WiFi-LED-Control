#include <ESP8266WiFi.h>

const char* ssid = "wifi_name";
const char* password = "wifi_password";

WiFiServer server(80);

void setup() {
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("NodeMCU is connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  delay(3000);
}

void loop() {
  WiFiClient client;
  client = server.available();

  if (client == 1) {
    String request = client.readStringUntil('\n');
    client.flush();
    Serial.println(request);
    if (request.indexOf("ledon") != -1) {
      digitalWrite(D1, HIGH);
      Serial.println("LED is ON");
    }

    if (request.indexOf("ledoff") != -1) {
      digitalWrite(D1, LOW);
      Serial.println("LED is OFF");
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();

    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<title>Controlling LED</title>");
    client.println("<style>");
    client.println("body { font-family: Arial, sans-serif; background-color: #f0f0f0; }");
    client.println(".container { text-align: center; margin-top: 50px; }");
    client.println(".button { display: inline-block; padding: 10px 20px; font-size: 18px; background-color: #ffc107; border: none; cursor: pointer; }");
    client.println("</style>");
    client.println("</head>");
    client.println("<body>");
    client.println("<div class=\"container\">");
    client.println("<h1>NodeMCU and Wifi Network</h1>");
    client.println("<p><a href=\"/ledon\"><button class=\"button\">ON</button></a></p>");
    client.println("<p><a href=\"/ledoff\"><button class=\"button\">OFF</button></a></p>");
    client.println("</div>");
    client.println("</body>");
    client.println("</html>");

    Serial.println("Client disconnected");
    Serial.println("------------------");
    Serial.println("                  ");
  }
}
