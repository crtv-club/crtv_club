#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

const char *ssid = "RGB LED";
const char *password = "ledIsOn";
const int pin_red = 0;
const int pin_green = 2;
const int pin_blue = 15;
const byte DNS_PORT = 53;

IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

String webpage = "<canvas id='colorspace'></canvas>";
String script = "<script type='text/javascript'>(function () {var canvas = document.getElementById('colorspace');var ctx = canvas.getContext('2d');function drawCanvas() {var colours = ctx.createLinearGradient(0, 0, window.innerWidth, 0);for(var i=0; i <= 360; i+=10) {colours.addColorStop(i/360, 'hsl(' + i + ', 100%, 50%)');}ctx.fillStyle = colours;ctx.fillRect(0, 0, window.innerWidth, window.innerHeight);var luminance = ctx.createLinearGradient(0, 0, 0, ctx.canvas.height);luminance.addColorStop(0, '#ffffff');luminance.addColorStop(0.05, '#ffffff');luminance.addColorStop(0.5, 'rgba(0,0,0,0)');luminance.addColorStop(0.95, '#000000');luminance.addColorStop(1, '#000000');ctx.fillStyle = luminance;ctx.fillRect(0, 0, ctx.canvas.width, ctx.canvas.height);}var eventLocked = false;function handleEvent(clientX, clientY) {if(eventLocked) {return;}function colourCorrect(v) {return Math.round(v*1024/256);}var data = ctx.getImageData(clientX, clientY, 1, 1).data;var params = ['r=' + colourCorrect(data[0]),'g=' + colourCorrect(data[1]),'b=' + colourCorrect(data[2])].join('&');var req = new XMLHttpRequest();req.open('POST', '?' + params, true);req.send();eventLocked = true;req.onreadystatechange = function() {if(req.readyState == 4) {eventLocked = false;}}}canvas.addEventListener('click', function(event) {handleEvent(event.clientX, event.clientY, true);}, false);canvas.addEventListener('touchmove', function(event){handleEvent(event.touches[0].clientX, event.touches[0].clientY);}, false);function resizeCanvas() {canvas.width = window.innerWidth;canvas.height = window.innerHeight;drawCanvas();}window.addEventListener('resize', resizeCanvas, false);resizeCanvas();drawCanvas();document.ontouchmove = function(e) {e.preventDefault()};})();</script>";

void handleRoot() {
  int red = webServer.arg(0).toInt();
  int green = webServer.arg(1).toInt();
  int blue = webServer.arg(2).toInt();

  analogWrite(pin_red, red);
  analogWrite(pin_green, green);
  analogWrite(pin_blue, blue);
  webServer.send(200, "text/html", webpage + script);
}

void setup() {
  pinMode(pin_red, OUTPUT);
  pinMode(pin_green, OUTPUT);
  pinMode(pin_blue, OUTPUT);

  analogWrite(pin_red, 1023);
  analogWrite(pin_green, 1023);
  analogWrite(pin_blue, 1023);

  Serial.begin( 9600 );

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid);

  webServer.on("/", handleRoot);
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
