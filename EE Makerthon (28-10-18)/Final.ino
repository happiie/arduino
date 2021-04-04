#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#define DHTTYPE DHT11 
#include "DHT.h"
#define dht_dpin D3
DHT dht(dht_dpin, DHTTYPE); 

// Replace with your network credentials
const char* ssid = "Qwer";
const char* password = "88888888";
 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
  
void setup(void){
  
  //the HTML of the web page
 // page = "<h1>Sensor to Node MCU Web Server</h1><h3>Data:</h3> <h4>"+String(t)+"</h4>";
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
  
  dht.begin();
  pinMode(D0,OUTPUT);
 
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    delay(800);


  

  digitalWrite(D0, HIGH);  
  page = "<h1>Sensor to Node MCU Web Server</h1><h3>Temperature:</h3> <h4>"+String(t)+"</h4><h3>Humidity:</h3> <h4>"+String(h)+"</h4>";
  server.handleClient();

}
