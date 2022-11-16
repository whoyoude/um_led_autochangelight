// Variable to hold analog values from mic
int del = 65510;
int record = 0;int changelight=1;
int led1 = 6;
int led2 = 5;
int led3 = 3;
int bri1 = 0;
int bri2 = 0;
int bri3 = 0;
int scale = 150;
String data;

void light_change() {
  record = 0;changelight =1;
  //TIMSK1 |= (0 << TOIE1);  //Disable timer interrupt termporaily
//
//  TCCR1A = 0;
//  TCCR1B = 0;
//  TCNT1 = del;                        // preload timer
//  TCCR1B |= (1 << CS11) | (1 << CS10);  // 64 prescaler
//  TIMSK1 |= (1 << TOIE1);               // enable timer overflow
//  TIMSK1 |= (1 << TOIE1);  //Enable timer interrupt again
//  interrupts();                         // enable all interrupts
}

void setup() {
  Serial.begin(2000000);
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = del;                        // preload timer
  TCCR1B |= (1 << CS11) | (1 << CS10);  // 64 prescaler
  TIMSK1 |= (1 << TOIE1);               // enable timer overflow interrupt ISR
  interrupts();                         // enable all interrupts

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), light_change, CHANGE);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

ISR(TIMER1_OVF_vect)                    // interrupt service routine for overflow per 1ms
{
  TCNT1 = del;
  // preload timer
    record = 1^changelight;
  
}

void loop() {
    if ((record == 1) && (changelight == 0)) {
      int micout = analogRead(A1) >> 2;
      Serial.println(micout);
      record = 0;
   }
   else if((record == 0) && (changelight == 1)){
     record = 1;changelight =0;
     delay(500);
  //TIMSK1 |= (0 << TOIE1);  //Disable timer interrupt termporaily    
     if(Serial.available() > 0) {
        data = Serial.readStringUntil('\n');
        if (data == "eb") { //Everything brighter
          bri1 = min(255, bri1 + scale); bri2 = min(255, bri2 + scale); bri3 = min(255, bri3 + scale);
          analogWrite(led1, bri1); analogWrite(led2, bri2); analogWrite(led3, bri3);
          Serial.println("eb\n");
        }
        else if (data == "ed") { //Everything dimmer
          bri1 = max(0, bri1 - scale); bri2 = max(0, bri2 - scale); bri3 = max(0, bri3 - scale);
          analogWrite(led1, bri1); analogWrite(led2, bri2); analogWrite(led3, bri3);
          Serial.println("ed\n");
        }
        //Individual brightess: xy, where x =[1,2,3] indicate light, y = [b,d] indicate brighter, dimmer
        else if (data == "1b") {
          bri1 = min(255, bri1 + scale);
          analogWrite(led1, bri1);
          Serial.println("1b\n");
        }
        else if (data == "2b") {
          bri2 = min(255, bri2 + scale);
          analogWrite(led2, bri2);
          Serial.println("2b\n");
        }
        else if (data == "3b") {
          bri3 = min(255, bri3 + scale);
          analogWrite(led3, bri3);
          Serial.println("3b\n");
       }
        else if (data == "1d") {
          bri1 = max(0, bri1 - scale);
          analogWrite(led1, bri1);
          Serial.println("1d\n");
        }
        else if (data == "2d") {
          bri2 = max(0, bri2 - scale);
          analogWrite(led2, bri2);
          Serial.println("2d\n");
        }
        else if (data == "3d") {
          bri3 = max(0, bri3 - scale);
          analogWrite(led3, bri3);
          Serial.println("3d\n");
        }
        changelight=0;
     }
   }
}
