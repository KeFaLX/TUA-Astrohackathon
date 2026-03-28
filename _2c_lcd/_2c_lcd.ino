// ================================================
//  Arduino UNO - I2C LCD + 2x RGB LED
//  Sabit sıcaklık ve nem değerleri
//  LED 1: Sıcaklığa göre renk değişir
//  LED 2: Neme göre renk değişir
// ================================================

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Ayarları (Adres: 0x27, 16 sütun, 2 satır)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---- SABİT DEĞERLER (istediğiniz gibi değiştirin) ----
float sicaklik = 24.5;   // Sıcaklık (°C)
float nem      = 55.0;   // Nem (%)

// ---- RGB LED 1 Pin Tanımları (Sıcaklık) ----
#define LED1_R  3    // Kırmızı  → D3 (PWM)
#define LED1_G  5    // Yeşil    → D5 (PWM)
#define LED1_B  6    // Mavi     → D6 (PWM)

// ---- RGB LED 2 Pin Tanımları (Nem) ----
#define LED2_R  9    // Kırmızı  → D9 (PWM)
#define LED2_G  10   // Yeşil    → D10 (PWM)
#define LED2_B  11   // Mavi     → D11 (PWM)

// Derece (°) özel karakter tanımı
byte derece[] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

// RGB LED renk ayar fonksiyonu
void setLedColor(int pinR, int pinG, int pinB, int r, int g, int b) {
  analogWrite(pinR, r);
  analogWrite(pinG, g);
  analogWrite(pinB, b);
}

void setup() {
  // LED pinlerini çıkış olarak ayarla
  pinMode(LED1_R, OUTPUT);
  pinMode(LED1_G, OUTPUT);
  pinMode(LED1_B, OUTPUT);
  pinMode(LED2_R, OUTPUT);
  pinMode(LED2_G, OUTPUT);
  pinMode(LED2_B, OUTPUT);

  // LCD'yi başlat
  lcd.init();
  lcd.backlight();

  // Özel derece karakterini kaydet
  lcd.createChar(0, derece);

  // --- 1. Satır: Sıcaklık ---
  lcd.setCursor(0, 0);
  lcd.print("Sicaklik:");
  lcd.print(sicaklik, 1);
  lcd.write(0);  // ° sembolü
  lcd.print("C");

  // --- 2. Satır: Nem ---
  lcd.setCursor(0, 1);
  lcd.print("Nem:     %");
  lcd.print(nem, 1);

  // ---- LED 1: Sıcaklığa göre renk ----
  if (sicaklik < 18) {
    // Soğuk → MAVİ
    setLedColor(LED1_R, LED1_G, LED1_B, 0, 0, 255);
  }
  else if (sicaklik <= 28) {
    // Normal → YEŞİL
    setLedColor(LED1_R, LED1_G, LED1_B, 0, 255, 0);
  }
  else {
    // Sıcak → KIRMIZI
    setLedColor(LED1_R, LED1_G, LED1_B, 255, 0, 0);
  }

  // ---- LED 2: Neme göre renk ----
  if (nem < 30) {
    // Kuru → SARI
    setLedColor(LED2_R, LED2_G, LED2_B, 255, 255, 0);
  }
  else if (nem <= 60) {
    // Normal → MAVİ
    setLedColor(LED2_R, LED2_G, LED2_B, 0, 100, 255);
  }
  else {
    // Nemli → MOR
    setLedColor(LED2_R, LED2_G, LED2_B, 180, 0, 255);
  }
}

void loop() {
  // LED pinlerini çıkış olarak ayarla
  pinMode(LED1_R, OUTPUT);
  pinMode(LED1_G, OUTPUT);
  pinMode(LED1_B, OUTPUT);
  pinMode(LED2_R, OUTPUT);
  pinMode(LED2_G, OUTPUT);
  pinMode(LED2_B, OUTPUT);
}
