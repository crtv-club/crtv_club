# RGB led & ESP8266

### Объявление логина и пароля сети WiFi, необходимых для подключения

```
const char *ssid = "RGB LED";
const char *password = "ledIsOn";
```

### Объявление подключаемых пинов, для падачи значений на RGB LED
```
const int pin_red = 0;
const int pin_green = 2;
const int pin_blue = 15;
```

### IP адрес сервера (ввести в адресную строку браузера)
```
IPAddress apIP(192, 168, 1, 1);
```

### Текст, выводимый в браузере web-клиента
```
String webpage = "<canvas id='colorspace'></canvas>";
```

### Описание логики работы приложения на стороне клиента
Переменная ```script``` содержит код на JavaScript, который отрисовывает цветовую палитру и отправляет на сервер POST запрос со значениям выбранного цвета для отображения.

[Скрипты, записанные в данной переменной можно посмотреть в файле script.html](https://github.com/s-kostyuk/crtv_club/blob/rgbled_esp8266/projects/2018_01_18_rgb_led_esp/script.js)


### Хендлер для обработки запросов по адресу 192.168.1.1/
Подает на указанные пины esp8266 полученные значение от клиентаю. Отправляет клиенту строку с ответом.
```
void handleRoot() {
  String red = webServer.arg(0);
  String green = webServer.arg(1);
  String blue = webServer.arg(2);
  
  analogWrite(0, red.toInt());
  analogWrite(2, green.toInt());
  analogWrite(15, blue.toInt());
  webServer.send(200, "text/html", webpage + script);
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


### Бонус.
* [пример многостраничного приложения](https://github.com/s-kostyuk/crtv_club/tree/a6a0ed62261f00abcba2313d7b2450137fc7224a/projects/2018_01_18_rgb_led_esp)

