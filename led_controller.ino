#include <Adafruit_NeoPixel.h>
#include "color_step.h" 

#define PIN 6       //信号端子のピン番号
#define LED_NUM 64  //LEDの数
 
Adafruit_NeoPixel ledtape = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);
//3つめのパラメータは使うLEDテープの制御ICがWS2812ならNEO_KHZ800 / WS2811ならNEO_KHZ400

void set_colors(uint32_t colors[4])
{
  for(int i=0;i<4;i++) {
    for(int j=0;j<16;j++) {
      int id = i * 16 + j;
      ledtape.setPixelColor(id, colors[i]);
    }
  }
  ledtape.show();
}

uint32_t get_color(int id, float t)
{
  float interval = 1;
  int step = t / interval + id;
  float angle = fmod(t / interval, 1.0) * 3.1415926535;

  int step1 = step % step_max;
  float gain1 = (cos(angle) + 1) / 2.0;
  uint32_t c1 = color_step[step1];
  uint8_t r1 = ((c1 >> 16) & 0xff) * gain1;
  uint8_t g1 = ((c1 >>  8) & 0xff) * gain1;
  uint8_t b1 = ((c1 >>  0) & 0xff) * gain1;

  int step2 = (step + 1) %step_max;
  float gain2 = 1.0 - gain1;
  uint32_t c2 = color_step[step2];
  uint8_t r2 = ((c2 >> 16) & 0xff) * gain2;
  uint8_t g2 = ((c2 >>  8) & 0xff) * gain2;
  uint8_t b2 = ((c2 >>  0) & 0xff) * gain2;

  uint8_t r = r1 + r2;
  uint8_t g = g1 + g2;
  uint8_t b = b1 + b2;

  if(id == 0){
    Serial.print(b +   0);
    Serial.print(", ");
    Serial.print(r + 600);
    Serial.print(", ");
    Serial.print(g + 300);
    Serial.print(", ");
    Serial.print(900);
    Serial.print(", ");
    Serial.println("");
  }

  return(ledtape.Color(r, g, b));
}
 
void setup() {
  ledtape.begin();
  ledtape.show();   //一旦全てOFFの状態で反映
  Serial.begin(115200);
}

void loop() {
  float t = float(millis()) / 1000;

  uint32_t colors[4];
  for(int i=0;i<4;i++){
    colors[i] = get_color(i, t);
  }
  set_colors(colors);

  delay(10);
}
