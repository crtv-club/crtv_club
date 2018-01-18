#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

const char *ssid = "RGB LED";
const char *password = "ledIsOn";

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

String webpage = "<h1 style='text-align: center; margin-top: 45vh'>Hello world!</h1>";

int count = 0;

void handleRoot() {
  count = count + 1;
  Serial.print("client ");
  Serial.println(count);
  webServer.send(200, "text/html", webpage);
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

  webServer.on("/", handleRoot);

  webServer.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  dnsServer.processNextRequest();
  webServer.handleClient();
}
