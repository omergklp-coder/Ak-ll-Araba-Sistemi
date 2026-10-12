#include <IRremote.h>

// pin tanımları
const int ir_PIN = 4; 

// motor pinleri
const int sagMotorIleri = 5;  
const int sagMotorGeri = 6;   
const int solMotorIleri = 7;  
const int solMotorGeri = 8;   

//  Park Sensörü Pinleri
const int trigPin = 3;
const int echoPin = 2;

// güvenlik parametreleri
const int mesafeKritik = 4;     //  4 cm kala GERİ vites kilitlenir
unsigned long eskiZaman = 0;
long anlikMesafe = 100;         

unsigned long sonSinyalZamani = 0;
const int sinyalZamanAsimi = 250; 

int enSonKomut = 0; 

void setup() {
  Serial.begin(9600);
  
  pinMode(solMotorIleri, OUTPUT);
  pinMode(solMotorGeri, OUTPUT);
  pinMode(sagMotorIleri, OUTPUT);
  pinMode(sagMotorGeri, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  arabaDur();
  IrReceiver.begin(ir_PIN, ENABLE_LED_FEEDBACK);
  
  Serial.println("==================================================");
  Serial.println("                    Araç Hazır                    ");
  Serial.println("==================================================");
}

void loop() {
  unsigned long simdikiZaman = millis();

  // sadece geri komutunda güvenlik durumu
  if (enSonKomut == 0x52) { 
    if (simdikiZaman - eskiZaman >= 60) { 
      eskiZaman = simdikiZaman;
      anlikMesafe = mesafeOlce();

      // Sadece kritik bölgedeyken (10 cm altı) 
      if (anlikMesafe > 0 && anlikMesafe <= 10) {
        Serial.print(">> [Geri Vites] Sensör Mesafesi: ");
        Serial.print(anlikMesafe);
        Serial.println(" cm");
      }
    }
  } else {
    anlikMesafe = 100; // İleri veya Durma konumunda mesafeyi güvenli eşiğe çek
  }

  // KUMANDADAN BAĞIMSIZ MUTLAK ACİL FREN 
  if (enSonKomut == 0x52 && anlikMesafe > 0 && anlikMesafe <= mesafeKritik) {
    arabaDur(); 
    enSonKomut = 0; 
    Serial.println(" ACIL FREN DEVREDE: Arkada engel var, motorlar KILITLENDI!");
  }

  //  KUMANDA SİNYAL YAKALAMA VE HAREKET
  if (IrReceiver.decode()) { 
                                                                                                                                                                                                                        
                                                                                                                                                                                                                        
    int kumandaKomutu = IrReceiver.decodedIRData.command;
    
    // Tuşa basılı tutulduğunda hafızadaki yönü devam ettir
    if (kumandaKomutu == 0 || IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
      kumandaKomutu = enSonKomut; 
    }

    if (kumandaKomutu != 0) {
      sonSinyalZamani = simdikiZaman; 
      
      //  İLERİ (0x18)
      if (kumandaKomutu == 0x18) { 
        enSonKomut = kumandaKomutu;
        arabaIleri(); 
        Serial.println("Kumanda: ILERI");
      } 
      
      // GERİ (0x52)
      else if (kumandaKomutu == 0x52) { 
        if (anlikMesafe > 0 && anlikMesafe <= mesafeKritik) {
          arabaDur();
          enSonKomut = 0;
          Serial.println("ENGEL UYARISI: Yol kapali, geri gidilemez!");
        } else {
          enSonKomut = kumandaKomutu;
          arabaGeri(); 
          Serial.println("Kumanda: GERI");
        }
      }
      
      //  SAĞ (0x5A) -> Sadece sol motorlar çalışır
      else if (kumandaKomutu == 0x5A) { 
        enSonKomut = kumandaKomutu;
        arabaSag();
        Serial.println("Kumanda: SAGA DONUS");
      } 
      
      //  SOL (0x8) -> Sadece sağ motorlar çalışır
      else if (kumandaKomutu == 0x8) { 
        enSonKomut = kumandaKomutu;
        arabaSol();
        Serial.println("Kumanda: SOLA DONUS");
      }
    }
    IrReceiver.resume(); 
  }

  //   Parmağını tuştan çektiğinde durur
  if (simdikiZaman - sonSinyalZamani > sinyalZamanAsimi) {
    arabaDur(); 
    enSonKomut = 0; 
  }
}

//  MOTOR KONTROL FONKSİYONLARI 

void arabaIleri() {
  digitalWrite(solMotorIleri, HIGH);
  digitalWrite(solMotorGeri, LOW);
  digitalWrite(sagMotorIleri, HIGH);
  digitalWrite(sagMotorGeri, LOW);
}

void arabaGeri() {
  digitalWrite(solMotorIleri, LOW);
  digitalWrite(solMotorGeri, HIGH);
  digitalWrite(sagMotorIleri, LOW);
  digitalWrite(sagMotorGeri, HIGH);
}

void arabaSag() {
  digitalWrite(solMotorIleri, HIGH);
  digitalWrite(solMotorGeri, LOW);
  digitalWrite(sagMotorIleri, LOW);
  digitalWrite(sagMotorGeri, LOW);
}

void arabaSol() {
  digitalWrite(solMotorIleri, LOW);
  digitalWrite(solMotorGeri, LOW);
  digitalWrite(sagMotorIleri, HIGH);
  digitalWrite(sagMotorGeri, LOW);
}

void arabaDur() {
  digitalWrite(solMotorIleri, LOW);
  digitalWrite(solMotorGeri, LOW);
  digitalWrite(sagMotorIleri, LOW);
  digitalWrite(sagMotorGeri, LOW);
}

// park sensör
long mesafeOlce() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long sure = pulseIn(echoPin, HIGH, 20000); 
  long mesafe = sure * 0.034 / 2;
  
  if (mesafe <= 0 || mesafe > 200) {
    return 0; 
  }
  return mesafe;
}