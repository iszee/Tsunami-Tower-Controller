#include <SoftwareSerial.h>

SoftwareSerial SIM900(7, 8);

char incoming_char=0;
String sms="";
String grantedNumber="+94717278771";
String grantedNumber1="+94713256039";
String senderNumber;
String senderMsg;
String demosms="+CMT: +94717278771,,18/04/13,00:09:58+22\nOn\n\n";

void setup() {
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
  SIM900.begin(19200);
  Serial.begin(19200); 
  delay(20000);

  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}

void loop() {
  readSms();
  if(sms!=""){
    //Serial.println(sms);
    Serial.println("Message Validating . . . . .");
    senderNumber=validateNumMsg(sms);
    delay(10000);
  }
  
}


void readSms(){
  sms="";
  while(SIM900.available() >0) {
    incoming_char=SIM900.read(); 
    sms.concat(incoming_char);
    delay(1);
    }
  }

String validateNumMsg(String sms){
  int i=0;
  int k;
  String senderNum="";
  senderMsg="";
  while(sms[i]!=NULL){
    if((sms[i]=='+')&&(sms[i+1]=='9')&&(sms[i+2]=='4')){
      for(k=0;k<=11;k++){
        senderNum.concat(sms[i]);
        i++;
        }
        if((grantedNumber==senderNum)||(grantedNumber1==senderNum)){
          Serial.print("Access Granted For ");
          Serial.println(senderNum);
          while(sms[i]!='\n'){
            i++;
            }
            i++;
            while(sms[i]!='.'){
              senderMsg.concat(sms[i]);
              i++;
              if(sms[i]=='\n'){
                break;
                }
              if(sms[i]==NULL){
                break;
                }
              }
              Serial.print("Sender Message ::::   ");
              Serial.print(senderMsg);
              Serial.println("   ::::");
              switchMode(senderMsg);
          }
          else{
            Serial.print("Access Denied For ");
            Serial.println(senderNum);
            Serial.println("\n");
            }
        break;
      }
      else{
        i++;
        }
    }
    return senderNum;
  }

void switchMode(String msg){
  String msg1=msg;

  if((msg1=="on")||(msg1=="ON")||(msg1=="On")){
    Serial.println("Successfully Turn ON the Tower\n");
    }
  else if ((msg1=="off")||(msg1=="OFF")||(msg1=="Off")){
    Serial.println("Successfully Turn OFF the Tower\n");
    }
  else if (msg1=="mode1"){
    Serial.println("Successfully Turn ON the Mode 1\n");
    }
  else if (msg1=="mode2"){
    Serial.println("Successfully Turn ON the Mode 2\n");
    }
  else{
    Serial.println("Invalid Message!\n");
    }
  
  
  }
