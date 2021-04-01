#define IR_USE_TIMER1

#include <IRremote.h>
#include <Servo.h>

int RECV_PIN = 12; // define input pin on Arduino 
IRrecv irrecv(RECV_PIN); 
decode_results results; // decode_results class is defined in IRremote.h

Servo myServo;

const int LED_ON = 3;
const int LED_GREEN = 4;
const int LED_BLUE = 5;
const int LED_WHITE = 6;

const int BUZZ = 7;

void sing(int times) {
  digitalWrite(BUZZ, HIGH);
  delay(50);
  
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZ, LOW);
    delay(500);
    digitalWrite(BUZZ, HIGH);
    delay(500);
  }
}

void food(int amount){

  sing(amount);

  int del = 0;

  const int POS_MAX = 90;

  switch(amount){
    case 1:
      del = 200;
      break;
    case 2:
      del = 500;
      break;
    case 3:
      del = 1000;
      break;
    default:
      Serial.println("Illegal amount selected");
      del = '0';
  }

    myServo.write(0);
    delay(100);

    delay(del);

    myServo.write(180);
    delay(100);
}

void food2(int amount){

  sing(amount);

  int del = 0;
  const int POS_MAX = 90;
  del = 700;

  for (int i = 0; i < amount; i++) {
    myServo.write(0);

    delay(del);

    myServo.write(180);
    delay(del);
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  irrecv.enableIRIn(); 
  myServo.attach(9); 
  
  pinMode(LED_ON, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);

  pinMode(BUZZ, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(LED_ON, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_WHITE, LOW);

  digitalWrite(BUZZ, HIGH);

  myServo.write(180);
  delay(500);

  long int flag = 0; 

  if (irrecv.decode()) {
    irrecv.printResultShort(&Serial);
    Serial.println();
    // Serial.println(irrecv.results.value); 

    flag = irrecv.results.value;
    // Receive the next value 

    irrecv.resume(); 
  }

  if (flag == 16738455){ 
    Serial.println("Will pour a small amount of food");
    digitalWrite(LED_WHITE, HIGH);
    food2(1);
 } 
 else if (flag == 16750695){
    Serial.println("Will pour a medium amount of food");
    digitalWrite(LED_BLUE, HIGH);
    food2(2);
 }
 else if (flag == 16756815){
  Serial.println("Will pour a large amount of food");
  digitalWrite(LED_GREEN, HIGH); 
  food2(3);
 }
 else{ 
   // Serial.println("Currently not active");
 }

   delay(100);
  //16738455 = 1
  //16750695 = 2
  //16756815 = 3
}
