#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd_1(0);

#define led 2
#define bpulsar 12
#define bprocesar 13
#define analogPin 0

//tipo dato(void, int, float...) nombre()
void agregar(int *arreglo, int num, int nDatos);
void imprimir(int *arreglo, int n);
void copiar(int *origen, int *destino, int nDatos);
int offset(int *arreglo, int nDatos);
void amplitud(int *arreglo, int nDatos);

int num=0; //guarda el valor del generador de señales
int nDatos=0; //cantidad de datos en el heap
int *ptrAd= nullptr; //puntero que almacena los nDatos
int *aux = nullptr; //puntero que ayuda a cambiar el tamaño de datos

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
      ptrAd= new int[nDatos]; //creamos arreglo tipo enteros
      agregar(ptrAd,analogRead(analogPin), nDatos-1);

    }else{
      aux=new int[nDatos];
      copiar(ptrAd,aux,nDatos); //guardamos la información actual para soicitar mas espacio de memoria

      delete[] ptrAd; //borramos la memoria reservada actualmente 
      ptrAd=nullptr; //hacemos que no sea un puntero peligroso

      nDatos++; //incrementamos la cantidad de datos para solicitar nueva memoria
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

int offset(int *arreglo, int nDatos){
	int mayor=0;
    int menor=0;
  for(int i=0;i<nDatos; i++){
    if (*(arreglo+i)> mayor){
    	mayor=*(arreglo+i);
    }
    if (*(arreglo+i)<menor){
    	menor=*(arreglo+i);
    }
  }
  
  Serial.println("mayor:");
  Serial.println(mayor);
  
  Serial.println("menor:");
  Serial.println(menor);
  
  int ff= menor+mayor;  
  if (ff>-100 && ff<100){
    return 0;
  }
  else {
    Serial.println("offset:");
  	Serial.println(ff/2);
  	return (ff/2);
  }
  
}

void amplitud(int *arreglo, int nDatos){
	float amplitud=0;				
  	for (int i = 0; i < nDatos; ++i) {
      if(*(arreglo+i) < 0){ //pregunto si es negativo
        if((*(arreglo+i) * -1) > amplitud){// si lo es lo comparo con amplitud y miro si es mayor
        	amplitud = *(arreglo+i);// si es mayor, amplitud se actualiza con el valor del puntero
          	amplitud = amplitud *(-1);// como era negativo lo hacemos positivo
        }
      }else{
      	if(*(arreglo+i) > amplitud){//pregunto si es positivo y mayor para actualizar amplitud
        	amplitud = *(arreglo+i);
        }
      }
    }
  	Serial.println("amplitud:");
  	Serial.println(amplitud);
  	int ff = 0;
    ff = offset(arreglo, nDatos);
  	amplitud=amplitud-ff;
  
  	lcd_1.clear(); //borra el display
    lcd_1.setCursor(0, 0);
  	lcd_1.print("Amplitud: ");
  	lcd_1.setCursor(0, 1);
  	lcd_1.print(amplitud/100);
  	lcd_1.print(" V");
}
