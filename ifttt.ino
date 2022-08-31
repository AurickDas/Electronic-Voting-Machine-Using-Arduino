#include <WiFi.h>
#include <HTTPClient.h>

#define RXp2 16
#define TXp2 17
#define sendpin 23
char value1;
char value2;
char value3;
const char * ssid = "Fatin";
const char * password = "12345678";

String server = "http://maker.ifttt.com";
String eventName = "vote_count";
String IFTTT_Key = "nISCel7oHDlsSR04fflUGNl3iPmFBP8LVJUJvF0_ZGU";
String IFTTTUrl="http://maker.ifttt.com/trigger/vote_count/with/key/nISCel7oHDlsSR04fflUGNl3iPmFBP8LVJUJvF0_ZGU";


void setup() {
  
  pinMode(sendpin,INPUT);
  digitalWrite(sendpin,HIGH);
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Viola, Connected !!!");
}

//float getLightPercentage(void)
//{
//  int ldrRawVal;
//  float percentage;
//  ldrRawVal = analogRead(LDR_PIN);    
//  percentage = ((float)((ldrRawVal*100)/4096));
//  return percentage;
//}

char receivedChar;
boolean newData = false;
char i;
int vote;
int count = 0;
char j[4];
int id;
void votecount()

{
  recvOneChar();
    
       if (newData == true) 
        {
            i=receivedChar;
//            vote=i.toInt();
        if (!(isSpace(i))){
             Serial.println(i);
             delay(50);
             newData=false;
             j[id]=i;
             id++;
             
        }
        }
        
       
  }


  void recvOneChar() {
    if (Serial2.available() > 0) {
        receivedChar = Serial2.read();
        newData = true;
    }
}



void sendDataToSheet(void)
{
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + String(value1) + "&value2="+String(value2) +"&value3=" + String(value3);  
  Serial.println(url);
  //Start to send data to IFTTT
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  http.begin(url); //HTTP

  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();

}
int flg=0;
  void increaseflg()
  {
    flg=flg+1;
    
    }

void loop() {

  
  
  
  votecount();
  value1 = j[0];
  value2 = j[1];
  value3 = j[2]; 

  Serial.print("Values are ");
  Serial.print(value1);
  Serial.print(' ');
  Serial.print(value2);
  Serial.print(' ');
  Serial.println(value3);
  Serial.print(' '); 

if (!(j[0]==NULL | j[1] == NULL | j[2]==NULL ))

{
  if (flg==0)
{
    sendDataToSheet();
    increaseflg();
}
}
Serial.print( " the flag is ");
Serial.println(flg);
  delay(3000);
}
