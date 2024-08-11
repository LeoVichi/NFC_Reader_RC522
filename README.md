# NFC_Reader_RC522a# Leitor NFC com RC522

Este projeto é um leitor NFC usando o módulo RC522. O código permite a leitura de cartões NFC, especialmente os cartões NTAG213/215/216, e exibe as informações no monitor serial.

## Como Usar

1. **Clone o repositório:**

   ```bash
   git clone https://github.com/LeoVichi/NFC_Reader_RC522.git
   cd rc522-nfc-leitor
   ```

2. **Configuração do Hardware:**

   Conecte o RC522 ao microcontrolador usando SPI:
   - **RC522 RFID NFC:**
     - SDA  -> D10
     - SCK  -> D13
     - MOSI -> D11
     - MISO -> D12
     - RST  -> D9
     - GND  -> GND
     - 3.3V -> 3.3V

3. **Bibliotecas Necessárias:**

   Certifique-se de que as seguintes bibliotecas estejam instaladas:
   - `MFRC522`
   - `SPI`

   Estas bibliotecas podem ser instaladas através do Gerenciador de Bibliotecas da Arduino IDE.

4. **Carregue o Código:**

   Abra o arquivo `rc522_nfc_leitor.ino` no Arduino IDE e carregue-o no microcontrolador.

5. **Funcionamento:**

   - O código inicializa o módulo RC522 e espera por um cartão NFC.
   - Quando um cartão NFC é detectado, o UID e outras informações são exibidas no monitor serial.
   - Se um cartão NTAG213/215/216 for detectado, os dados das páginas 4 a 7 são lidos e exibidos.

## Licença

Este projeto é licenciado sob os termos da licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.

## Autor

- **L3nny_P34s4n7**
- **Email:** contact@leonardovichi.com
