#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd_1(0);

#define led 2
#define bpulsar 12
#define bprocesar 13
#define analogPin 0

void agregar(int *arreglo, int num, int nDatos);
void imprimir(int *arreglo, int n);
void copiar(int *origen, int *destino, int nDatos);
void amplitud(int *arreglo, int nDatos);

int num=0;
int nDatos=0;
int *ptrAd= nullptr;
int *aux = nullptr;
bool adquirir = false;
bool procesar = false;



void setup() { 
  pinMode(bpulsar,INPUT); // se declara el pin 12 como entrada
  pinMode(bprocesar,INPUT);
  Serial.begin(9600);// se declara el pin 2 como salida
  
  lcd_1.begin(16, 2);
  lcd_1.print("hello world");
} 

void loop() {
  if(digitalRead(bpulsar)==LOW){
    adquirir = true;
  }else if(digitalRead(bprocesar)==LOW){
  	adquirir = false;
    imprimir(ptrAd,nDatos);
    amplitud(ptrAd,nDatos);
  }
  
  if(adquirir==true){
    Serial.println("adquiriendo");
    if(nDatos==0){
      nDatos++;
      ptrAd= new int[nDatos];
      agregar(ptrAd,analogRead(analogPin), nDatos-1);

    }else{
      aux=new int[nDatos];
      copiar(ptrAd,aux,nDatos);

      delete[] ptrAd;
      ptrAd=nullptr;

      nDatos++;
      ptrAd=new int[nDatos];
      copiar(aux,ptrAd,nDatos-1);
      agregar(ptrAd,analogRead(analogPin), nDatos-1);
      delete[] aux;
      aux=nullptr;
    }
  }
}



void agregar(int *arreglo, int num, int nDatos){
    *(arreglo+nDatos)=num;
}

void imprimir(int *arreglo, int nDatos){
   Serial.println("imprimiendo");  
   if (nDatos==0) {
        Serial.println("Aun no hay datos");
    }
    for (int i = 0; i < nDatos; ++i) {
        Serial.println(*(arreglo+i));
    }
}

void copiar(int *origen, int *destino, int nDatos){
    for (int i = 0; i < nDatos; ++i) {
        *(destino+i) = *(origen+i);
    }
}

void amplitud(int *arreglo, int nDatos){
	int amplitud=0;				
  	for (int i = 0; i < nDatos; ++i) {
      if(*(arreglo+i) < 0){
        if((*(arreglo+i) * -1) > amplitud){
        	amplitud = *(arreglo+i);
          	amplitud = amplitud *(-1);
        }
      }else{
      	if(*(arreglo+i) > amplitud){
        	amplitud = *(arreglo+i);
        }
      }
    }
  	lcd_1.clear();
  	lcd_1.print("Amplitud: ");
  	lcd_1.setCursor(0, 1);
  	lcd_1.print(amplitud/100);
  	lcd_1.print(" V");
}