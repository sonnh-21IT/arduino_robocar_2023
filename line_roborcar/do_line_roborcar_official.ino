
//motor left
const int ENA = 10;
const int IN1 = 6;
const int IN2 = 7;
//motor right
const int IN3 = 8;
const int IN4 = 9;
const int ENB = 5;

const int Pin_ss1 = A0; // Analog output pin that the LED is attached to
const int Pin_ss2 = A1;
const int Pin_ss3 = A2;
const int Pin_ss4 = A3;
const int Pin_ss5 = A4;

const int max_speed=255;
int IN_line = 0, In_line_last = 0, mode = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);

  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENB,OUTPUT);

  //motor left
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  //motor right
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);  

  //speed
  analogWrite(ENA, max_speed);
  analogWrite(ENB, max_speed);

  pinMode(Pin_ss1, INPUT);//Set chân cảm biến 1 là input
  pinMode(Pin_ss2, INPUT);//Set chân cảm biến 2 là input
  pinMode(Pin_ss3, INPUT);//Set chân cảm biến 3 là input
  pinMode(Pin_ss4, INPUT);//Set chân cảm biến 4 là input
  pinMode(Pin_ss5, INPUT);//Set chân cảm biến 5 là input

  Serial.begin(9600);
}

void loop() {
  In_line_last = IN_line;
  IN_line = In_SenSor();
  if (IN_line != In_line_last)
  {
    if (In_line_last != 5)
    {
      robotMover(IN_line);
    }
  }
}
void left(){
  //motor left
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  //motor right
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void right(){
  //motor left
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  //motor right
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void backward(){
  //motor left
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  //motor right
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void forward(){
  //motor left
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  //motor right
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void mstop(){
  //motor left
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  //motor right
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
void robotMover (int line)
{
  switch (line)
  {
    case -1:// sang trai
      {
        mode=-1;
        left();
        break;
      }
    case 0:
      {
        forward();
        break;
      }
    case 1:// rẽ phai
      {
        mode=1;
        right();
        break;
      };
      case 5:
      {
        mode=5;
        mstop();
        break;
      };
  }
}
int In_SenSor()
{
  int ss1 = digitalRead(Pin_ss1);
  int ss2 = digitalRead(Pin_ss2);
  int ss3 = digitalRead(Pin_ss3);
  int ss4 = digitalRead(Pin_ss4);
  int ss5 = digitalRead(Pin_ss5);

  bool a = ss1 == 1;
  bool b = ss2 == 1;
  bool c = ss3 == 1;
  bool d = ss4 == 1;
  bool e = ss5 == 1;

  if ((a && !b && !c && !d && e) || (a && !b && !c && d && e) || (a && b && !c && !d && e) || (a && b && !c && d && e) || (a && !b && c && d && e) || (a && b && c && !d && e)) {
    if ((a && b && c && !d && e) || (a && b && !c && !d && e)) {
    mode = 1;
    } else if ((a && !b && c && d && e) || (a && !b && !c && d && e)) {
    mode = -1;
    }
    return 0;
  } else if ((a && b && c && d && !e) || (a && b && c && !d && !e)||(a && !b && c && !d && !e) || (a && !b && !c && !d && !e) || (a && !b && c && !d && !e) || (a && b && c && !d && !e) || (a && !b && c && d && !e)) {
    return 1;
  } else if ((!a && b && c && d && e) || (!a && !b && c && d && e)||(!a && !b && !c && d && e) || (!a && !b && !c && !d && e) || (!a && !b && c && !d && e) || (!a && !b && c && d && e) || (a && b && !c && d && !e)) {
    return -1;
  } else if ((a && !b && c && !d && e) || (a && b && c && d && e)) {
    return mode;
  } else if ((!a && !b && !c && !d && !e) || (!a && !b && c && !d && !e)) {
    return 5;
  }
}
