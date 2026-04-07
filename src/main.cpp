#include "Arduino.h"
#include "HX711.h"
#include "ArduinoJson.h"
#include "led"
#include "loadcell"


#define scale1_dout 1
#define scale1_sck 1

#define scale2_dout 1
#define scale2_sck 1

#define scale3_dout 1
#define scale3_sck 1

#define scale4_dout 1
#define scale4_sck 1

#define scale5_dout 1
#define scale5_sck 1

#define scale6_dout 1
#define scale6_sck 1

#define scale7_dout 1
#define scale7_sck 1

#define scale8_dout 1
#define scale8_sck 1

#define scale9_dout 1
#define scale9_sck 1

#define scale10_dout 1
#define scale10_sck 1

#define scale11_dout 1
#define scale11_sck 1

#define scale12_dout 1
#define scale12_sck 1

#define LED_1_R 1
#define LED_1_G 1
#define LED_1_B 1

#define LED_2_R 1
#define LED_2_G 1
#define LED_2_B 1

#define LED_3_R 1
#define LED_3_G 1
#define LED_3_B 1

#define LED_4_R 1
#define LED_4_G 1
#define LED_4_B 1

#define LED_5_R 1
#define LED_5_G 1
#define LED_5_B 1

#define LED_6_R 1
#define LED_6_G 1
#define LED_6_B 1

#define LED_7_R 1
#define LED_7_G 1
#define LED_7_B 1

#define LED_8_R 1
#define LED_8_G 1
#define LED_8_B 1

#define LED_9_R 1
#define LED_9_G 1
#define LED_9_B 1

#define LED_10_R 1
#define LED_10_G 1
#define LED_10_B 1

#define LED_11_R 1
#define LED_11_G 1
#define LED_11_B 1

#define LED_12_R 1
#define LED_12_G 1
#define LED_12_B 1


#define calibration_factor_test -7050


JsonDocument doc;


HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;
HX711 scale5;
HX711 scale6;
HX711 scale7;
HX711 scale8;
HX711 scale9;
HX711 scale10;
HX711 scale11;
HX711 scale12;

HX711 sclaeTest;

typedef struct
{
  HX711 scale;
  float calibration_factor;
  unsigned int dout;
  unsigned int sck;
} Scale;

Scale scale[12];

typedef struct 
{
  short int r;
  short int g;
  short int b;
} Led;

Led led[12];



// 0점 셋팅
void setScaleZero(HX711 scale){
  scale.tare(10);  
}

// set calibration_factor
void setCalibrationFactor(HX711 scale, float value){
  scale.set_scale(value);
}

// set DOUT,SCK
void setDout(HX711 scale, int dout, int sck){
  scale.begin(dout,sck);
}


void activateLedRed(Led led){
  digitalWrite(led.r,HIGH);
  digitalWrite(led.g,LOW);
  digitalWrite(led.b,LOW);
}

void activateLedGreen(Led led){
  digitalWrite(led.r,LOW);
  digitalWrite(led.g,HIGH);
  digitalWrite(led.b,LOW);
}

void activateLedBlue(Led led){
  digitalWrite(led.r,LOW);
  digitalWrite(led.g,LOW);
  digitalWrite(led.b,HIGH);
}

void deactivateLed(Led led){
  digitalWrite(led.r,LOW);
  digitalWrite(led.g,LOW);
  digitalWrite(led.b,LOW);
}

void activateAllLedRed(Led led[]){
  for(int i =0 ; i<12 ;i++){
    activateLedRed(led[i]);
  }
}

void activateAllLedGreen(Led led[]){
  for(int i =0 ; i<12 ;i++){
    activateLedGreen(led[i]);
  }
}

void activateAllLedBlue(Led led[]){
  for(int i =0 ; i<12 ;i++){
    activateLedBlue(led[i]);
  }
}

void deactivateAllLed(Led led[]){
  for(int i= 0; i<12;i++){
    deactivateLed(led[i]);
  }
}

void makeJsonForScale(JsonDocument doc, int scaleNumber,int weight){
  
  doc["scale"]=scaleNumber;
  doc["weight"]=weight;

}





int beforeWeight[12] = {0};

float calitest = -700.7;

int temp = 0;




void setup() {
  
  Serial.begin(9600);

  // 변수 초기화
  for(int i=0;i<12;i++){
    beforeWeight[i]=0;
  }


  sclaeTest.begin(25,24);
  
  sclaeTest.set_scale(calitest);

  sclaeTest.tare(5);






  // scale1.set_scale(calibration_factor);

  scale1.tare(10);
  scale2.tare(10);
  scale3.tare(10);
  scale4.tare(10);
  scale5.tare(10);
  scale6.tare(10);
  scale7.tare(10);
  scale8.tare(10);
  scale9.tare(10);
  scale10.tare(10);
  scale11.tare(10);
  scale12.tare(10);




  


}



void loop() {
  // put your main code here, to run repeatedly:
  

  // Serial 데이터 수신
  if(Serial.available()>0){
    String str = "";
    str = Serial.readStringUntil('\n');




    
  }

  




  // Serial.println(sclaeTest.read());
  Serial.print(sclaeTest.get_units(5),2);
  Serial.println("g");


Serial.print("-----"); 
Serial.print(temp);   
Serial.println("----"); 

temp++;
delay(1000); 

// scale 데이터 송신

for(int i = 0 ;i<12 ; i++){
  int afterWeight = 0;

   afterWeight = scale[i].scale.get_units(5);
  if(beforeWeight[i] - afterWeight > 1 || afterWeight==0 ){

    String str="";
    JsonDocument doc;

    makeJsonForScale(doc,i,afterWeight);
    
    str=serializeJson(doc,str);

    Serial.write(str.c_str());
    
    Serial.print("ScaleJson : ");
    Serial.println(str);
    
    
    
  }
}




  // // 이전과 차이가 1g 이상 나면 송신
  // Serial.write(scale1.get_units(5));
  // Serial.write(scale2.get_units(5));
  // Serial.write(scale3.get_units(5));
  // Serial.write(scale4.get_units(5));
  // Serial.write(scale5.get_units(5));
  // Serial.write(scale6.get_units(5));
  // Serial.write(scale7.get_units(5));
  // Serial.write(scale8.get_units(5));
  // Serial.write(scale9.get_units(5));
  // Serial.write(scale10.get_units(5));
  // Serial.write(scale11.get_units(5));
  // Serial.write(scale12.get_units(5));

  

}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}