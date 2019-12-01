#include <ESP8266WiFi.h>

const char* ssid = "*";
const char* password = "*";

void setup() {
  Serial.begin(9600);
  delay(10);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("");
  Serial.println("");
  Serial.print("En attente de connexion a ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("Connexion reussie");
  Serial.print("Adresse IP : " );
  Serial.println(WiFi.localIP());
  Serial.print("Adresse MAC : ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  delay(10000);
}
