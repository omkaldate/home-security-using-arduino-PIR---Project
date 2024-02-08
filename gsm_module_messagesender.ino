#include <SoftwareSerial.h>
#include<LiquidCrystal.h>

LiquidCrystal lcdd(12,11,10,9,8,7);
int const txdgsm = 2;
int const rxdgsm = 3;
int pir = 13;
int buzzer = 4;
int pirin ;
SoftwareSerial modulegsm(rxdgsm,txdgsm);
void message();
void call();


void setup() {
    Serial.begin(9600);
    Serial.println("starting the system");
    
   lcdd.begin(16,2);
   lcdd.setCursor(2,0);
   lcdd.print("staarting the ");
   lcdd.setCursor(5,1);
   lcdd.print("system");
   delay(500);
   lcdd.clear();
   lcdd.print("*** all done ***");
   
   pinMode(pir,INPUT);
   pinMode(buzzer,OUTPUT);
  
  while(!Serial);
   modulegsm.begin(9600);
  delay(1000);
}
   
 void loop() {
   pirin = digitalRead(pir);
   Serial.print("PIR sensor input = ");
   Serial.println( pirin );
   
   if(pirin==HIGH){
   //  ##################### MESSAGE SEND PROGRAM ####################
    Serial.println("thief is detected ");
    digitalWrite(buzzer,HIGH);
    lcdd.clear();
    lcdd.print("thief is detected");
    delay(400);
    lcdd.clear();
    lcdd.print("sending message");
    Serial.println("prepairing the system for SMS sending");
     message();
     lcdd.clear();
     lcdd.setCursor(1,0);
     lcdd.println("aleart message");
     lcdd.setCursor(0,1);
     lcdd.println("sent sucessfully");
     Serial.println();
     delay(400);
    //  ##################### CALLING PROGRAM ####################
     lcdd.clear();
     lcdd.print("calling to owner");
     Serial.println("prepairing the system for calling");
     call();
     lcdd.clear();
     lcdd.println("aleart call");
     lcdd.setCursor(0,1);
     lcdd.println("done sucessfully");
     Serial.println();
     delay(400);
   }

   else{
     digitalWrite(buzzer,LOW);
     lcdd.clear();
     lcdd.setCursor(2,0);
     lcdd.print("thief is not ");
     lcdd.setCursor(4,1);
     lcdd.print("detected");
     delay(400);
     lcdd.clear();
     lcdd.setCursor(2,0);
     lcdd.print("all safe here");
     delay(400);
     Serial.println();
           
   }
   }



   void message(){
    Serial.println("set SMS format to ASCI");
    modulegsm.print("AT+CMGF=1\r\n");
    delay(500);
    Serial.println("Send new SMS command and destination message number");
    modulegsm.print("AT+CMGS=\"7558335252\"\r\n");
    delay(500);
    modulegsm.print("thief is detected....!");
    delay(500);
    modulegsm.println((char)26);
    Serial.println("SMS Sent succesfully...");
    delay(400);
     }

   void call(){
    Serial.print("set call format and destination calling number");
    modulegsm.println("ATD7558335252;");
    delay(3000);
    Serial.println("cut call command");
    modulegsm.println("ATH");
    Serial.println("call done succesfully...");
    modulegsm.println();
    

   }
   
   
