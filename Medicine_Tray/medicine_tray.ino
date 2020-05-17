#include <Servo.h> 

Servo myservo;
  int sensor = 8;
  int led = 3;
  int buzzer = 8;
  int flag=0;
  int timesTosend=1;
  char phone_no[]="7012805128";
  int count=0;


void setup() 
{ 
  myservo.attach(9);
  pinMode(led, OUTPUT);
  pinMode(sensor, INPUT);
  delay(5000);
  digitalWrite(sensor,LOW);
  digitalWrite(led,LOW);
  digitalWrite(buzzer,LOW);
  Serial.begin(9600); 
  Serial.println("AT+CMGF=1");    //set gsm to text mode
}



void loop() 
{
  myservo.write(0);  // set servo to mid-point
  delay(10000); 
  Serial.println("Time for morning medicine");
  buzzer();
  myservo.write(45);  // set servo to mid-point
  check();
  delay(3000);
  myservo.write(0);  // set servo to mid-point
  delay(10000); 
  Serial.println("Time for afternoon medicine");
  buzzer();
  myservo.write(90);  // set servo to mid-point
  check();
  delay(3000);
  myservo.write(0);  // set servo to mid-point
  delay(10000); 
  Serial.println("Time for evening medicine");
  buzzer();
  myservo.write(135);  // set servo to mid-point
  check();
  delay(3000);
  myservo.write(0);  // set servo to mid-point
  delay(10000); 
  Serial.println("Time for night medicine");
  buzzer();
  myservo.write(180);  // set servo to mid-point
  check();
  delay(3000);
  myservo.write(0);  // set servo to mid-point
  delay(1000); 
  } 

  void buzzer()
  {
    digitalWrite(buzzer,HIGH);
    delay(5000)
    digitalWrite(buzzer,LOW);
  }  
  
  void check()
  { 
    for(int i=0;i<30;i++) 
    {
      if(digitalRead(sensor)==HIGH)
      {
       Serial.println("high");
       digitalWrite(led,HIGH);
       flag=1;
       break;
      }
      delay(2000);
    }  
    if(flag==0)
    {
      Serial.println("medicine not taken ");
      Serial.println("preparing to send call......"); 
      gsmcall();
    }
    else if(flag==1)
    { 
      Serial.println("medicine taken");
      flag=0;
    }
  }
  void gsmcall()
  {
    while(count<timesTosend)
    {
      delay(3000);
      Serial.print("ATD");;
      Serial.print(phone_no);
      Serial.println(";");
      delay(20000);
      Serial.println("ATH");
      delay(1000);
      
      Serial.print("AT+CMGS=\"");
      Serial.print(phone_no);
      Serial.println("\"");
      delay(1500);
      Serial.println("<<<<MEDICNE NOT TAKEN>>>>");
      Serial.write(0x1A);               
      delay(5000);
      count++;
     }
   }                  