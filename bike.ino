int state = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(11, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(11);
  if (state == 0 && value == 0)
  {
    state = 1;
  }

  if (state == 1 && value == 1)
  {
    Serial.println(1);
    state = 0;
  }
  
  delay(20);
}
