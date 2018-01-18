# RGB led & ESP8266

коммит с примером многостраничного приложения на esp8266

### Создание строковыъ переменных
Первая страница
```
String webpage1 = "<h1 style='text-align: center'>Page 1</h1>";
```

Вторая страница
```
String webpage2 = "<h1 style='text-align: center'>Page 2</h1>";
```

Третья страница
```
String webpage3 = "<h1 style='text-align: center'>Page 3</h1>";
```

Общий заголовок для всех странц
```
String header = ""
"<header style='font-size: 15px'>"
  "<a href='/1'><button style='width:30%; margin: 5px'>1</button></a>"
  "<a href='/2'><button style='width:30%; margin: 5px'>2</button></a>"
  "<a href='/3'><button style='width:30%; margin: 5px'>3</button></a>"
 "</header>";
```

### Обработчики для кадой страницы
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

### Подписание обработчиков на запросы
  webServer.on("/1", handleRoot1);
  webServer.on("/2", handleRoot2);
  webServer.on("/3", handleRoot3);
