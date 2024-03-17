  #include <dht.h>
#include <LiquidCrystal.h>

// Motor A connections
int enA = 6;
int in1 = 13;
int in2 = 8;
int reset = 1;

const int trigPin = 9;         
const int echoPin = 10; 

const int DHT11_PIN = 7;         
const int waterPin1 = A0;     

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //lcd pins

const int waterPin2 = A1;      // Replace with the actual analog pin number for tank 2 water level sensor


dht DHT;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//TANK ONE
const float tankmin = 5.0;   // Adjust based on your specific needs
const float tankok = 25.0;    // Adjust based on your specific needs
const float tankmax = 70.0; 
//TANK TWO
const float tank2min = 30.0;   // Adjust based on your specific needs for tank 2
const float tank2max = 700.0;   // Adjust based on your specific needs for tank 2


float distanceVal(int trigPin, int echoPin){              
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);
  Serial.print("Distance: ");
  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration*.0343)/2;
  Serial.println(distance);
  return distance; 
  delay(100); 
  }
  
  
  float tempVal(){
  int chk = DHT.read11(DHT11_PIN); //de setat pin
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  delay(1500);
  return DHT.temperature;
  }
  
  float waterLevel(int waterPin){             
  float val = analogRead(waterPin);    
  return val;             
  }

  void displayTankStatus(float level,float temperature) {
  lcd.clear();
  if (level < tankok) {
    lcd.print("Tank Status:Empty");
  
  } else if (level >= tankmin && level < tankmax) {
    lcd.print("Tank Status: OK");
    
  } else {
    lcd.print("Tank Status:Full");
    
  }
  
  lcd.setCursor(0, 1);  
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
}

  
void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  
  
}

void loop() {
  Serial.print("level1: ");
  float level = waterLevel(waterPin1);
  Serial.println(level);
  float temperature = tempVal();
  displayTankStatus(level, temperature);
  float distance = distanceVal(9, 10);
  Serial.print("level2: ");
  float level2 = waterLevel(waterPin2);
  Serial.println(level2);
  if (distance < 10.0 && level2 <tank2max) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(1000);
  setup();
    
  }
  else{
  analogWrite(enA, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(3000);
  setup();
  
    }


  delay(500);  
}
