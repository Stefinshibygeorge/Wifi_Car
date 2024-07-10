#define BLED 2
#define ENA 19 // You can change these pin numbers according to your wiring
#define IN1 13
#define IN2 12
#define IN3 26
#define IN4 25
#define ENB 21

#define ENA_ 5 // You can change these pin numbers according to your wiring
#define IN1_ 14 
#define IN2_ 27
#define IN3_ 33
#define IN4_ 32
#define ENB_ 18

#include <WiFi.h>
#include <WebServer.h>

String command;             // String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;

const char* ssid = "ESP32 Car";
WebServer server(80);

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 

  pinMode(ENA_, OUTPUT);
  pinMode(ENB_, OUTPUT);  
  pinMode(IN1_, OUTPUT);
  pinMode(IN2_, OUTPUT);
  pinMode(IN3_, OUTPUT);
  pinMode(IN4_, OUTPUT); 
  
  Serial.begin(115200);
  
  // Connecting WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
  // Starting WEB-server 
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();    
}

void goAhead(){ 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN1_, LOW);
  digitalWrite(IN2_, HIGH);
  analogWrite(ENA, speedCar);
  analogWrite(ENA_, speedCar);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3_, LOW);
  digitalWrite(IN4_, HIGH);
  analogWrite(ENB, speedCar);
  analogWrite(ENB_, speedCar);
}

void goBack(){ 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN1_, HIGH);
  digitalWrite(IN2_, LOW);
  analogWrite(ENA, speedCar);
  analogWrite(ENA_, speedCar);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3_, HIGH);
  digitalWrite(IN4_, LOW);
  analogWrite(ENB, speedCar);
  analogWrite(ENB_, speedCar);
}

void goRight(){ 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN1_, HIGH);
  digitalWrite(IN2_, LOW);
  analogWrite(ENA, speedCar);
  analogWrite(ENA_, speedCar);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3_, LOW);
  digitalWrite(IN4_, HIGH);
  analogWrite(ENB, speedCar);
  analogWrite(ENB_, speedCar);
}

void goLeft(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN1_, LOW);
  digitalWrite(IN2_, HIGH);
  analogWrite(ENA, speedCar);
  analogWrite(ENA_, speedCar);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3_, HIGH);
  digitalWrite(IN4_, LOW);
  analogWrite(ENB, speedCar);
  analogWrite(ENB_, speedCar);
}

void goAheadRight(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN1_, LOW);
  digitalWrite(IN2_, HIGH);
  analogWrite(ENA, speedCar / speed_Coeff);
  analogWrite(ENA_, speedCar / speed_Coeff);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3_, LOW);
  digitalWrite(IN4_, HIGH);
  analogWrite(ENB, speedCar);
  analogWrite(ENB_, speedCar);
}

void goAheadLeft(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN1_, LOW);
  digitalWrite(IN2_, HIGH);
  analogWrite(ENA, speedCar);
  analogWrite(ENA_, speedCar);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3_, LOW);
  digitalWrite(IN4_, HIGH);
  analogWrite(ENB, speedCar / speed_Coeff);
  analogWrite(ENB_, speedCar / speed_Coeff);
}

void goBackRight(){ 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN1_, HIGH);
  digitalWrite(IN2_, LOW);
  analogWrite(ENA, speedCar / speed_Coeff);
  analogWrite(ENA_, speedCar / speed_Coeff);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3_, HIGH);
  digitalWrite(IN4_, LOW);
  analogWrite(ENB, speedCar);
  analogWrite(ENB_, speedCar);
}

void goBackLeft(){ 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN1_, HIGH);
  digitalWrite(IN2_, LOW);
  analogWrite(ENA, speedCar);
  analogWrite(ENA_, speedCar);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3_, HIGH);
  digitalWrite(IN4_, LOW);
  analogWrite(ENB, speedCar / speed_Coeff);
  analogWrite(ENB_, speedCar / speed_Coeff);
}

void stopRobot(){  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN1_, LOW);
  digitalWrite(IN2_, LOW);
  analogWrite(ENA, speedCar);
  analogWrite(ENA_, speedCar);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3_, LOW);
  digitalWrite(IN4_, LOW);
  analogWrite(ENB, speedCar);
  analogWrite(ENB_, speedCar);
}

void loop() {
  server.handleClient();
  
  command = server.arg("State");
  if (command == "F") goAhead();
  else if (command == "B") goBack();
  else if (command == "L") goLeft();
  else if (command == "R") goRight();
  else if (command == "I") goAheadRight();
  else if (command == "G") goAheadLeft();
  else if (command == "J") goBackRight();
  else if (command == "H") goBackLeft();
  else if (command == "0") speedCar = 400;
  else if (command == "1") speedCar = 470;
  else if (command == "2") speedCar = 540;
  else if (command == "3") speedCar = 610;
  else if (command == "4") speedCar = 680;
  else if (command == "5") speedCar = 750;
  else if (command == "6") speedCar = 820;
  else if (command == "7") speedCar = 890;
  else if (command == "8") speedCar = 960;
  else if (command == "9") speedCar = 1023;
  else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}
