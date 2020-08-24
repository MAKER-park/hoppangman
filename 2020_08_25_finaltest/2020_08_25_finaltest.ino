#include <MsTimer2.h>

int TRIG = 6, ECHO = 7;
int LED = 3; //릴레이
int PIR = 5;
int MOS = 4;//이제 사용안함

float duration, distance; //초음파발사
int readValue = 0;
int count_a = 0;// 2m30s
bool count_b = false;// rest
int count_c = 0;

void sensor() {
  count_a++;


  if (count_b == false) {
    if (distance < 30)
    {
      count_a = 0;

      if (readValue == HIGH)
      {
        digitalWrite(LED, LOW);
      }
      else
      {
        digitalWrite(LED, LOW);
      }
    }

    else if (distance >= 30)
    {
      if (readValue == HIGH) {
        digitalWrite(LED, LOW);
      }
      else
      { digitalWrite(LED, HIGH);
        if (count_a >= 300) //2m 30s
        {
          digitalWrite(LED, LOW);
          digitalWrite(MOS, LOW);
          //Serial.print("H / MOS H");
          count_a = 0;
          count_b = true;
        }
      }
    }

    else
      digitalWrite(LED, LOW);
  }
  else {
    if (distance < 30 || readValue == HIGH)
    {
      count_b = false;
    }

  }
}






void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);

  MsTimer2::set(500, sensor); // sensor함수를 500ms마다 호출한다
  MsTimer2::start();
}



void loop() {
  digitalWrite(TRIG, HIGH);
  delay(20);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH); //초음파가 사무 맞고 돌아온 시간 저장
  distance = ((float)(duration * 340) / 10000) / 2; //시간을 거리로cm환산

  readValue = digitalRead(PIR); // PIR센서 리드
  Serial.print("거리 : ");
  Serial.print(distance);
  Serial.println("cm\n");
  Serial.print("count_a: ");
  Serial.print(count_a);
  Serial.println("SEC");

  Serial.print("count_b: ");
  Serial.print(count_b);
  Serial.println("SEC");

  Serial.print("count_c: ");
  Serial.print(count_c);
  Serial.println("SEC");
}
