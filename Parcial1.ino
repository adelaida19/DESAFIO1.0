#define led 2
#define bpulsar 12

//const int led =2; // indica que el led está conectado al pin 2
//const int bpulsar =12;
int boton;  // // se declara la variable boton
void setup() { 
  pinMode(bpulsar,INPUT); // se declara el pin 12 como entrada
  pinMode(led, OUTPUT);
  Serial.begin(9600);// se declara el pin 2 como salida
} 
void loop() {
  boton=digitalRead(bpulsar);  //se asigna a la variable “boton” el valor del pin 12
  // // el led se enciende o no de acuerdo al valor del push button 
  Serial.println(boton);
  if(boton==LOW){
  	digitalWrite(led,HIGH); 
  }else{
   digitalWrite(led,LOW); 
  }
}


//1. sensar los datos en un arreglo que este en un for, inicia
//con el pulsador y para con el mismo pulasador
//2. cuando inicies inicies el sensado invoca la funcion milis y guardas el tiempo en una variable
//3. medir period
//4. en el arreglo buscar el numero mayor y dividirlo por 100

