#define IR 6

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

  pinMode(IR, INPUT);
}

void loop() {

  int distance = analogRead(IR);
  delay(10);
    
  if (distance > 19)            
  {
    digitalWrite(ENL, HIGH);                    // move forward
    digitalWrite(ENR, HIGH);
    digitalWrite(IN1, HIGH);                                
    digitalWrite(IN3, HIGH);                                                       
  }

  if (distance < 18)
  {
    digitalWrite(ENL, LOW);      //Stop                
    digitalWrite(ENR, LOW);
    digitalWrite(IN1, LOW);                                
    digitalWrite(IN3, LOW);
    delay(500);
    digitalWrite(ENL, LOW);      //Move right         
    digitalWrite(ENR, HIGH);
    digitalWrite(IN1, LOW);                                
    digitalWrite(IN3, HIGH);
    delay(500);
    digitalWrite(ENL, HIGH);                    // move forward
    digitalWrite(ENR, HIGH);
    digitalWrite(IN1, HIGH);                                
    digitalWrite(IN3, HIGH);
    delay(500);
    digitalWrite(ENL, HIGH);     //Move left                
    digitalWrite(ENR, LOW);
    digitalWrite(IN1, HIGH);                                
    digitalWrite(IN3, LOW);  
    delay(500);
    digitalWrite(ENL, HIGH);                    // move forward
    digitalWrite(ENR, HIGH);
    digitalWrite(IN1, HIGH);                                
    digitalWrite(IN3, HIGH);
    delay(500); 
    digitalWrite(ENL, HIGH);     //Move left                
    digitalWrite(ENR, LOW);
    digitalWrite(IN1, HIGH);                                
    digitalWrite(IN3, LOW);  
    delay(500);
    digitalWrite(ENL, HIGH);                    // move forward
    digitalWrite(ENR, HIGH);
    digitalWrite(IN1, HIGH);                                
    digitalWrite(IN3, HIGH);
    delay(500);
    digitalWrite(ENL, LOW);      //Move right         
    digitalWrite(ENR, HIGH);
    digitalWrite(IN1, LOW);                                
    digitalWrite(IN3, HIGH);
    delay(500);
  }

}
