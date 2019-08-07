struct hsv{
  uint16_t hue;
  uint8_t sat;
  uint8_t val;
};

hsv color_step[] = {
  hsv{0x0000, 0,   0},
  hsv{0x0000, 0, 255},
  hsv{0x2000, 0,   0},
  hsv{0x2000, 0, 255},
  hsv{0x4000, 0,   0},
  hsv{0x4000, 0, 255},
  hsv{0x6000, 0,   0},
  hsv{0x6000, 0, 255},
  hsv{0x8000, 0,   0},
  hsv{0x8000, 0, 255},
  hsv{0xa000, 0,   0},
  hsv{0xa000, 0, 255},
  hsv{0xc000, 0,   0},
  hsv{0xc000, 0, 255},
  hsv{0xe000, 0,   0},
  hsv{0xe000, 0, 255},
};

int step_max = sizeof(color_step) / sizeof(hsv);