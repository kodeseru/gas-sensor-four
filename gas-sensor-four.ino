#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD I2C dengan alamat yang sesuai (sesuaikan jika perlu)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat I2C untuk LCD

// Pin untuk sensor gas dan buzzer
const int GAS_SENSOR_PIN = A0;  // Pin analog untuk sensor gas
const int BUZZER_PIN = 8;      // Pin digital untuk buzzer

// Variabel untuk menyimpan nilai dari sensor gas
int gasValue;

void setup() {
  // Inisialisasi Serial Monitor untuk debugging
  Serial.begin(9600);

  // Inisialisasi pin buzzer sebagai output
  pinMode(BUZZER_PIN, OUTPUT);

  // Inisialisasi LCD
  lcd.begin(16, 2);   // Mengatur LCD dengan ukuran 16 kolom dan 2 baris
  lcd.init();         // Inisialisasi LCD
  lcd.backlight();    // Menyalakan backlight LCD
}

void loop() {
  // Membaca nilai dari sensor gas
  gasValue = analogRead(GAS_SENSOR_PIN);

  // Menampilkan nilai gas di Serial Monitor
  Serial.print("Nilai Gas: ");
  Serial.println(gasValue);

  // Menampilkan nilai gas di LCD
  lcd.clear();
  lcd.setCursor(0, 0);  // Menampilkan di baris pertama
  lcd.print("Gas Level: ");
  lcd.print(gasValue);

  // Mengatur tingkat gas, jika melewati batas tertentu
  if (gasValue > 500) {  // Misalnya, jika gas melebihi nilai 400
    lcd.setCursor(0, 1);  // Menampilkan di baris kedua
    lcd.print("Bahaya!");
    digitalWrite(BUZZER_PIN, HIGH);  // Menyalakan buzzer
  } else {
    lcd.setCursor(0, 1);  // Menampilkan di baris kedua
    lcd.print("Aman");
    digitalWrite(BUZZER_PIN, LOW);  // Mematikan buzzer
  }

  // Menunggu 500 ms sebelum pembacaan berikutnya
  delay(500);
}
