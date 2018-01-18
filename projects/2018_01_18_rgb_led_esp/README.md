# RGB led & ESP8266

### Объявление логина и пароля сети WiFi, необходимых для подключения

```
const char *ssid = "RGB LED";
const char *password = "ledIsOn";
```

### IP адрес сервера (ввести в адресную строку браузера)
```
IPAddress apIP(192, 168, 1, 1);
```

### Текст, выводимый в браузере web-клиента
```
String webpage = "<h1 style='text-align: center; margin-top: 45vh'>Hello world!</h1>";
```

### Хендлер для обработки запросов по адресу 192.168.1.1/
Отправляет клиенту мтроку с ответом
```
void handleRoot() {
    ...
}
```

### Создание точки подключения
```
void setup() {
  ...
  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid);

  webServer.on("/", handleRoot);

  webServer.begin();
}
```

### Запуск dns сервера и запуск слушателя подключения клиентов
```
void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
```