#include <WiFi.h>

// Configura los datos de la red WiFi
const char* ssid = "iotB";
const char* password = "inventaronelVAR";

// Pines para los relés
const int relayPin1 = 2;  // Pin D2 (GPIO2)

// Crea el objeto del servidor en el puerto 80
WiFiServer server(80);

void setup() {
  // Inicia el puerto serie
  Serial.begin(115200);

  // Configura los pines de los relés como salida
  pinMode(relayPin1, OUTPUT);
  
  // Apaga los relés al inicio
  digitalWrite(relayPin1, HIGH);  // Relé normalmente abierto

  // Conecta a la red Wi-Fi
  Serial.println("Conectando a la red WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }
  
  Serial.println("Conectado a la red WiFi");
  Serial.println(WiFi.localIP());
  
  // Inicia el servidor web
  server.begin();
}

void loop() {
  // Escucha a los clientes del servidor web
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Cliente conectado");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    
    // Comandos para encender/apagar los relés
    if (request.indexOf("/relay1/on") != -1) {
      digitalWrite(relayPin1, LOW);  // Enciende el relé 1
    }
    if (request.indexOf("/relay1/off") != -1) {
      digitalWrite(relayPin1, HIGH);  // Apaga el relé 1
    }
   
  // HTML simple para la interfaz web
    client.println("<html>");
    client.println("<head><title>Control de Relé ESP32</title></head>");
    client.println("<body><h1>Controla los Relés</h1>");
    client.println("<p><a href=\"/relay1/on\"><button>Encender Relé 1</button></a>");
    client.println("<a href=\"/relay1/off\"><button>Apagar Relé 1</button></a></p>");
    
    client.println();
    client.stop();
    Serial.println("Cliente desconectado");
  }
}
