int LED = 8;
int PIR = 5;

void setup() { pinMode(LED, OUTPUT);
pinMode(PIR, INPUT);
Serial.begin(9600);
}

void loop() {

int readValue = digitalRead(PIR); Serial.println(readValue);
if (readValue == HIGH) {

digitalWrite(LED, LOW);      
} else {digitalWrite(LED, HIGH);
}

}
