#define SAMPLE_RATE 16000
#define SAMPLE_LENGTH 5
IntervalTimer myTimer;
volatile int count = 0;
int led1 = 35;
int led2 = 36;
int led3 = 37;
int bri1 = 0;
int bri2 = 0;
int bri3 = 0;
int scale = 150;
String data;


void setup() {
  while (millis() < 4000); // wait for python to start
  Serial.begin(2000000);
 
  myTimer.begin(voice_read, 62); // 16000 sample rate

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  analogWriteFrequency(led1,10000);
  analogWriteResolution(8); // 0 - 255
  analogWriteFrequency(led2,10000);
  analogWriteResolution(8); // 0 - 255
  analogWriteFrequency(led2,10000);
  analogWriteResolution(8); // 0 - 255
}

void voice_read(){
  count ++;
  if(count < SAMPLE_RATE * SAMPLE_LENGTH) {
   Serial.println(analogRead(PIN_A14)>>2); 
  }
}

void loop(){
   if(Serial.available() >= 3) {
        data = Serial.readStringUntil('\n');
        if (data == "eb") { //Everything brighter
          bri1 = min(255, bri1 + scale); bri2 = min(255, bri2 + scale); bri3 = min(255, bri3 + scale);
          analogWrite(led1, bri1); analogWrite(led2, bri2); analogWrite(led3, bri3);
          Serial.println("eb\n");
           delay(4000);
        analogWrite(led1,0); analogWrite(led2, 0); analogWrite(led3, 0);
        }
         else if (data == "ed") { //Everything dimmer
          bri1 = max(0, bri1 - scale); bri2 = max(0, bri2 - scale); bri3 = max(0, bri3 - scale);
          analogWrite(led1, bri1); analogWrite(led2, bri2); analogWrite(led3, bri3);
          Serial.println("ed\n");
           delay(4000);
        analogWrite(led1,0); analogWrite(led2, 0); analogWrite(led3, 0);
        }
        //Individual brightess: xy, where x =[1,2,3] indicate light, y = [b,d] indicate brighter, dimmer
        else if (data == "1b") {
          bri1 = min(255, bri1 + scale);
          analogWrite(led1, bri1);
          Serial.println("1b\n");
           delay(4000);
        analogWrite(led1,0); analogWrite(led2, 0); analogWrite(led3, 0);
        }
        else if (data == "2b") {
          bri2 = min(255, bri2 + scale);
          analogWrite(led2, bri2);
          Serial.println("2b\n");
           delay(4000);
        analogWrite(led1,0); analogWrite(led2, 0); analogWrite(led3, 0);
        }
        else if (data == "3b") {
          bri3 = min(255, bri3 + scale);
          analogWrite(led3, bri3);
          Serial.println("3b\n");
           delay(4000);
        analogWrite(led1,0); analogWrite(led2, 0); analogWrite(led3, 0);
       }
        else if (data == "1d") {
          bri1 = max(0, bri1 - scale);
          analogWrite(led1, bri1);
          Serial.println("1d\n");
           delay(4000);
        analogWrite(led1,0); analogWrite(led2, 0); analogWrite(led3, 0);
        }
        else if (data == "2d") {
          bri2 = max(0, bri2 - scale);
          analogWrite(led2, bri2);
          Serial.println("2d\n");
           delay(4000);
        analogWrite(led1,0); analogWrite(led2, 0); analogWrite(led3, 0);
        }
        else if (data == "3d") {
          bri3 = max(0, bri3 - scale);
          analogWrite(led3, bri3);
          Serial.println("3d\n");
           delay(4000);
        analogWrite(led1,0); analogWrite(led2, 0); analogWrite(led3, 0);
        }
        
        if(data == "start"){
          count = 0;
        }
        Serial.flush();
       
   }

}

