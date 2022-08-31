
#include <Adafruit_Fingerprint.h>
#define PB 26
#define vote1 22
#define vote2 28
#define vote3 30

#define sending 34
#include <Keypad.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // rs,en,db4,db5.db6,db7
int flag[128];
SoftwareSerial mySerial(12,11);
#include <string.h>


const int ROW_NUM    = 4; // four rows
const int COLUMN_NUM = 4; // four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  
  {'1','4','7', '*'},
{'2','5','8', '0'},
{'3','6','9', '#'},
{'A','B','C', 'D'}
};
//  {'1','2','3', 'A'},
//  {'4','5','6', 'B'},
//  {'7','8','9', 'C'},
//  {'*','0','#', 'D'}
byte pin_rows[ROW_NUM] = {52, 50, 48, 46}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {44, 42, 40, 38}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const String password_1 = "1234ABC"; // change your password here

String input_password;


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{ pinMode(PB,INPUT);
  pinMode(vote1,INPUT);
  pinMode(vote2,INPUT);
  pinMode(vote3,INPUT);

  pinMode(sending,INPUT);
  input_password.reserve(32);
  digitalWrite(PB,HIGH);
  digitalWrite(vote1,HIGH);
  digitalWrite(vote2,HIGH);
  digitalWrite(vote3,HIGH);
//  digitalWrite(vote4,HIGH);
  digitalWrite(sending,HIGH);

  lcd.begin(16, 2);
  lcd.print(" Electronic ");
  lcd.setCursor(0,1);
  lcd.print(" Voting Machine ");
  delay(4000);
  lcd.clear();
  lcd.begin(16,2);
  lcd.print("press 1 to vote");
  Serial.begin(9600);
  while (!Serial);  
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  
  
}
int votef;
int votes;
int votet;
int votefo;
void voteincrement1()
{votef++;
  }
  void voteincrement2()
{votes++;
  }
  void voteincrement3()
{votet++;
  }
  
  
void increaseFlag()
{ int k=finger.fingerID;
  flag[k]=1;
  }

int pass()
{
  lcd.begin(16,2);
  lcd.print("input password");
  lcd.setCursor(0,1);
   int passflg; 
while(1)
{     
  char key = keypad.getKey();
  if (key){
  lcd.print(key);
        if(key!=('#')){
      input_password += key; // append new character to input password string
    }

    else  break;
  }
      }

  if(input_password == password_1 ) {
        
  passflg= -5;
  
      } 
      
      else {
      
        passflg= -9;
         
      }
      
return passflg;
}

void passclear()
{
  input_password.remove(0,7);
  }
  
void loop()                     // run over and over again
{ int pbflg=0;
  if (digitalRead(PB)==0) 
  {pbflg=1;
  lcd.begin(16,2);
  lcd.print("place finger");
  }
 //o Serial.println(pbflg);
  while(digitalRead(PB)==0);
  while (pbflg)
  {
  int k=getFingerprintIDez();
  
  if (k!=-3 && k!=-2 && k!=-4 && k!=3)
  { lcd.begin(16,2);
    lcd.print("cast your vote");
    //Serial.println(k);
     increaseFlag();
     pbflg=0;
     while(1){
      if (digitalRead(vote1)==0)
      {
        voteincrement1();
        lcd.begin(16,2);
        lcd.print("successful");
        delay(3000);
         lcd.clear();
         lcd.begin(16,2);
         lcd.print("press 1 to vote");
        break;
        }
        if (digitalRead(vote2)==0)
        { lcd.begin(16,2);
        lcd.print("successful");
          voteincrement2();
          delay(6000);
         lcd.clear();
         lcd.begin(16,2);
         lcd.print("press 1 to vote");
          break;
          }
          if (digitalRead(vote3)==0)
        { lcd.begin(16,2);
        lcd.print("successful");
          voteincrement3();
          delay(6000);
         lcd.clear();
         lcd.begin(16,2);
         lcd.print("press 1 to vote");
          break;
          }
                }
    }
    if (k!=-3  && k==3) pbflg=0;
    if(k==-4) pbflg=0;
   
    if(pbflg==0) break;
    

}
//Serial.println("votecount1= ");
if (digitalRead(sending)==0){

  int l=pass();
   if (l==-5){     
  Serial.println(votef);
  Serial.println(votes);
  Serial.println(votet);
  Serial.println(votefo);
  lcd.begin(16,2);
  lcd.print("data sent");
  passclear();
   }

         else if (l==-9)
         {
          lcd.begin(16,2);
          lcd.print("password incorrect");
          passclear();
         
          }
  }
  delay(50);            //don't ned to run this at full speed.
 
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
//  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
//  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t q,r;
  int imgflg;
  int tmpflg;
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) 
  {//Serial.println("image paynai"); 
  return -2;
  }
  else  imgflg=1;
  
  q = finger.image2Tz();
  if (q != FINGERPRINT_OK)  {
    //Serial.println("template paynai"); 
  return -3;
  }
  else tmpflg=1;

  r = finger.fingerFastSearch();
  
  if (r != FINGERPRINT_OK && imgflg==1 && tmpflg==1 ) 
  
  { lcd.begin(16,2);
    lcd.print("invalid voter");
     delay(6000);
         lcd.clear();
         lcd.begin(16,2);
         lcd.print("press 1 to vote");
    
  return -4;
  }
  // found a match!
  if(flag[finger.fingerID]==0 && finger.fingerID!=0){
//  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
//  Serial.print(" with confidence of "); 
//  Serial.println(finger.confidence);
  return finger.fingerID; }
  
  else 
  { lcd.begin(16,2);
    lcd.print("already voted");
     delay(6000);
         lcd.clear();
         lcd.begin(16,2);
         lcd.print("press 1 to vote");
//    Serial.println("already voted");
    return 3;
  }
}
uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;

  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
  }

  return p;
}

uint8_t readnumber(void) {
  uint8_t num = 0;

  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}
