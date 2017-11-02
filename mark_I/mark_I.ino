#include <ESP8266WiFi.h>

const char* ssid = "Totalplay-8195";
const char* password = "81956A81qN3nEKbx";


void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.print("Connecting to");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); //Client mode
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  Serial.println("Hi");
  delay(1000);
}
