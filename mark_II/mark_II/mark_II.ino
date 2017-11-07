#include <ESP8266WiFi.h>

WiFiServer server(80);

//Ultrasonic sensor variables
const int trigPin = 2;
const int echoPin = 14;
const int LED_1 = 04;
const int LED_2 = 05;
long duration;
long distance;

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
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
}

void ultrasonic(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  //TODO: Send response via ?
  Serial.print("Distance: ");
  Serial.println(distance);
  //return distance;
}

void loop() {
  
  WiFiClient client = server.available();
  if (!client){return;}
  Serial.println("Client connected :)");
  String request = client.readStringUntil('\r');
  Serial.println(request);
  if (request.indexOf("/110") !=-1){digitalWrite(LED_BUILTIN, HIGH);}
  else if (request.indexOf("/111") != -1){digitalWrite(LED_BUILTIN, LOW);}
  else if (request.indexOf("/011") != -1){digitalWrite(LED_1, HIGH);}
  else if (request.indexOf("/010") != -1){digitalWrite(LED_1, LOW);}
  else if (request.indexOf("/101") != -1){digitalWrite(LED_2, HIGH);}
  else if (request.indexOf("/100") != -1){digitalWrite(LED_2, LOW);}
  else if (request.indexOf("/READ") != -1){ultrasonic();}
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<br><input type=\"button\" name=\"b1\" value=\"SWITCH 01 ON\" onclick=\"location.href='/011'\">";
  s += "<br>";
  s += "<br><input type=\"button\" name=\"b1\" value=\"SWITCH 01 OFF\" onclick=\"location.href='/010'\">";
  s += "<br><br>";
  s += "<br><input type=\"button\" name=\"b1\" value=\"SWITCH 02 ON\" onclick=\"location.href='/101'\">";
  s += "<br>";
  s += "<br><input type=\"button\" name=\"b1\" value=\"SWITCH 02 OFF\" onclick=\"location.href='/100'\">";
  s += "<br><br>";
  s += "<br><input type=\"button\" name=\"b1\" value=\"SWITCH 03 ON\" onclick=\"location.href='/111'\">";
  s += "<br>";
  s += "<br><input type=\"button\" name=\"b1\" value=\"SWITCH 03 OFF\" onclick=\"location.href='/110'\">";
  s += "<br><br>";
  String distance_s = String(distance);
  s += "<br><input type=\"button\" name=\"b3\" value=\"READ WATER LEVEL\" onclick=\"location.href='/READ'\"><label>    ";
  s += distance_s;
  s += "</label>";
  s += "</html>\n";
  
  //printf("Entero es: %d",n);
  client.flush();
  client.print(s);
  delay(1);
  Serial.println("Client disconnected");
}
