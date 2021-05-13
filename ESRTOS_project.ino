#include<Arduino_FreeRTOS.h>
const int pingPin = 2; // Trigger Pin of right Ultrasonic Sensor
const int echoPin = 3; // Echo Pin of right Ultrasonic Sensor
const int pingPin2 = 4; // Trigger Pin of left Ultrasonic Sensor
const int echoPin2 = 5; // Echo Pin of left Ultrasonic Sensor
const int in1 = 6;
const int in2 = 7;
const int in3 = 8;
const int in4 = 9;
const int m1 = 10; // PWM right
const int m2 = 11; // PWM left
long duration, cm, duration2, cm2;
void forward();
void right();
void left();
void backward();

void task1(void *param);
void task2(void *param);
long microsecondsToCentimeters(long microseconds);

TaskHandle_t task_handle1;
TaskHandle_t task_handle2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  xTaskCreate(task1,"Task1",100,NULL,1,&task_handle1);
  xTaskCreate(task2,"Task2",100,NULL,1,&task_handle2);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void task1(void * param){
  (void) param;
  while(1){
    Serial.print("Running Task 1\n"); 
    
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    cm = microsecondsToCentimeters(duration);
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    
    pinMode(pingPin2, OUTPUT);
    digitalWrite(pingPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin2, LOW);
    pinMode(echoPin2, INPUT);
    duration2 = pulseIn(echoPin2, HIGH);
    cm2 = microsecondsToCentimeters(duration2);
    Serial.print(cm2);
    Serial.print("cm");
    Serial.println();
   
    vTaskDelay(50/portTICK_PERIOD_MS);
  }
}

void task2(void * param){
  (void) param;
  while(1){
    Serial.print("Running Task 2\n");
    if (cm > 60 && cm2 > 60){
      forward();
      Serial.print("Forward");
    }
    else if (cm > 30 && cm2 > 30 && (cm <= 60 || cm2 <= 60)){
      forwardslow();
      Serial.print("Forward slow");
    }
    else if (cm > 30 && cm2 <= 30){
      right();
      Serial.print("right");
    }
    else if (cm <= 30 && cm2 > 30){
      left();
      Serial.print("left");
    }
    else if (cm <= 30 && cm2 <= 30){
      backward();
      Serial.print("backward");
      changedirection();
      Serial.print("change direction");
    }

    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds * 0.034 / 2;
}


void forward(){
  analogWrite(m1,100);
  analogWrite(m2,100);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void forwardslow(){
  analogWrite(m1,80);
  analogWrite(m2,80);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void left(){
  analogWrite(m1,80);
  analogWrite(m2,0);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void right(){
  analogWrite(m1,0);
  analogWrite(m2,80);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void backward(){
  analogWrite(m1,80);
  analogWrite(m2,80);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

void changedirection(){
  analogWrite(m1,80);
  analogWrite(m2,80);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
