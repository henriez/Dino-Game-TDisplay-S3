#define D4 2
#define D3 0

void setup() {
  // put your setup code here, to run once:
  pinMode(D4, OUTPUT);
  pinMode(D3, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(D3) == LOW) {
    tone(D4, 500, 250);
    delay(250);
    noTone(D4);
  }
}
