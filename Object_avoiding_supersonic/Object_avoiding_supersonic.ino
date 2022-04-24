int trigPin = 9;      // trig pin of HC-SR04
int echoPin = 10;     // Echo pin of HC-SR04

#define ENL 2       // left motor
#define ENR 3       // left motor
#define IN1 4       // right motor
#define IN3 5       // right motor

long duration, distance;

void setup() {

  pinMode(ENL, OUTPUT);      // set Motor pins as output
  pinMode(ENR, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN3, OUTPUT);
  
  pinMode(trigPin, OUTPUT);         // set trig pin as output
  pinMode(echoPin, INPUT);          //set echo pin as input to capture reflected waves

  Serial.begin(9600);
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);     // send waves for 10 us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH); // receive reflected waves
  distance = duration / 58.2;   // convert to distance
  delay(10);
    
  if (distance > 19)            
  {
    digitalWrite(ENL, HIGH);                    // move forward
    digitalWrite(ENR, HIGH);
    digitalWrite(IN1, HIGH);                                
    digitalWrite(IN3, HIGH);

    Serial.println("No object detected");
  }

  if (distance < 18)
  {
    digitalWrite(ENL, LOW);  //Stop                
    digitalWrite(ENR, LOW);
    digitalWrite(IN1, LOW);                                
    digitalWrite(IN3, LOW);

    Serial.println("Stopping");
    
    delay(500);
    digitalWrite(ENL, LOW);      //Move right         
    digitalWrite(ENR, HIGH);
    digitalWrite(IN1, LOW);                                
    digitalWrite(IN3, HIGH);

    Serial.println("Moving right");
    
    delay(500);
    digitalWrite(ENL, HIGH);                    // move forward
    digitalWrite(ENR, HIGH);
    digitalWrite(IN1, HIGH);                                
    digitalWrite(IN3, HIGH);

    Serial.println("Moving forward");
    
    delay(500);
    digitalWrite(ENL, HIGH);     //Move left                
    digitalWrite(ENR, LOW);
    digitalWrite(IN1, HIGH);                                
    digitalWrite(IN3, LOW);

    Serial.println("Moving left");
    
    delay(500);
    digitalWrite(ENL, HIGH);                    // move forward
    digitalWrite(ENR, HIGH);
    digitalWrite(IN1, HIGH);                                
    digitalWrite(IN3, HIGH);

    Serial.println("Moving forward");
    
    delay(500); 
    digitalWrite(ENL, HIGH);     //Move left                
    digitalWrite(ENR, LOW);
    digitalWrite(IN1, HIGH);                                
    digitalWrite(IN3, LOW);

    Serial.println("Moving left");
      
    delay(500);
    digitalWrite(ENL, HIGH);                    // move forward
    digitalWrite(ENR, HIGH);
    digitalWrite(IN1, HIGH);                                
    digitalWrite(IN3, HIGH);

    Serial.println("Moving forward")
    
    delay(500);
    digitalWrite(ENL, LOW);      //Move right         
    digitalWrite(ENR, HIGH);
    digitalWrite(IN1, LOW);                                
    digitalWrite(IN3, HIGH);

    Serial.println("Moving right")
    delay(500);

    Serial.println("Object avoiding complete")
  }

}
