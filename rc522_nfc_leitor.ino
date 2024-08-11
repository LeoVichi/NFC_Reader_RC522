/*
Author: L3nny_P34s4n7
Email: contact@leonardovichi.com
Date: 2024-08-10
License: MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

CONNECTIONS
-----------

RC522 RFID NFC
SDA  -> D10
SCK  -> D13
MOSI -> D11
MISO -> D12
RST  -> D9
GND  -> GND
3.3V -> 3.3V

*/

#include <SPI.h>
#include <MFRC522.h>

// Definindo os pinos utilizados para SPI
#define SS_PIN 10
#define RST_PIN 9

// Inicializando o MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup(void) {
  Serial.begin(115200);
  SPI.begin();       // Inicia a interface SPI
  mfrc522.PCD_Init(); // Inicia o RC522
  Serial.println("Inicializando RC522...");

  Serial.println("Esperando por um cartão NFC...");
}

void loop(void) {
  // Verifica se um novo cartão está presente
  if (!mfrc522.PICC_IsNewCardPresent()) {
    delay(1000);
    return;
  }

  // Seleciona um dos cartões presentes
  if (!mfrc522.PICC_ReadCardSerial()) {
    delay(1000);
    return;
  }

  Serial.println("Cartão NFC encontrado!");

  // Imprimindo o UID
  Serial.print("UID: ");
  for (uint8_t i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Identificando o tipo de cartão
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.print("Tipo de cartão: ");
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

  if (piccType == MFRC522::PICC_TYPE_MIFARE_UL) {
    Serial.println("Cartão NTAG213/215/216 detectado!");

    // Leitura de uma página do NTAG (4 bytes por página)
    byte buffer[18];
    byte size = sizeof(buffer);
    for (byte page = 4; page < 8; page++) {  // Lendo as páginas 4 a 7 (16 bytes)
      if (mfrc522.MIFARE_Read(page, buffer, &size) == MFRC522::STATUS_OK) {
        Serial.print("Página "); 
        Serial.print(page); 
        Serial.print(": ");
        for (uint8_t i = 0; i < 4; i++) {
          Serial.print(buffer[i], HEX);
          Serial.print(" ");
        }
        Serial.println();
      } else {
        Serial.print("Falha na leitura da página ");
        Serial.println(page);
      }
    }
  } else {
    Serial.println("Tipo de cartão não suportado para leitura de NTAG.");
  }

  Serial.println("----- Fim das Informações do Cartão -----\n");
  mfrc522.PICC_HaltA(); // Para a comunicação com o cartão
  delay(2000);
}
