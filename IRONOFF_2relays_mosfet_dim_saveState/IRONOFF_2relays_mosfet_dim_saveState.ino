#include <IRremote.h>
IRsend irsend;
int RECV_PIN = 2;
const int RELAY = 13;
const int RELAY10 = 10;
const int RELAY1 = 6;



const int RELAY2=7;
int relayState = 0;
int relay1State = 0;
IRrecv irrecv(RECV_PIN);
decode_results results;
int counter = 255;


long previousMillis = 0;
long interval = 500;


void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(RELAY, OUTPUT);
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);    
        pinMode(RELAY10, OUTPUT);    
}

void loop() {
  
  
  

   if (Serial.read() != -1) {
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0xa90, 12); // Sony TV power code
      //delay(100);
    }
   }
  else  if (irrecv.decode(&results)) {
    Serial.println(results.value, DEC);
    
 
   unsigned long currentMillis = millis();
  
     
  if (currentMillis - previousMillis>interval){
   previousMillis = currentMillis;
   
 if(results.value==2894&&relayState==HIGH)
  
{  relayState=LOW;
counter=0;
  Serial.print("relayState =    ");
  Serial.println(relayState);
  Serial.println(counter);

      analogWrite(RELAY10, counter/4);
            //analogWrite(RELAY1, counter/4);
}
    else  if(results.value==2894&&relayState==LOW)
      {relayState=HIGH;
     //TRY THIS NEXT TIME relayState = relay1State;
      counter = 255;
        Serial.print("relayState =    ");

  Serial.println(relayState);
          Serial.println(counter);

      }
      else if
   
 (results.value==3216&&relayState==HIGH){
 
    counter = counter -20; 
 
    if(counter<=0){
     counter =0; 
    }
   Serial.print("dimming    ");
      Serial.println(counter);

  }
  else if(results.value==1168&&relayState==HIGH){
   counter=counter+20;
  
  if(counter>=255){
   counter = 255;
  } 
   Serial.print("brightening!   ");
   Serial.println(counter);
  }

   analogWrite(RELAY10, counter);
    //  analogWrite(RELAY1, counter);
    
     
  }
  
  
  
  
  if(results.value==691022&&relay1State==HIGH){
   relay1State =LOW;
 Serial.print("relay2State =    ");
 Serial.println(relay1State);}
   else if(results.value==691022&&relay1State==LOW){
     relay1State=HIGH;
     Serial.print("relay2State =    ");
 Serial.println(relay1State);
   }
  
  
  
  
      digitalWrite(RELAY, relayState);
     analogWrite(RELAY1, counter);
    
  
  digitalWrite(RELAY2, relay1State);
    //analogWrite(RELAY10, 127);
       
    
  
    irrecv.resume(); // Receive the next value
  
  }
  
  
   
  }
  
  

//  fuse?
