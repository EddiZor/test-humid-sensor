#include <Arduino.h>

const int sensorPin = A0; // Pin analogico a cui è collegato il sensore

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Attesa connessione seriale (utile per schede con USB nativa)
  }
  Serial.println("=== TEST SENSORE UMIDITA' TERRENO CAPACITIVO ===");
  Serial.println("Tieni il sensore all'asciutto, poi prova a toccare la parte inferiore con un dito umido o a immergerla leggermente in acqua.");
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  
  // Stampa il valore letto dal convertitore analogico-digitale (ADC 10-bit: da 0 a 1023)
  Serial.print("Valore Analogico letto: ");
  Serial.print(sensorValue);
  
  // Diagnostica di base sullo stato del sensore
  if (sensorValue <= 5) {
    Serial.print(" -> [ATTENZIONE] Valore vicino a 0: Possibile cortocircuito o pin scollegato/rotto.");
  } else if (sensorValue >= 1020) {
    Serial.print(" -> [ATTENZIONE] Valore al massimo (1023): Circuito aperto o sensore guasto (nessun segnale).");
  } else {
    Serial.print(" -> [OK] Il sensore sta rispondendo e leggendo una tensione valida.");
  }
  
  Serial.println();
  delay(500);
}