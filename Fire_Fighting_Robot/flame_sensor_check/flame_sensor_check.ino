#define Left A14    // left sensor
#define Right A13    // right sensor
#define Forward A15 //front sensor

void setup() {
  pinMode(Left,INPUT);
  pinMode(Right,INPUT);
  pinMode(Forward,INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Flame 1 : ");
  Serial.print(analogRead(Left));
  Serial.print("Flame 2 : ");
  Serial.print(analogRead(Right));
  Serial.print("Flame 3 : ");
  Serial.println(analogRead(Forward));
}
