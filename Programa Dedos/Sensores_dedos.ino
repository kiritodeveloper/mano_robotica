#include <Servo.h>
//Variables

//Variables dedo1
int flexpin1=A0;
Servo myservo1;
int flexsum1=0;
int gradosServo1=0;

//variables dedo2
int flexpin2=A1;
Servo myservo2;
int flexsum2=0;
int gradosServo2=0;

//variables ded03
int flexpin3=A2;
Servo myservo3;
int flexsum3=0;
int gradosServo3=0;

//variables dedo4
int flexpin4=A3;
Servo myservo4;
int flexsum4=0;
int gradosServo4=0;


//variables dedo5
int flexpin5=A5;
Servo myservo5;
int flexsum5=0;
int gradosServo5=0;

void setup()
{
  //Servo1
  myservo1.attach(6);
  myservo1.write(0);
  //Servo2
  myservo2.attach(5);
  myservo2.write(0);
  //Servo3
  myservo3.attach(3);
  myservo3.write(0);
  //Servo4
  myservo4.attach(10);
  myservo4.write(0);
  //Servo5
  myservo5.attach(9);
  myservo5.write(0);
  
  // inicializamos la comunicacion
  Serial.begin(9600); 
}

void loop()
{  
  dedo1();
  dedo2();
  dedo3();
  dedo4();
  dedo5();
  
  //iMPRIMIMOS VALORES
  /*Serial.print("DEDO1: ");
  Serial.print(flexsum1);
  Serial.print("   grados: ");
  Serial.println(gradosServo1);
  delay(300);
  
  /*Serial.print("DEDO2: ");
  Serial.print(flexsum2);
  Serial.print("   grados: ");
  Serial.println(gradosServo2);
  
  /*Serial.print("DEDO3: ");
  Serial.print(flexsum3);
  Serial.print("   grados: ");
  Serial.println(gradosServo3);
  
  Serial.print("DEDO4: ");
  Serial.print(flexsum4);
  Serial.print("   grados: ");
  Serial.println(gradosServo4);
  */
  Serial.print("DEDO5: ");
  Serial.print(flexsum5);
  Serial.print("   grados: ");
  Serial.println(gradosServo5);
  
  }
  
void dedo1(){
 for( int x=0; x<20;x++){
  flexsum1=flexsum1+analogRead(flexpin1);
  }
  flexsum1=flexsum1/20;
  delay(100);
  // convert the voltage reading to inches
  // the first two numbers are the sensor values for straight (768) and bent (853)
  // the second two numbers are the degree readings we'll map that to (0 to 90 degrees)
  if (flexsum1>=890 ){
   gradosServo1=0;
   myservo1.write(0);
  }
  else{
   gradosServo1=90;
   myservo1.write(90);
  }  
}

void dedo2(){
 for( int x=0; x<20;x++){
  flexsum2=flexsum2+analogRead(flexpin2);
  }
  flexsum2=flexsum2/20;
  delay(100);
  if (flexsum2>=870 ){
   gradosServo2=0;
   myservo2.write(90);
  }
  else{
   gradosServo2=90;
   myservo2.write(0);
  }  
}

void dedo3(){
 for( int x=0; x<20;x++){
  flexsum3=flexsum3+analogRead(flexpin3);
  }
  flexsum3=flexsum3/20;
  delay(100);
  if (flexsum3>=900 ){
   gradosServo3=0;
   myservo3.write(90);
  }
  else{
   gradosServo3=90;
   myservo3.write(0);
  }  
}

void dedo4(){
 for( int x=0; x<20;x++){
  flexsum4=flexsum4+analogRead(flexpin4);
  }
  flexsum4=flexsum4/20;
  delay(100);
  if (flexsum4>=500 ){
   gradosServo4=0;
   myservo4.write(90);
  }
  else{
   gradosServo4=90;
   myservo4.write(0);
  }  
}

void dedo5(){
 for( int x=0; x<20;x++){
  flexsum5=flexsum5+analogRead(flexpin5);
  }
  flexsum5=flexsum5/20;
  delay(100);
  if (flexsum5>=700 ){
   gradosServo5=0;
   myservo5.write(90);
  }
  else{
   gradosServo5=90;
   myservo5.write(0);
  }  
}

