#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>



const int trigPin = D7;  
const int echoPin = D8;  
float duration;
int distance;

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
  
 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 


 
 
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
   

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;

    Serial.print("Distance: ");
    Serial.println(distance);
    delay(2000);




  
  page = "<h3>Distance:</h3> <h4>"+String(distance)+"</h4>";
  server.handleClient();

  
}
