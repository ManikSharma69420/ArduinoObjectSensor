// Arduino HCSRO4 Code By Manik Sharma (ManikSharma69420 - Github)

// this constant won't change. It's the pin number of the sensor's output:
const int echoPin = 8;
const int trigPin = 7;
const int buzzerPin = 10;
const int ledPin = 11;
const int switchPin = 2;

int switchState = 0;
int q = 0;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(buzzerPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(switchPin,INPUT);
}

void loop() {
  
  long duration, inches, cm;


  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // The echo pin is used to read the signal from the HC-SRO4: a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  switchState = digitalRead(switchPin);

  if (switchState == HIGH) {
    q = 0;
    Serial.print(q);
    if (inches >= 300) {
      Serial.print("falseinches");
    }

    if (cm >= 105) {
      Serial.print("falsecentimeters");
    }
    if (cm > 20 && cm < 150) {
      tone(buzzerPin, 300, 750);
      digitalWrite(ledPin, HIGH);
      delay(1000);
      noTone(buzzerPin);
      digitalWrite(ledPin, LOW);
      delay(1000);
    }

    if (cm > 15 && cm < 20) {
      tone(buzzerPin, 700, 500);
      digitalWrite(ledPin, HIGH);
      delay(500);
      noTone(buzzerPin);
      digitalWrite(ledPin, LOW);
      delay(500);
      }

    if (cm > 7 && cm < 15) {
      tone(buzzerPin, 1000, 250);
      digitalWrite(ledPin, HIGH);
      delay(250);
      noTone(buzzerPin);
      digitalWrite(ledPin, LOW);
      delay(250);
    }

    if (cm < 7 && cm > 0) {
      tone(buzzerPin, 1200, 100);
      digitalWrite(ledPin, HIGH);
      delay(100);
      noTone(buzzerPin);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
  }

  else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
}
long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

