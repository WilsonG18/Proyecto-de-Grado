#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

WiFiClient client;

char* ssid = "Your_WiFi_Network";
char* password = "Your_WiFi_Password";

ESP8266WebServer server(80);

bool EngineStatus = false;

void setup() {
  Serial.begin(9600);
  pinMode(D4, OUTPUT);

  WiFi.begin(ssid, password);

  server.on("/", handle_OnConnect);
  server.on("/engineOn", handle_EngineOn);
  server.on("/engineOff", handle_EngineOff);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(EngineStatus));
}

void handle_EngineOn() {
  EngineStatus = true;
  Serial.println("1");
  digitalWrite(D4, LOW);
  server.send(200, "text/html", SendHTML(EngineStatus)); 
}

void handle_EngineOff() {
  EngineStatus = false;
  Serial.println("0");
  digitalWrite(D4, HIGH);
  server.send(200, "text/html", SendHTML(EngineStatus)); 
}

String SendHTML(bool engineStatus){
  String html = "<html><head><style>\n";
  html += ".BtnOn {width: 100%; height: 60px; padding: 10px; text-align: center; background-color: green; color: white;}\n";
  html += ".BtnOff {width: 100%; height: 60px; padding: 10px; text-align: center; background-color: red; color: white;}\n";
  html += "body {padding: 10%; background-color: gray;}\n";
  html += "p {color: white;}\n";
  html += "</style></head><body><p> Status: \n";
  if(engineStatus)
  {
    html += "ON\n";
  }
  else
  {
    html += "OFF\n";
  }
  html += "</p>";
  html += "<a class=\"BtnOn\" href=\"/engineOn\">ON</a>";
  html += "<a class=\"BtnOff\" href=\"/engineOff\">OFF</a>";
  html += "</body></html>";
  return html;
}
