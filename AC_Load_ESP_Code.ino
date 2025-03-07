#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Rafi";
const char* password = "qnh1013hg";

WebServer server(80);

#define LED1  4  // GPIO pin where the LED is connected
#define LED2 18 

void handleRoot() {
  String message = "Send data to /post with 'data' parameter (5 to turn on the LED, 3 to turn off the LED)";
  server.send(200, "text/plain", message);
}

void handlePost() {
  if (server.hasArg("data")) {
    
      String data = server.arg("data");
      Serial.print("Received data: ");
      Serial.println(data);
      
      if (data=="1")
      
       {
         digitalWrite(LED1,HIGH);
         server.send(200, "text/plain", "LED1 is ON");
              
        }
      
      else if (data=="2")

       {
         digitalWrite(LED2,HIGH);
         server.send(200, "text/plain", "LED2 is ON");
        }
       
    
      else if (data=="0")
       {
        digitalWrite(LED1,LOW);
        digitalWrite(LED2,LOW);
        server.send(200, "text/plain", "LEDs are off");
     }
      else 
        server.send(200, "text/plain", "NULL");
    } 
  
  else {
    server.send(400, "text/plain", "No data received");
  }
}

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  pinMode(LED1,OUTPUT); 
  pinMode(LED2,OUTPUT); 

  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/post", HTTP_POST, handlePost);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  server.handleClient();
}
