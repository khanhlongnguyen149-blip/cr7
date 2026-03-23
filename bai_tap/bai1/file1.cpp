#include <Arduino.h>

const int hang[] = {4, 5};        
const int cot[] = {7, 15, 16};   
const int led[] = {17, 18, 8, 3, 9}; 

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 5; i++) pinMode(led[i], OUTPUT);
  for (int i = 0; i < 2; i++) {
    pinMode(hang[i], OUTPUT);
    digitalWrite(hang[i], HIGH); 
  }
  for (int i = 0; i < 3; i++) pinMode(cot[i], INPUT_PULLUP);
}

void loop() {
  for (int r = 0; r < 2; r++) {    
    digitalWrite(hang[r], LOW);   

    for (int c = 0; c < 3; c++) {    
      if (digitalRead(cot[c]) == LOW) { 
        
        int nut = (r * 3) + c + 1; 
        Serial.print("Nút đã nhấn: "); Serial.println(nut);

        for(int l=0; l<5; l++) digitalWrite(led[l], LOW);
        if (nut <= 5) digitalWrite(led[nut - 1], HIGH);

        while(digitalRead(cot[c]) == LOW); 
        delay(50);
      }
    }
    digitalWrite(hang[r], HIGH);
  }
}
