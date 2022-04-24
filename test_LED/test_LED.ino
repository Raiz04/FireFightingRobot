#define test 5
void setup() {
  pinMode(test, OUTPUT);
}

void loop() {

  digitalWrite(test,HIGH);
  delay(1500);
  digitalWrite(test,LOW);
  delay(1500);

}
