#include "socketlogger.h"
#include "oled.h"

void setup() {
    socketInit();
    initOled();
    Serial.begin(115200);
}

int cntr = 0;
int onRoom = false;
void loop() {
  
    cntr++;
    if(cntr % 10000 == 0){
      if(onRoom){
      }
      else{
        onRoom = connectRoom();
      }

    } 
    socketLoop();
}


