#include <SoftwareSerial.h>

SoftwareSerial MyBlue(2, 3); // RX | TX 
String receivedData; // Variável para armazenar os dados recebidos
int LED = 8; 

void setup() {   
  Serial.begin(9600); 
  MyBlue.begin(9600); 
  pinMode(LED, OUTPUT); 
  Serial.println("Ready to connect\nDefault password is 1234 or 000"); 
} 

void loop() { 
  if (MyBlue.available()) { 
    receivedData = MyBlue.readStringUntil('\n'); // Ler a string até encontrar uma quebra de linha
    receivedData.trim(); // Remove espaços em branco no início e no final da string
    Serial.println(receivedData);
    
    if (receivedData == "yes") { 
      digitalWrite(LED, HIGH); 
      Serial.println("LED On"); 
      MyBlue.println("LED is on👍");
    } 
    else if (receivedData == "no") { 
      digitalWrite(LED, LOW); 
      Serial.println("LED Off"); 
      MyBlue.println("LED is off👎");
    } 
    else if (receivedData == "status") {
      if (digitalRead(LED) == HIGH) {
        MyBlue.println("LED is on😱");
        Serial.println("Status sent: LED is on😱");
      } else {
        MyBlue.println("LED is off😱");
        Serial.println("Status sent: LED is off😱");
      }
    }
  } 
  delay(1000);
}
