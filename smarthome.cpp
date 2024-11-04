#include "BluetoothSerial.h"

bool flagC=0;
bool flagE=0;
bool flagB=0;
int valorLuz=0;
//*************************SENSOR DE PRESENÇA********************************
int pirCorredor = 34;       
int pirEscada = 35;
int pirBanheiro = 33;
//*************************SENSOR DE LUMINOSIDADE********************************
int sensorLuz = 4;
//*************************LED DO COMÔDO*************************************
int ledQuarto = 14; 
int ledCozinha = 18; 
int ledSala = 5; 
int ledBanheiro = 15; 
int ledCorredor = 27; 
//*************************LED ESPECIAIS*************************************
int ledEscada = 13; 
int ledVaranda = 19; 
//*************************RELE**********************************************
int releVentilador = 12;


String device_name = "SH-2";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void setup() {

  Serial.begin(115200);
  SerialBT.begin(device_name);  //Bluetooth device name
  //************************Definições dos pinos de saida***************************************************
  pinMode(27, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  //************************Definições dos pinos de entrada***************************************************
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  pinMode(33, INPUT);
  
}

void loop() {
   //*Lógica do LDR
  valorLuz = analogRead(sensorLuz);    
  Serial.println ("Valor Analogico:");
  Serial.println (valorLuz);
  
  if(valorLuz<750)
  {               
    digitalWrite(ledVaranda,HIGH);
    delay(1000);
  }
  else
  {    
                   
    digitalWrite(ledVaranda,LOW);
    delay(1000); 
  }

  char DADOS;
  DADOS = SerialBT.read();
  //*Lógica do sensor do corredor
  if(digitalRead(pirCorredor)==HIGH && (flagC==0))
  {
    flagC=1;
    digitalWrite(ledCorredor,HIGH);
    Serial.println("Luz do corredor");
    delay(1000);
    
  }
  if(digitalRead(pirCorredor)==LOW && (flagC==1))
  {
    flagC=0;
    digitalWrite(ledCorredor,LOW);
    Serial.println("Desligar luz do corredor");
    
  }
  //**************************************
  
  //*Lógica do sensor da escada
  if(digitalRead(pirEscada)==HIGH && (flagE==0))
  {
    flagE=1;
    digitalWrite(ledEscada,HIGH);
    Serial.println("Escada!Cuidado");
    delay(1000);
    
  }
  if(digitalRead(pirEscada)==LOW && (flagE==1))
  {
    flagE=0;
    digitalWrite(ledEscada,LOW);
    Serial.println("Desligar luz da escada");
    
  }
  //**************************************

  //*Lógica do sensor do banheiro
  if(digitalRead(pirBanheiro)==HIGH && (flagB==0))
  {
    flagB=1;
    digitalWrite(ledBanheiro,HIGH);
    Serial.println("Luz do banheiro ligada");
    delay(1000);
    
  }
  if(digitalRead(pirBanheiro)==LOW && (flagB==1))
  {
    
    if(DADOS =='b' || DADOS ==' '){
    flagB=0;
    digitalWrite(ledBanheiro,LOW);
    Serial.println("Desligar luz do banheiro");
    }
    
  }
  //**************************************
  
  //*Lógica do sensor do quarto
  if(DADOS == 'Q' )
  {
    digitalWrite(ledQuarto, HIGH);
    Serial.println("Quarto Ligado");
  }
  if(DADOS =='q' )
  {
    digitalWrite(ledQuarto, LOW);
    Serial.println("Quarto desligado");
  }
  //**************************************

  //*Lógica do sensor da sala
  if(DADOS == 'S' )
  {
    digitalWrite(ledSala, HIGH);
    Serial.println("Sala Ligada");
  }
  if(DADOS =='s' )
  {
    digitalWrite(ledSala, LOW);
    Serial.println("Sala Desligada");
  }
  //**************************************

  //*Lógica do sensor da cozinha
  if(DADOS == 'C' )
  {
    digitalWrite(ledCozinha, HIGH);
    Serial.println("Quarto Ligado");
  }
  if(DADOS =='c' )
  {
    digitalWrite(ledCozinha, LOW);
    Serial.println("Quarto desligado");
  }
  //**************************************

  //*Lógica do sensor do banheiro
  if(DADOS == 'B' )
  {
    digitalWrite(ledBanheiro, HIGH);
    Serial.println("Quarto Ligado");
  }
  if(DADOS =='b' )
  {
    digitalWrite(ledBanheiro, LOW);
    Serial.println("Quarto desligado");
  }
  //**************************************

  //*Lógica do Ventilador
  if(DADOS == 'A' )
  {
    digitalWrite(releVentilador, HIGH);
    Serial.println("Ventilador ligado");
  }
  if(DADOS =='a' )
  {
    digitalWrite(releVentilador, LOW);
    Serial.println("Ventilador desligado");
  }
  //**************************************


  //**************************************
}
