# mano-robotica
## PROYECTO FINAL -Arquitectura de Sistema de Elaboración de datos II- UNDAV
## Estudiantes: Sol Gonzalez, Daniel Julián, Victoria Sol Caparelli


### OBJETIVO 

Presentar a través de un proyecto basado en Arduino, las temáticas que se brindaron a lo largo de la cursada, 
logrando mediante la praxis que el alumnado ponga en práctica los conocimientos teóricos adquiridos durante el 
trayecto del cuatrimestre. 

### PRESENTACION  

El proyecto realizado por los alumnos se basa en un brazo robótico controlado esencialmente por: 

Sensores flexibles creados por los estudiantes 

Servos (Servo Tower Pro Sg90 9g) 

Acelerómetro 

Arduino  

### MODO DE FUNCIONAMIENTO 

El modo de funcionamiento se basa en un guante que posee sensores flexibles, los cuales actúan como  una resistencia
variable. Por esto último, se puede controlar la tensión que tiene cada uno, leyendo el valor analógico a través de
los pines de Arduino. 

Al contar con estos valores, se puede controlar el movimiento de los dedos, estableciendo parámetros, obtenidos
mediante un promedio. Una vez establecidos los valores, se envían órdenes para el movimiento de los servos.  

Además de controlar los dedos de la mano, se puede realizar un control de lo que es el antebrazo por medio del giroscopio
y el acelerómetro.



