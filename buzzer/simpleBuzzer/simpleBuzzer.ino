#define D4 2
#define D3 0
#define D2 4

void setup() {
  // put your setup code here, to run once:
  pinMode(D4, OUTPUT);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(D3) == LOW  || digitalRead(D2) == LOW) {
    tone(D4, 500, 100);
    delay(250);
    noTone(D4);
  }
}