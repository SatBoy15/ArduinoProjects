/*
 * Meteo-Ino by Albi.
 * 
 * Modules: DHT11 or DHT22;
 *          Thermistor;
 *          Display 16x2.
 * 
 * Features: Read Temperature and Humidity;
 *           Prints it to the Display.
 * 
 * Version: 1.1 (8/Nov/2017)
 * 
 * ChangeLog: 1.0+First Build.
 *            1.1+Add Thermistor Compatibility and added Led.
 */
 
//  Include Libraries

#include <dht11.h>

#include <math.h>

#include <LiquidCrystal.h>

// Set Pins and Other

LiquidCrystal lcd(12,11,5,4,3,2);

dht11 DHT;

#define DHTPIN 8

int LedPin = 7;

// Setup Function

double Termistore(double PinAnalog){
  double Temp = log(10000.0*((1024.0/PinAnalog-1.0)));
  Temp = 1/(0.001129148 +(0.000234125 +(0.0000000876741 * Temp * Temp )) * Temp);
  Temp = Temp - 273.15;
  return Temp;
}

void UpTime(int cont){
  //Shows Up-time on Serial 9600.
  if(cont>=60){
    int minutes = cont/60;
    int sec = cont-(60*minutes);
    
    Serial.print("Tempo passato dall' Accensione: ");
    
    Serial.print(minutes);
    
    Serial.print(" minuti e ");
    
    Serial.print(sec);
    
    Serial.println(" Secondi");
    
    }else{
      
    Serial.print("Secondi passati dall' Accensione: ");
    
    Serial.println(cont);
    
    }
}
void setup() {
  
  // Initialise the Display
  
  lcd.begin(16,2);

  // Initialise Serial Interface
  
  Serial.begin(9600);
  
  // Print on display the first screen
  
  lcd.print(" Stazione Meteo ");
  
  lcd.setCursor(0,1);
  
  lcd.print("    by  Albi    ");
  
  delay(2000);

  // It writes on the display that it needs loading.
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(" Caricamento... ");
  lcd.setCursor(0,1);
  lcd.print("Attendere 2s...");

  // Lights the Led to tell it Works.
  digitalWrite(LedPin,HIGH);
  delay(500);
  digitalWrite(LedPin,LOW);
  delay(500);  
  digitalWrite(LedPin,HIGH);
  delay(500);
  digitalWrite(LedPin,LOW);
  delay(500);
  digitalWrite(LedPin,HIGH);
  //Set this point as UpTime Start
  int cont = 1;
}
void loop() {
  
  // Read Values from DHT Sensor and Clears Display
  
  DHT.read(DHTPIN);
  lcd.clear();

  // Shows Uptime on Serial
  
  UpTime(cont);
  
  // Writes on display Temperature...
  
  lcd.setCursor(0,0);
  lcd.print("Temperat= ");
  lcd.print(Termistore(analogRead(0)));
  //lcd.print(DHT.temperature);
  lcd.print("C");

  // ... and Humidity.
  lcd.setCursor(0,1);
  lcd.print("Umidita = ");
  lcd.print(DHT.humidity);
  lcd.print(" %");

  // It stops 2 seconds and then restarts the loop and blinks the led.
  digitalWrite(LedPin,LOW);
  delay(250);
  digitalWrite(LedPin,HIGH);
  delay(1750);
  cont += 2;
}
