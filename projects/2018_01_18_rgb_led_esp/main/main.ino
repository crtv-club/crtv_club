#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

const char *ssid = "RGB LED";
const char *password = "ledIsOn";

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

String webpage1 = "<h1 style='text-align: center'>Page 1</h1>";
String webpage2 = "<h1 style='text-align: center'>Page 2</h1>";
String webpage3 = "<h1 style='text-align: center'>Page 3</h1>";
String header = ""
"<header style='font-size: 15px'>"
  "<a href='/1'><button style='width:30%; margin: 5px'>1</button></a>"
  "<a href='/2'><button style='width:30%; margin: 5px'>2</button></a>"
  "<a href='/3'><button style='width:30%; margin: 5px'>3</button></a>"
 "</header>";

void handleRoot1() {
  Serial.println("client view page 1");
  webServer.send(200, "text/html", header + webpage1);
}
void handleRoot2() {
  Serial.println("client view page 2");
  webServer.send(200, "text/html", header + webpage2);
}
void handleRoot3() {
  Serial.println("client view page 3");
  webServer.send(200, "text/html", header + webpage3);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 9600 );
  Serial.println( "=== Started ===" );
  Serial.print( "IP to connected: ");
  Serial.println(apIP );

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid);

  webServer.on("/1", handleRoot1);
  webServer.on("/2", handleRoot2);
  webServer.on("/3", handleRoot3);

  webServer.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  dnsServer.processNextRequest();
  webServer.handleClient();
}
