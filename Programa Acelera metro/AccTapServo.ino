#include <Wire.h> //El módulo GY-80 tiene una conexion de datos I2C. Esta libreria posee el protocolo I2C,lo que facilita la comunicacion entre la placa Arduino
		          //y el módulo. En la arduino UNO, las conexiones son: SDA -> A4  SCL -> A5
#include <Servo.h>
#include "ADXL345.h"
/*El módulo , al realizar las distintas mediciones, guarda los datos en una tabla interna. Cada posicion de la tabla 
tiene una direccion específica, y es allí donde iremos a buscar los datos. Los siguientes define son las direcciones que vamos a usar */

#define Register_ID 0
#define Register_2D 0x2D //Registro de control de potencia
#define Register_X0 0x32 //Dato del eje X 
#define Register_X1 0x33 //Dato del eje X
#define Register_Y0 0x34 //Dato del eje Y
#define Register_Y1 0x35 //Dato del eje Y
#define Register_Z0 0x36 //Dato del eje Z 
#define Register_Z1 0x37 //Dato del eje Z 

//Definimos los objetos a utilizar
ADXL345 accelerometer;
Servo myservo;
Servo myservo2;

//Definimos las variables a utilizar
int ADXAddress = 0xA7 >> 1;  // Es la dirección del slave de 7-bit por default
int reading = 0;
int val=0;
int X0,X1,X_out,estado=0;
int Y0,Y1,Y_out;
int Z1,Z0,Z_out;
double Xg,Yg,Zg;
int contador=0; //Este contador lo usaremos para realizar un pequeño filtro promediador.
int  vecx[10],vecy[10],vecz[10]; //Vectores que utilizaremos para el filtro.


void setup()
{
  Wire.begin();       //Iniciamos la libreria.
  myservo2.attach(5); //Servo1                          FIX THIS PART AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
  myservo.attach(6);  //Servo2
    
  Serial.begin(9600);    
  delay(100);
  // enable to measute g data
  Wire.beginTransmission(ADXAddress); //Iniciamos la transmición con el slave ( en este caso, con el módulo GY-80)
  Wire.write(Register_2D);			
  Wire.write(8);                //Habilitamos las mediciones
  Wire.write(0x31);             //  voy al registro DATA FORMAT, donde puedo settear el rango de medicion
  Wire.write(0x01);              // pongo el rango en +/- 4G
  Wire.endTransmission();     // Dejamos de transmitir
  
  accelerometer.setTapDetectionX(0);       // Don't check tap on X-Axis
  accelerometer.setTapDetectionY(0);       // Don't check tap on Y-Axis
  accelerometer.setTapDetectionZ(1);       // Check tap on Z-Axis
    accelerometer.setTapThreshold(2.5);      // Recommended 2.5 g
  accelerometer.setTapDuration(0.02);      // Recommended 0.02 s
  accelerometer.setDoubleTapLatency(0.10); // Recommended 0.10 s
  accelerometer.setDoubleTapWindow(0.30);  // Recommended 0.30 s

  // Select INT 1 for get activities
  accelerometer.useInterrupt(ADXL345_INT1);

  // Check settings
  checkSetup();
}

void checkSetup()
{
  Serial.print("Look tap on axis = "); 
  if (accelerometer.getTapDetectionX()) { Serial.print(" X "); }
  if (accelerometer.getTapDetectionY()) { Serial.print(" Y "); }
  if (accelerometer.getTapDetectionZ()) { Serial.print(" Z "); }
  Serial.println();

  Serial.print("Tap Threshold = "); Serial.println(accelerometer.getTapThreshold());
  Serial.print("Tap Duration = "); Serial.println(accelerometer.getTapDuration());
  Serial.print("Double Tap Latency = "); Serial.println(accelerometer.getDoubleTapLatency());
  Serial.print("Double Tap Window = "); Serial.println(accelerometer.getDoubleTapWindow());
}


void loop()
{
  //--------------X--------------
  Wire.beginTransmission(ADXAddress); // Iniciamos la transmición
  Wire.write(Register_X0);	//En estos dos registros se encuentran los datos del eje X. Para ver
  Wire.write(Register_X1);	//que hay en cada dirección, ver el datasheet.
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2)   
  {
    X0 = Wire.read();
    X1 = Wire.read(); 
    X1=X1<<8;
    X_out=X0+X1;   
  }

  //------------------Y-------------
  Wire.beginTransmission(ADXAddress); // Transmitimos ..
  Wire.write(Register_Y0);	//Como información adicional: Ya mencione que para traer la info de un eje, consultamos 2 registros distintos.
  Wire.write(Register_Y1);	//Esto es porque la info de cada eje consta de 2 bytes, y como cada registro almacena 1 byte, se divide la info en 2.
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); // RequestFrom(direccion,cantidad) se usa para pedir bytes del maestro al esclavo. 
  if(Wire.available()<=2)   //Luego del requestFrom se utiliza available, que devuelve la cantidad de bytes que estan disponibles para lectura.
  {
    Y0 = Wire.read(); //Con la función read obtenemos los bytes que el esclavo quiere transmitir. Como pedimos 2, primero 
    Y1 = Wire.read(); //trasmite un byte con el primer Wire.read, y con el segundo Wire.read, transmite el segundo.
    Y1=Y1<<8;
    Y_out=Y0+Y1;
  }
	
  //------------------Z----------------
  Wire.beginTransmission(ADXAddress); // Transmitimos..
  Wire.write(Register_Z0);
  Wire.write(Register_Z1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2)   
  {
    Z0 = Wire.read();
    Z1 = Wire.read(); 
    Z1=Z1<<8;
    Z_out=Z0+Z1;
  }
  //
  Xg=X_out*100/256.0;		//Calculos que todavia tengo que analizar.
  Yg=Y_out*100/256.0;		//En estas variables se guardan los valores de los ejes.
  Zg=Z_out*100/256.0;
  
   
   Vector norm = accelerometer.readNormalize();
  // Read activities
  Activites activ = accelerometer.readActivites();

  if (activ.isDoubleTap) {
   if(estado==1) estado=0;
   else estado=1;
   Serial.println("TAPEASTE");
   Serial.println("Estado");
   Serial.println(estado);
  }  
  if(estado==0){  
   int asd=map(Yg,-90,90,0,180);
  if(asd>=0) myservo.write(asd);
  Serial.println(asd);
  }
 
  if(estado==1){
  if(Xg>=0) myservo2.write(Xg);
  Serial.print(" X: "); 
  Serial.println(Xg);  
}
   delay(10);  

}
