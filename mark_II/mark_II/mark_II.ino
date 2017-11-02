#include <ESP8266WiFi.h>

WiFiServer server(80);

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP("nodeMCU","Pass.word0");
  server.begin();

  Serial.begin(9600);
  IPAddress HTTPS_ServerIP = WiFi.softAPIP();
  Serial.print("Server IP is: ");
  Serial.println(HTTPS_ServerIP);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  WiFiClient client = server.available();
  if (!client){
    return;
  }
  Serial.println("Client connected :)");

  String request = client.readStringUntil('\r');
  Serial.println(request);
  if (request.indexOf("/OFF") !=-1)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if (request.indexOf("/ON") != -1)
  {
    digitalWrite(LED_BUILTIN, LOW);
  }

  String s = "HTTP/1.1 200 OK\r\n";
s += "Content-Type: text/html\r\n\r\n";
s += "<!DOCTYPE HTML>\r\n<html>\r\n";
s += "<br><input type=\"button\" name=\"b1\" value=\"Turn LED ON\" onclick=\"location.href='/ON'\">";
s += "<br><br><br>";
s += "<br><input type=\"button\" name=\"b2\" value=\"Turn LED OFF\" onclick=\"location.href='/OFF'\">";
s += "</html>\n";

client.flush();
client.print(s);
delay(1);
Serial.println("Client disconnected");
}
