#include <Servo.h>  //include servo.h library
 
int pos = 0;    
boolean fire = false;
 
#define Left A14    // left sensor
#define Right A13    // right sensor
#define Forward A15 //front sensor

#define ENL 2       // left motor
#define ENR 3       // left motor
#define IN1 4       // right motor
#define IN3 5       // right motor
#define pump 6
 
void setup()
{
    pinMode(Left, INPUT);
    pinMode(Right, INPUT);
    pinMode(Forward, INPUT);
    pinMode(ENL, OUTPUT);
    pinMode(ENR, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(pump, OUTPUT);

    Serial.begin(9600);
}
 
void put_off_fire()
{
    delay (500);

    Serial.println("Putting off fire");
    
    digitalWrite(ENL, LOW);
    digitalWrite(ENR, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN3, LOW);
    
    digitalWrite(pump, HIGH);
    delay(500);
    
    fire=false;
}

void loop()
{
    Serial.print("Left : ");
    Serial.print(analogRead(Left));
    Serial.print("Right : ");
    Serial.print(analogRead(Right));
    Serial.print("Forward : ");
    Serial.println(analogRead(Forward));
    if (analogRead(Left) > 900 && analogRead(Right) > 900  && analogRead(Forward) > 900) //No fire
    {
      
      digitalWrite(ENL, LOW);
      digitalWrite(ENR, LOW);
      digitalWrite(IN1, LOW);
      digitalWrite(IN3, LOW);
      Serial.println("No fire");
      
    }

    else if (analogRead(Forward) < 900 && analogRead(Left)>500 && analogRead(Right)>500) //Distant fire infront
    {
        
      digitalWrite(ENL, HIGH);
      digitalWrite(ENR, HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN3, HIGH);
      Serial.println("Distant Fire infront");
      
    }
    
    else if ( analogRead(Forward) < 500 && ((analogRead(Left) - analogRead(Right))<150 || (analogRead(Right) - analogRead(Left))<150 )) //Fire infront
    {
      digitalWrite(ENL, HIGH);
      digitalWrite(ENR, HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN3, HIGH);
      Serial.println("Fire infront");
      put_off_fire();
    }
    
    else if (analogRead(Left)<700 && analogRead(Right)>700 && analogRead(Forward)>700)  //Fire towards left
    {
      digitalWrite(ENL, HIGH);
      digitalWrite(ENR, LOW);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN3, LOW);
      Serial.println("Fire towards left");
    }
    
    else if (analogRead(Left)>700 && analogRead(Right)<700 && analogRead(Forward)>700) //Fire towards right
    {
      digitalWrite(ENL, LOW);
      digitalWrite(ENR, HIGH);
      digitalWrite(IN1, LOW);
      digitalWrite(IN3, HIGH);
      Serial.println("Fire towards right");
    }
    
    delay(100);
}
