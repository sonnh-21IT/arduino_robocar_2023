#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial HC05(12,13);//RX,TX
const int IN1 = 6;
const int IN2 = 7;
const int IN3 = 8;
const int IN4 = 9;

char status;
int mode=0;
Servo servo_quay,servo_1,servo_2,servo_gap;
void setup() {
  // put your setup code here, to run once:
  HC05.begin(9600);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  servo_quay.attach(4);
  servo_1.attach(5);
  servo_2.attach(10);
  servo_gap.attach(11);

  servo_quay.write(90);
  servo_1.write(90);
  servo_2.write(90);
  servo_gap.write(45);
}
void forward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void backward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void mstop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void turnright(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void turnleft(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void servo_driver(Servo servo,int pos,int reg){
  servo.write(pos+reg);
}
void loop() {
  // put your main code here, to run repeatedly:
  if(HC05.available()){
    status = HC05.read();
    switch(status){
      case 'F':{
        if(mode==1){
          
          break;
        }else{
          forward();
          break;
        }
      }
      case 'B':{
        backward();
        break;
      }
      case 'H':
      case 'G':
      case 'L':{
        if(mode==1){
          servo_driver(servo_quay,servo_quay.read(),-3);
          break;
        }else{
          turnleft();
          break;
        }
      }
      case 'J':
      case 'I':
      case 'R':{
        if(mode==1){
          //quay
          servo_driver(servo_quay,servo_quay.read(),3);
          break;
        }else{
          turnright();
          break;
        }
      }
      case 'S':{
        mstop();
        break;
      }
      case 'X':{
        mode=1;
        break;
      }
      case 'x':{
        mode=0;
        break;
      }
    }
    if(status=='1'||status=='2'||status=='3'||status=='4'||status=='5'||status=='6'||status=='7'||status=='8'||status=='9'||status=='q'){
      servo_driver(servo_gap,servo_gap.read(),-3);
    }
    if(status=='0'){
      if(servo_gap.read()>=45){
        servo_driver(servo_gap,servo_gap.read(),3);
      }
    }
  }
}