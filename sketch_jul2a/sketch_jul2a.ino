#define ledGreen 2
#define ledRed 3
#define buzzer 4
int mq7_base = 0;
int mq135_base = 0;

void setup() {
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);

  delay(10000); 

  long sum7 = 0;
  long sum135 = 0;

  for (int i = 0; i < 50; i++) {
    sum7 += analogRead(A0);
    sum135 += analogRead(A1);
    delay(20);
  }

  mq7_base = sum7 / 50;
  mq135_base = sum135 / 50;

  Serial.print("MQ7 base = ");
  Serial.println(mq7_base);

  Serial.print("MQ135 base = ");
  Serial.println(mq135_base);
}

void loop() {

  long sum7 = 0;
  long sum135 = 0;

  for (int i = 0; i < 20; i++) {
    sum7 += analogRead(A0);
    sum135 += analogRead(A1);
    delay(10);
  }

  int mq7 = sum7 / 20;
  int mq135 = sum135 / 20;

  int diff7 = mq7 - mq7_base;
  int diff135 = abs(mq135 - mq135_base);

  Serial.print("MQ7: ");
  Serial.print(mq7);
  Serial.print(" | MQ135: ");
  Serial.print(mq135);
  Serial.print(" | D7: ");
  Serial.print(diff7);
  Serial.print(" | D135: ");
  Serial.println(diff135);

  if (diff7 < 20 && diff135 < 20) {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(buzzer, LOW);
  }

  else if (diff7 < 80) {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(buzzer, LOW);
  }

  else {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    digitalWrite(buzzer, HIGH); 
  }
  delay(200);
}