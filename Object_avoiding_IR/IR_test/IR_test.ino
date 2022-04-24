void setup() {
  pinmode(A0, INPUT)
  Serial.begin(9600)
}

void loop() {

  Serial.println(analogRead(A0))

}
