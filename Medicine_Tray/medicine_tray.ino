#include <Servo.h>
#include<SoftwareSerial.h>

Servo myservo;

int IR=8;
int led=12;

int flag;
char phone_no[] = "8086265488";
int incomingByte = 0;

SoftwareSerial mySerial(9, 10); // RX, TX  

void setup() 
{
  myservo.attach(7);

  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)

  pinMode(IR, INPUT);
  pinMode(led, OUTPUT);

  delay(2000);
  Serial.println("AT+CMGF=1");   //set GSM to text mode
  delay(200);
}
 void loop()
 {
   // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
  
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
    
    if (incomingByte == 49) {
     Serial.println("morning medicine");
     delay(2000);
     medicineTray(45);
     }
     
     if (incomingByte == 50) {
      Serial.println("afternoon medicine");
      delay(2000);
      medicineTray(90);
     }
    
      if (incomingByte == 51) {
        Serial.println("night medicine");
        delay(2000);
        medicineTray(135);
      }  
 }
 }

void medicineTray(int x)
{
  myservo.write(0);
   delay(1000);

    myservo.write(x);
    delay(1000);
    
    medicineTakenStatus(); 

    myservo.write(0);

  }

  void medicineTakenStatus()
  {
   flag = 0;
   for(int i= 0; i<20; i++)                       // waits for 20 sec
   {  
    Serial.println(i);
    if(digitalRead(IR)==LOW)
    {
      digitalWrite(led, HIGH);
      Serial.println("Motion Detected");
      digitalWrite(led, LOW);
      flag = 1;
      break;
      
    }
    delay(1000);
   }
    if (flag != 1)
    { Serial.println("medicine not taken, make call to caretaker");
    
     gsmCall();
     
      }
    }

    void gsmCall()
    {
     if (mySerial.available()>0)
      Serial.write(mySerial.read()); 
     
     delay(1000);
     
     Serial.println("dialing");
     mySerial.print("ATD");;
     mySerial.print(phone_no);
     mySerial.println(";");
     delay(20000);
     mySerial.println("ATH");
     delay(1000);
     Serial.println("Call stopping");
     
     Serial.println("messaging");
     mySerial.print("AT+CMGS=\"");
     mySerial.print(phone_no);
     mySerial.println("\"");
     delay(1500); 
     mySerial.print("CAUTION...INTRUDER ALERT ALARM !!!!!!!!!!"); 
     mySerial.write(0x1A);
     delay(2000);
     flag = 0;  
    }
