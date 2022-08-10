#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 9

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(21, 7, PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);


const uint16_t red = matrix.Color(255,0,0);
const uint16_t green = matrix.Color(0,255,0);

boolean start = true;

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(true);
  matrix.setBrightness(40);
  pinMode(13,OUTPUT);
  Serial.write("0");
  Serial.flush();
}

int x = matrix.width();
int pass = 0;
String info = "0";
String stock_name = "None";

void loop() {

  if (start == true){ 
    float price = 0;
    float change = 0;

    while(Serial.available()==0){
      
    }

    if (Serial.available()!=0){
      stock_name = Serial.readString();
    }
    
    while(Serial.available()==0){ 
    }
    
    if (Serial.available()!=0){
      price = Serial.parseFloat();

    }
  
    while(Serial.available()==0){ 
    
    }
    
    if (Serial.available()!=0){
      change = Serial.parseFloat();
    }
  
    String percent = "% "; 
    String dollar = "$";
    String space = " ";

    info = stock_name + space + dollar + price + space + change + percent;
    start = false;    
    matrix.setTextColor(red);

    if (change >= 0){
      
      matrix.setTextColor(green);
    } 
    
  }
  
  
  matrix.fillScreen(0);    //Turn off all the LEDs
  matrix.setCursor(x, 0);
  matrix.print(info);

  
  if( --x < -120 ) {
    x = matrix.width();
    Serial.write("0");

    if(++pass >= 7) pass = 0;

  }
  matrix.show();
  delay(100);

  if (Serial.available() != 0){
    start = true;
  }
  
}
