/**
 * Demonstracao de fita LED
 */
#include <FastLED.h>

#define LED_PINO    8
#define LED_TOTAL   144
#define LED_TIPO    WS2812B   // WS2812 ou WS2812B
#define LED_ORDEM   GRB
#define DELAY       10

CRGB          leds[LED_TOTAL];
CRGBPalette16 paleta;
int           brilho;

void setup() {
  // preDefinicoes: RainbowColors_p, OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p and PartyColors_p
  paleta = RainbowColors_p;
  brilho = 0;
  
  FastLED.addLeds<LED_TIPO, LED_PINO, LED_ORDEM>( leds, LED_TOTAL ).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( 100 );
}

void loop() {
  static uint8_t ledInicial = 0;
  
  setaLeds( ledInicial );
  conferePaletaEBrilho();
  
  // rotacao
  ledInicial += 3;
  
  FastLED.show();
  FastLED.delay(DELAY); // velocidade
}

void setaLeds(uint8_t ledInicial) {
  // Setar os LEDs conforme paleta, brilho e rotacao
  for(int i = 0; i < LED_TOTAL; i++) {
    leds[i] = ColorFromPalette( paleta, ledInicial, brilho, LINEARBLEND );
    ledInicial += 3;
  }
}

void conferePaletaEBrilho() {
  // FadeIn e FadeOut do brilho
  uint8_t bs = ((millis() / 100) % 100); // 0..99
  if(bs > 49) bs = 100 - bs; // 0..50..0
  brilho = bs;  // Max brilho = 99


  // Testar todas as 6 paletas
  uint8_t dec = (((millis() / 1000) % 60) / 10) + 1; // 1..6
  static uint8_t decAnterior = 99;
  
  if(dec != decAnterior) {
    decAnterior = dec;
    
    if(     dec == 1) paleta = RainbowColors_p;
    else if(dec == 2) paleta = OceanColors_p;
    else if(dec == 3) paleta = LavaColors_p;
    else if(dec == 4) paleta = ForestColors_p;
    else if(dec == 5) paleta = PartyColors_p;
    else if(dec == 6) paleta = CloudColors_p;
  }
}
