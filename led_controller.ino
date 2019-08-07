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
  float angle = fmod(t / interval, 1.0) * 2.0 * 3.1415926535;
  step %= step_max;

  hsv c = color_step[step];
  uint8_t val = c.val * (1 - cos(angle)) / 2.0;
  return(ledtape.ColorHSV(c.hue, c.sat, val));
}
 
void setup() {
  ledtape.begin();
  ledtape.show();   //一旦全てOFFの状態で反映
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
