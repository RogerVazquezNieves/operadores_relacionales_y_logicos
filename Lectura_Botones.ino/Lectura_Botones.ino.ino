//Bibliotecas
#include "DHT.h"

// Digital pin connected to the DHT sensor
#define DHTPIN 12 

// Uncomment whatever type you're using!
#define DHTTYPE DHT11

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

//Constantes
const int BOTON1=13;
const int BOTON2=15;
const int BOTON3=14;
const int LED1 = 2;
const int LED2 = 4;
const int TEMP_HIGH=28;

//Variables
int dato1, dato2, dato3;

//Definicion de objetos

//Condiciones iniciales

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  
  pinMode(BOTON1, INPUT_PULLUP);
  pinMode(BOTON2, INPUT_PULLUP);
  pinMode(BOTON3, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  
  // put your main code here, to run repeatedly:
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  //Read buttons
  dato1 = digitalRead(BOTON1);
  dato2 = digitalRead(BOTON2);
  dato3 = digitalRead(BOTON3);

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  Serial.print(hic);
  Serial.println(F("°C"));
  
  Serial.print(F("Refrigeración Manual (Led Azul)"));
  if (dato1==0) {
    Serial.println(F("Encendido"));
    digitalWrite(LED1, HIGH);
  }
  else {
    Serial.println(F("Apagado"));
    digitalWrite(LED1, LOW);
  }

  Serial.print(F("Refrigeración Automatica Temp (Led Verde)"));
  if (hic>TEMP_HIGH || dato2==0 || dato3==0) {
    Serial.println(F("Encendido"));
    digitalWrite(LED2, HIGH);
  }
  else {
    Serial.println(F("Apagado"));
    digitalWrite(LED2, LOW);
  }
  

}
