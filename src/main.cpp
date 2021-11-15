#include <Arduino.h>
#include <M5StickCPlus.h>

uint32_t rx_len = 0;
uint32_t tx_len = 0;

void print_counter(uint32_t rx, uint32_t tx)
{
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.printf("UL: %u", tx_len);
  M5.Lcd.setCursor(0, 50);
  M5.Lcd.printf("DL: %u", rx_len);
}

void setup()
{
  // put your setup code here, to run once:
  m5.begin();
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 33, 32);
  Serial.setRxBufferSize(128);
  Serial2.setRxBufferSize(128);

  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);

  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setTextSize(2);

  M5.Lcd.setCursor(0, 10);
  M5.Lcd.printf("Serial Passthrough");

  print_counter(rx_len, tx_len);
}

void loop()
{
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0 || Serial2.available() > 0)
  {
    if (Serial.available() > 0)
    {
      rx_len += Serial2.write(Serial.read());
    }

    if (Serial2.available() > 0)
    {
      tx_len += Serial.write(Serial2.read());
    }
  }

  if (M5.BtnA.read())
  {
    rx_len = 0;
    tx_len = 0;
    M5.Lcd.setCursor(0, 100);
    M5.Lcd.printf("DL:             ");
    M5.Lcd.setCursor(0, 50);
    M5.Lcd.printf("UL:             ");
  }
  
  print_counter(rx_len, tx_len);
}
