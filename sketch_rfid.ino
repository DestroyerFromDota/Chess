#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10  // Пин SDA
#define RST_PIN 9  // Пин RST

MFRC522 rfid(SS_PIN, RST_PIN); // Создаем объект MFRC522

void setup() {
  Serial.begin(9600); // Инициализация последовательного порта
  SPI.begin();        // Инициализация SPI
  rfid.PCD_Init();    // Инициализация MFRC522
  Serial.println("Поднесите RFID-карту к ридеру...");
}

void loop() {
  // Проверка на наличие карты
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // Выводим UID карты в последовательный монитор
    Serial.print("UID карты: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    // Завершаем чтение карты
    rfid.PICC_HaltA();
  }
}
