#define leftIR A11
#define rightIR A12


#define ENright 48
#define ENleft 52
#define IN1 50
#define IN2 53
#define IN3 51
#define IN4 49

void setup()
{
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
  
  pinMode(ENright, OUTPUT);
  pinMode(ENleft, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);
}

void TurnLeft()
{
  digitalWrite(ENright, LOW);
  digitalWrite(ENleft, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Turning left");
}

void TurnRight()
{
  digitalWrite(ENright, HIGH);
  digitalWrite(ENleft, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Turning right");
}

void goStraight()
{
  digitalWrite(ENright, HIGH);
  digitalWrite(ENleft, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Going Straight");
}

void stop()
{
  digitalWrite(ENright, LOW);
  digitalWrite(ENleft, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Stopping");
}

void loop()
{
  int LeftIR = analogRead(leftIR);
  int RightIR = analogRead(rightIR);

  Serial.print("LEFT : ");
  Serial.print(LeftIR);
  Serial.print("Right : ");
  Serial.println(rightIR);

  delay(500);
  
  if(LeftIR>=900)
  {
    TurnLeft();
  } else if (LeftIR<900 && RightIR>=900)
  {
    TurnRight();
  } else if (LeftIR<900 && RightIR<900)
  {
    goStraight();
  }

  if(LeftIR>900 && RightIR>900)
  {
    stop();
  }
}
