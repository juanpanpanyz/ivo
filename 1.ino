#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "IoTB";
const char* password = "inventaronelVAR";

// Pines de los relés
const int relay1Pin = 2;
const int relay2Pin = 15;

// Crear el servidor web en el puerto 80
WebServer server(80);

void handleRoot() {
  // HTML que se envía al navegador
  String html = "<html>\
  <head>\
    <title>Control de Relés</title>\
    <meta charset='utf-8'>\
    <style>body { font-family: Arial; text-align: center; margin-top: 50px; }</style>\
  </head>\
  <body>\
    <h1>Control de Relés con ESP32</h1>\
    <button onclick=\"location.href='/relay1/on'\">Encender Relé 1</button>\
    <button onclick=\"location.href='/relay1/off'\">Apagar Relé 1</button>\
    <br><br>\
    <button onclick=\"location.href='/relay2/on'\">Encender Relé 2</button>\
    <button onclick=\"location.href='/relay2/off'\">Apagar Relé 2</button>\
  </body>\
  </html>";

  // Enviar la respuesta HTML
  server.send(200, "text/html", html);
}

// Función para encender y apagar relé 1
void handleRelay1On() {
  digitalWrite(relay1Pin, HIGH);
  server.send(200, "text/plain", "Relé 1 encendido");
}

void handleRelay1Off() {
  digitalWrite(relay1Pin, LOW);
  server.send(200, "text/plain", "Relé 1 apagado");
}

// Función para encender y apagar relé 2
void handleRelay2On() {
  digitalWrite(relay2Pin, HIGH);
  server.send(200, "text/plain", "Relé 2 encendido");
}

void handleRelay2Off() {
  digitalWrite(relay2Pin, LOW);
  server.send(200, "text/plain", "Relé 2 apagado");
}

void setup() {
  Serial.begin(115200);

  // Configurar pines de los relés como salida
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);

  // Inicialmente, los relés estarán apagados
  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay2Pin, LOW);

  // Conectar a la red WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a la red WiFi");
  Serial.println(WiFi.localIP()); // Imprimir la IP del ESP32

  // Definir las rutas del servidor web
  server.on("/", handleRoot); // Ruta principal que sirve la página HTML
  server.on("/relay1/on", handleRelay1On);   // Ruta para encender relé 1
  server.on("/relay1/off", handleRelay1Off); // Ruta para apagar relé 1
  server.on("/relay2/on", handleRelay2On);   // Ruta para encender relé 2
  server.on("/relay2/off", handleRelay2Off); // Ruta para apagar relé 2

  // Iniciar el servidor
  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  server.handleClient(); // Manejar solicitudes del cliente web
}
