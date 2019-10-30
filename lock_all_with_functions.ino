
#include <IRremote.h>
int motoropen=11;
int motorclose=10;
int button=9;
int prox=7;
boolean state=HIGH;
char bstate=0;
int ledpin=13;


int IR_Recv = 8;   //IR Receiver Pin 3

IRrecv irrecv(IR_Recv);
decode_results results;


int runmotor(int);
void setup() {
  // put your setup code here, to run once:
pinMode(motoropen,OUTPUT);
pinMode(motorclose,OUTPUT);
pinMode(button,INPUT);
pinMode(ledpin,OUTPUT);
pinMode(prox,INPUT);
Serial.begin(9600);





  

irrecv.enableIRIn(); // Starts the receiver
  pinMode(ledpin,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(motoropen,LOW);
digitalWrite(motorclose,LOW);
digitalWrite(ledpin,LOW);



if(digitalRead(button)==HIGH)
{//Serial.println(digitalRead(button));
  runmotor(state);
}



if(digitalRead(prox)==LOW)
{//Serial.println(digitalRead(prox));
  runmotor(state);
  
digitalWrite(motoropen,LOW);
digitalWrite(motorclose,LOW);
  delay(500);
}



if(Serial.available()>0)
{ bstate=Serial.read();
delay(20);
}



if(bstate=='q' )
{runmotor(state);
 bstate=0;
}

if (irrecv.decode(&results)){
     long int decCode = results.value;
    //Serial.println(decCode);
 

if(decCode==351002655  ||  decCode==284154150     )                  // 284154150 
{runmotor(state);
decCode=0;
}


irrecv.resume();
}   
}

int runmotor(int s)
{
  if(s==1)
  { Serial.println("Its closed");
    delay(100);
  digitalWrite(motoropen,LOW);
digitalWrite(motorclose,HIGH);
delay(100);
state=LOW;}
  if(s==0)
   {Serial.println("Its open");
    delay(100);
   digitalWrite(motoropen,HIGH);
   digitalWrite(motorclose,LOW);

   delay(100);
   state=HIGH;}
}
