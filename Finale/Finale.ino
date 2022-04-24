#include <Wire.h>  // Wire library - used for I2C communication
#include <Servo.h>

Servo pitchServo;
Servo rollServo;

int ADXL345 = 0x53; // The ADXL345 sensor I2C address
float X_out, Y_out, Z_out;  // Outputs
float roll,pitch;
boolean fire = false;

#define leftIR A11
#define rightIR A12

#define Left A14    // left sensor
#define Right A13    // right sensor
#define Forward A15 //front sensor

#define ENright 48
#define ENleft 52
#define IN1 50
#define IN2 53
#define IN3 51
#define IN4 49

#define pump 35
void setup()
{
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);

  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  
  pinMode(ENright, OUTPUT);
  pinMode(ENleft, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(pump, OUTPUT);

  pitchServo.attach(9);
  rollServo.attach(10);
  
  Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
 
  Wire.begin(); // Initiate the Wire library
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // Bit D3 High for measuring enable (8dec -> 0000 1000 binary)
  Wire.endTransmission();
  delay(10);
  //Off-set Calibration
  //X-axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x1E);
  Wire.write(1);
  Wire.endTransmission();
  delay(10);
  //Y-axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x1F);
  Wire.write(-2);
  Wire.endTransmission();
  delay(10);
  //Z-axis
  Wire.beginTransmission(ADXL345);
  Wire.write(0x20);
  Wire.write(-9);
  Wire.endTransmission();
  delay(10);
  
  Serial.begin(9600);

  
}

void put_off_fire()
{
    delay (500);

    Serial.println("Putting off fire");
    
    digitalWrite(ENleft, LOW);
    digitalWrite(ENright, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN3, LOW);
    
    digitalWrite(pump, HIGH);
    delay(500);
    digitalWrite(pump, LOW);
    
    fire=false;
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

void followLine()
{
  int LeftIR = analogRead(leftIR);
  int RightIR = analogRead(rightIR);
    
  delay(1000);

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
void loop()
{
  followLine();
  // === Read acceleromter data === //
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  X_out = ( Wire.read() | Wire.read() << 8); // X-axis value
  X_out = X_out / 256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  X_out = X_out - 0.12;
  Y_out = ( Wire.read() | Wire.read() << 8); // Y-axis value
  Y_out = Y_out / 256;
  Y_out = Y_out + 0.07;
  Z_out = ( Wire.read() | Wire.read() << 8); // Z-axis value
  Z_out = Z_out / 256;
  Z_out = Z_out - 1.93;
  // Calculate Roll and Pitch (rotation around X-axis, rotation around Y-axis)
  roll = atan(Y_out / sqrt(pow(X_out, 2) + pow(Z_out, 2))) * 180 / PI;
  pitch = atan(-1 * X_out / sqrt(pow(Y_out, 2) + pow(Z_out, 2))) * 180 / PI;

  Serial.print("Left : ");
  Serial.print(analogRead(Left));
  Serial.print("Right : ");
  Serial.print(analogRead(Right));
  Serial.print("Forward : ");
  Serial.println(analogRead(Forward));
  
    if (analogRead(Left) > 900 && analogRead(Right) > 900  && analogRead(Forward) > 900) //No fire
    {
      
      goStraight();
      Serial.println("No fire");
      
    }

    else if (analogRead(Forward) < 900 && analogRead(Forward) > 500 &&analogRead(Left)>500 && analogRead(Right)>500) //Distant fire infront
    {
        
      goStraight();
      Serial.println("Distant Fire infront");
      
    }
    
    else if ( analogRead(Forward) < 500) //Fire infront
    {
      stop();
      Serial.println("Fire infront");
      put_off_fire();
    }
    
    else if (analogRead(Left)<700 && analogRead(Right)>700 && analogRead(Forward)>700)  //Fire towards left
    {
      TurnLeft();
      Serial.println("Fire towards left");
    }
    
    else if (analogRead(Left)>700 && analogRead(Right)<700 && analogRead(Forward)>700) //Fire towards right
    {
      TurnRight();
      Serial.println("Fire towards right");
    }
}
