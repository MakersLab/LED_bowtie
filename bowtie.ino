
#include <Adafruit_NeoPixel.h>

// SETUP YOUR OUTPUT PIN AND NUMBER OF PIXELS
#define PIN 2
#define NUM_PIXELS  14

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
int pins[]={0,1,2,3,4,5,6,13,12,11,10,9,8,7};
int mode = 1;
int r = 84;
int g = 155;
int b = 3;
void setup() {
  strip.begin();
  clearStrip(); // Initialize all pixels to 'off'
  //delay(1000);
}

void loop() {
  	knightRider(80, 5, r, g, b); // Cycles, Speed, Width, RGB Color
    repro(160, r, g, b); // Speed, RGB
}

void repro(int speed, int red, int green, int blue ){
  int pixels[4][2] = {{0,6},{1,5},{2,4},{3,3}};
  int pix[4][2] ={{13,7},{12,8},{11,9},{10,10}};
  for(int i = 0; i < 4; i ++){
      strip.setPixelColor(pixels[i][0], red,green,blue);
      strip.setPixelColor(pix[i][0], red,green,blue);
      strip.setPixelColor(pixels[i][1], red,green,blue);
      strip.setPixelColor(pix[i][1], red,green,blue);
      int x=i-1;
      if(x < 0){
        x = 3;
      }
      strip.setPixelColor(pixels[x][1], red/4,green/4,blue/4);
      strip.setPixelColor(pix[x][1], red/4,green/4,blue/4);
      strip.setPixelColor(pixels[x][0], red/4,green/4,blue/4);
      strip.setPixelColor(pix[x][0], red/4,green/4,blue/4);
  
  x=x-1;
      if(x < 0){
        x +=4;
      }
      strip.setPixelColor(pixels[x][0], 0, 0, 0);
      strip.setPixelColor(pix[x][0], 0, 0, 0);
      strip.setPixelColor(pixels[x][1], 0, 0, 0);
      strip.setPixelColor(pix[x][1], 0, 0, 0);
      strip.show();
      delay(speed);
  }
  
  }

// Cycles - one cycle is scanning through all pixels left then right (or right then left)
// Speed - how fast one cycle is (32 with 16 pixels is default KnightRider speed)
// Width - how wide the trail effect is on the fading out LEDs.  The original display used
//         light bulbs, so they have a persistance when turning off.  This creates a trail.
//         Effective range is 2 - 8, 4 is default for 16 pixels.  Play with this.
// Color - 32-bit packed RGB color value.  All pixels will be this color.
// knightRider(cycles, speed, width, color);
void knightRider( uint16_t speed, uint8_t width, uint16_t r, uint16_t g, uint16_t b) {
  
  uint32_t old_val[NUM_PIXELS]; // up to 256 lights!
  // Larson time baby!
      int count = 0;
    while(count != 14){
      strip.setPixelColor(pins[count], r,g,b);
      for(int i = 1; i < NUM_PIXELS ; i ++){
          int pixel = count - i;
          if(pixel < 0){
            pixel = 14+pixel; 
          }
          if(i < width){
          strip.setPixelColor(pins[pixel],r/((width)*i), g/((width)*i), b/((width)*i));
          }
          else{
            strip.setPixelColor(pins[pixel], 0);
          }
      }
      count+=1;
      strip.show();
      delay(speed);
      
    }
}

void clearStrip() {
  for( int i = 0; i<NUM_PIXELS; i++){
    strip.setPixelColor(i, 0x000000); strip.show();
  }
}

uint32_t dimColor(uint32_t color, uint8_t width) {
   return (((color&0xFF0000)/width)&0xFF0000) + (((color&0x00FF00)/width)&0x00FF00) + (((color&0x0000FF)/width)&0x0000FF);
}

// Using a counter and for() loop, input a value 0 to 251 to get a color value.
// The colors transition like: red - org - ylw - grn - cyn - blue - vio - mag - back to red.
// Entering 255 will give you white, if you need it.
uint32_t colorWheel(byte WheelPos) {
  byte state = WheelPos / 21;
  switch(state) {
    case 0: return strip.Color(255, 0, 255 - ((((WheelPos % 21) + 1) * 6) + 127)); break;
    case 1: return strip.Color(255, ((WheelPos % 21) + 1) * 6, 0); break;
    case 2: return strip.Color(255, (((WheelPos % 21) + 1) * 6) + 127, 0); break;
    case 3: return strip.Color(255 - (((WheelPos % 21) + 1) * 6), 255, 0); break;
    case 4: return strip.Color(255 - (((WheelPos % 21) + 1) * 6) + 127, 255, 0); break;
    case 5: return strip.Color(0, 255, ((WheelPos % 21) + 1) * 6); break;
    case 6: return strip.Color(0, 255, (((WheelPos % 21) + 1) * 6) + 127); break;
    case 7: return strip.Color(0, 255 - (((WheelPos % 21) + 1) * 6), 255); break;
    case 8: return strip.Color(0, 255 - ((((WheelPos % 21) + 1) * 6) + 127), 255); break;
    case 9: return strip.Color(((WheelPos % 21) + 1) * 6, 0, 255); break;
    case 10: return strip.Color((((WheelPos % 21) + 1) * 6) + 127, 0, 255); break;
    case 11: return strip.Color(255, 0, 255 - (((WheelPos % 21) + 1) * 6)); break;
    default: return strip.Color(0, 0, 0); break;
  }
}

