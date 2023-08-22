#include <ESP8266WiFi.h>

const char* ssid ="HCK Connect";
const char* password = "#erlad77";

WiFiServer server(80);

void setup() {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);

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

  if (client) {
    String request = client.readStringUntil('\n');
    client.flush();
    Serial.println(request);

    if (request.indexOf("ledon1") != -1) {
      digitalWrite(D1, HIGH);
      Serial.println("LED 1 is ON");
    }

    if (request.indexOf("ledoff1") != -1) {
      digitalWrite(D1, LOW);
      Serial.println("LED 1 is OFF");
    }

    if (request.indexOf("ledon2") != -1) {
      digitalWrite(D2, HIGH);
      Serial.println("LED 2 is ON");
    }

    if (request.indexOf("ledoff2") != -1) {
      digitalWrite(D2, LOW);
      Serial.println("LED 2 is OFF");
    }

    if (request.indexOf("ledon3") != -1) {
      digitalWrite(D3, HIGH);
      Serial.println("LED 3 is ON");
    }

    if (request.indexOf("ledoff3") != -1) {
      digitalWrite(D3, LOW);
      Serial.println("LED 3 is OFF");
    }

    // Handle the "Tihar" button
    if (request.indexOf("tiharon") != -1) {
      // Alternate turning LEDs on and off to create a light show
      for (int i = 0; i < 5; i++) {
        digitalWrite(D1, HIGH);
        digitalWrite(D2, LOW);
        digitalWrite(D3, HIGH);
        delay(500);  // Adjust the delay as needed
        digitalWrite(D1, LOW);
        digitalWrite(D2, HIGH);
        digitalWrite(D3, LOW);
        delay(500);  // Adjust the delay as needed
      }
      // Turn off all LEDs
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      Serial.println("Light show (Tihar)");
    }

    if (request.indexOf("tiharoff") != -1) {
      // Turn off all LEDs
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      Serial.println("Tihar effect turned off");
    }

    // Send the HTML response with CSS styles
    sendHTML(client);

    Serial.println("Client disconnected");
    Serial.println("------------------");
    Serial.println("                  ");
  }
}

void sendHTML(WiFiClient client) {
  // Improved CSS styles
  String cssStyle = "<style>";
  cssStyle += "body { font-family: Arial, sans-serif; background-color: #f0f0f0; }";
  cssStyle += ".container { display: flex; flex-direction: column; align-items: center; justify-content: center; height: 100vh; }";
  cssStyle += ".button { display: inline-block; padding: 10px 20px; font-size: 18px; border: none; cursor: pointer; margin: 5px; }";
  cssStyle += ".blue-btn { background-color: #0074d9; color: white; }";
  cssStyle += ".red-btn { background-color: #ff4136; color: white; }";
  cssStyle += ".yellow-btn { background-color: #ffdc00; color: black; }";
  cssStyle += ".tihar-bg { background-color: #6e2c00; color: white; }";
  cssStyle += "</style>";

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>Controlling LEDs</title>");
  client.println(cssStyle);  // Adding the CSS styles
  client.println("</head>");
  client.println("<body>");
  client.println("<div class=\"container\">");
  client.println("<h1>NodeMCU and Wifi Network</h1>");
  client.println("<p><a href=\"/ledon1\"><button class=\"button blue-btn\">LED 1 ON</button></a>");
  client.println("<a href=\"/ledoff1\"><button class=\"button red-btn\">LED 1 OFF</button></a></p>");
  client.println("<p><a href=\"/ledon2\"><button class=\"button blue-btn\">LED 2 ON</button></a>");
  client.println("<a href=\"/ledoff2\"><button class=\"button red-btn\">LED 2 OFF</button></a></p>");
  client.println("<p><a href=\"/ledon3\"><button class=\"button blue-btn\">LED 3 ON</button></a>");
  client.println("<a href=\"/ledoff3\"><button class=\"button red-btn\">LED 3 OFF</button></a></p>");
  client.println("<p><a href=\"/tiharon\"><button class=\"button yellow-btn tihar-bg\">Tihar</button></a></p>");
    client.println("<a href=\"/tiharoff\"><button class=\"button red-btn\">Turn Off Tihar</button></a></p>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");
}
