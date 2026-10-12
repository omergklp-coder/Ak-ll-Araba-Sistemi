# 🚗 Arduino Kontrollü Akıllı Robot Araba

Bu proje, Arduino tabanlı, hem otonom hem de manuel olarak kontrol edilebilen bir akıllı robot araba sistemidir. C/C++ ile geliştirilen bu araç, çevresindeki engelleri algılayarak çarpışmaları önleyebilir ve aynı zamanda kızılötesi (IR) kumanda ile uzaktan yönlendirilebilir.

## 🌟 Özellikler

- **Uzaktan Kontrol:** IR (Kızılötesi) kumanda ile ileri, geri, sağa ve sola manuel yönlendirme.
- **Engelden Kaçma:** Ultrasonik mesafe sensörü sayesinde önüne çıkan engelleri algılar ve çarpışmadan yönünü değiştirir.
- **Dinamik Motor Kontrolü:** L298N motor sürücü entegresi ile DC motorların hız ve yön kontrolü sorunsuz bir şekilde sağlanır.

## 🛠️ Kullanılan Donanımlar

- Arduino (Uno/Nano/Mega)
- L298N Motor Sürücü Kartı
- HC-SR04 Ultrasonik Mesafe Sensörü
- IR Alıcı Modül ve Kumanda
- DC Motorlar ve Tekerlekler
- Robot Araba Şasesi
- Jumper Kablolar ve Güç Kaynağı (Pil/Batarya)

## 💻 Kullanılan Teknolojiler ve Kütüphaneler

- **Dil:** C / C++ (Arduino IDE)
- **Kütüphaneler:** 
  - `IRremote.h` (Kumanda sinyallerini işlemek için)
  - `NewPing.h` veya standart `PulseIn` (Mesafe sensörü için)

## 🚀 Kurulum ve Kullanım

1. **Devre Kurulumu:** Arduino, L298N motor sürücü, ultrasonik sensör ve IR alıcı bağlantılarını şemaya uygun olarak gerçekleştirin. 
2. **Kütüphaneleri Yükleme:** Arduino IDE üzerinden gerekli IR ve sensör kütüphanelerini kurun.
3. **Kodu Yükleme:** Proje dizinindeki `.ino` uzantılı dosyayı açın ve Arduino kartınıza yükleyin.
4. **Çalıştırma:** Güç bağlantısını yaptıktan sonra aracı yere bırakın ve kumanda ile kontrol etmeye başlayın!

## 📌 Geliştirici Notları

Bu proje, gömülü sistemler ve motor kontrol mantığını anlamak için geliştirilmiştir. İlerleyen aşamalarda Bluetooth (HC-05) modülü eklenerek mobil uygulama üzerinden kontrol sağlanabilir veya çizgi izleyen robot özelliklerine evrilebilir.
