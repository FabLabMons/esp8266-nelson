#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "*";
const char* password = "*";
const int servo_pin = D1;

Servo my_servo;
int servo_position = 0;

ESP8266WebServer server(80);

void displayForm() {
  String html = "<!DOCTYPE HTML>\r\n<html><p>Angle actuel du servo : " + String(servo_position) + "°</p>";
  html += "<form method=\"POST\" action=\"/\">";
  html += "<p><input type=\"radio\" name=\"servo_position\" value=\"0\"";
  if (servo_position == 0) {
    html += " checked";
  }
  html += "> 0°</p>";
  html += "<p><input type=\"radio\" name=\"servo_position\" value=\"30\"";
  if (servo_position == 30) {
    html += " checked";
  }
  html += "> 30°</p>";
  html += "<p><input type=\"radio\" name=\"servo_position\" value=\"60\"";
  if (servo_position == 60) {
    html += " checked";
  }
  html += "> 60°</p>";
  html += "<p><input type=\"radio\" name=\"servo_position\" value=\"90\"";
  if (servo_position == 90) {
    html += " checked";
  }
  html += "> 90°</p>";
  html += "<p><input type=\"radio\" name=\"servo_position\" value=\"120\"";
  if (servo_position == 120) {
    html += " checked";
  }
  html += "> 120°</p>";
  html += "<p><input type=\"radio\" name=\"servo_position\" value=\"150\"";
  if (servo_position == 150) {
    html += " checked";
  }
  html += "> 150°</p>";
  html += "<p><input type=\"radio\" name=\"servo_position\" value=\"180\"";
  if (servo_position == 180) {
    html += " checked";
  }
  html += "> 180°</p>";
  html += "<p><input type=\"submit\"></p>";
  html += "</form>";
  html += "</html>\n";

  server.send(200, "text/html", html);
}

/* Handle requests to change position. */
void changePosition() {
  servo_position = server.arg("servo_position").toInt();
  my_servo.write(servo_position);
  redirectToForm();
}

/* Handle all the other requests. */
void redirectToForm() {
  server.sendHeader("Location", "/", true);
  server.send(303, "text/plain", "");
}

void setup() {
  Serial.begin(9600);
  delay(10);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("");
  Serial.print("En attente de connexion a ");
  Serial.println(ssid);

  // prepare servo
  my_servo.attach(servo_pin, 500, 2500);
  my_servo.write(servo_position);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("Connexion reussie");
  Serial.print("Adresse IP : " );
  Serial.println(WiFi.localIP());
  
  // Start the web server
  server.on("/", HTTP_GET, displayForm);
  server.on("/", HTTP_POST, changePosition);
  server.onNotFound(redirectToForm);
  server.begin();
  Serial.print("Serveur web disponible a l'adresse http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  server.handleClient();
}
