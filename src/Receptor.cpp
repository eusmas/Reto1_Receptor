//Reto #1 Control Banda - Receptor
//Lenguajes tecnicos de programacion
//Esteban Usma Sierra
//2021-2
#include <Arduino.h>
#include <SoftwareSerial.h>

int sensor_s1 = 30;
int sensor_s2 = 31;
int sensor_s3 = 32;
int sensor_s4 = 33;
int giro_der = 22;
int giro_izq = 23;
int pos_actual=0, pos_inicial=0;
int dato=0;
int destino, tiempo, inicio, cancelar;
int paso=0;


void setup() {
  pinMode(sensor_s1, INPUT);
  pinMode(sensor_s2, INPUT);
  pinMode(sensor_s3, INPUT);
  pinMode(sensor_s4, INPUT);
  pinMode(giro_der,OUTPUT);
  pinMode(giro_izq,OUTPUT);
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial3.print("f");
}

void loop() {
  //Lectura y almacenamiento de la posicion actual del objeto
  if(digitalRead(sensor_s1)==HIGH){
    pos_actual=1;   
    }
  if(digitalRead(sensor_s2)==HIGH){
    pos_actual=2;    
    }
  if(digitalRead(sensor_s3)==HIGH){
    pos_actual=3;    
    }    
  if(digitalRead(sensor_s4)==HIGH){
    pos_actual=4;    
    }
  Serial.println(pos_actual);

  //envios seriales para verificacion de datos  
  Serial.print(destino);
  Serial.print(tiempo);
  Serial.print(inicio);
  Serial.println(cancelar);
  delay(200);

  //_________________________________
  if(cancelar==0 && inicio==1){             //inicio de secuencia

    digitalWrite(giro_der,LOW);  
    digitalWrite(giro_izq,LOW);

    if(pos_actual<destino){                 //Giro a la izquierda
      digitalWrite(giro_izq,HIGH);
      Serial3.print("i");                   //envia una i cuando quira a la izquierda   
      }

    if(pos_actual>destino){                 //Giro a la derecha
      digitalWrite(giro_der,HIGH);
      Serial3.print("d");                   //envia una d cuando gira a la derecha
      }
    
    if(pos_actual==destino){                //objeto llego al destino
      digitalWrite(giro_der,LOW);  
      digitalWrite(giro_izq,LOW);
      destino=0; 
      if(paso<1){
        delay(tiempo*1000);
        }
      destino=pos_inicial;                  //asigna el punto de partida como el nuevo destino
      paso++;
      }
  
    if(paso>1){                             //paso que indica que el objeto ya fue al destino y regreso al origen
      digitalWrite(giro_der,LOW);  
      digitalWrite(giro_izq,LOW);
      destino=0;
      tiempo=0;
      inicio=0; 
      Serial.println("f");
      Serial3.print("f");
      }
}

 if(cancelar==1){                   //secuencia de cancelacion de movimiento
  digitalWrite(giro_der,LOW);  
  digitalWrite(giro_izq,LOW);
  destino=pos_inicial;
  if(pos_actual<destino){
    digitalWrite(giro_izq,HIGH);
    Serial3.print("i");      
    }
  if(pos_actual>destino){
    digitalWrite(giro_der,HIGH);
    Serial3.print("i");      
    }
  if(pos_actual==destino){
    digitalWrite(giro_der,LOW);  
    digitalWrite(giro_izq,LOW);
    destino=0;
    tiempo=0;
    inicio=0;
    Serial.println("f");
    Serial3.print("f");
    }
  }
}

void serialEvent3 ()  {         //evento serial, lee el dato y lo convierte en numero separados
  dato= Serial3.parseInt();
 
  if(dato==0) 
  {
    cancelar=1;
  }else{
    cancelar=0;
  destino=dato/100;
  tiempo=(dato-(destino*100))/10;
  inicio=dato-(destino*100)-(tiempo*10);
  pos_inicial=pos_actual;
  paso=0;
  }
}
 
