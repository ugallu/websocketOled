#include "socketlogger.h"
#include "oled.h"

void onEvent(char* payload){
  int x = strcmp(payload, "42[\"push\"]");
  if(x==0){
    drawText("New Push!");
  }
  
}
	
	void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    

    switch(type) {
        case WStype_DISCONNECTED:
            Serial.println("Event: disconnect");
            socketIsConnected = false;
            break;
        case WStype_CONNECTED:
            {
                Serial.println("Event: connected");
                socketIsConnected = true;
  
          // send message to server when Connected
                // socket.io upgrade confirmation message (required)
        webSocket.sendTXT("5");
            }
            break;
        case WStype_TEXT:
            
            Serial.println((char*)payload);
            onEvent((char*)payload);
            
      // send message to server
      // webSocket.sendTXT("message here");
            break;
        case WStype_BIN:
            Serial.println("Event:bin");
            hexdump(payload, length);

            // send data to server
            // webSocket.sendBIN(payload, length);
            break;
    }

}

	void socketInit() {
	    WiFiMulti.addAP(SSID, PASS);

	    while(WiFiMulti.run() != WL_CONNECTED) {
		delay(100);
	    }

	    webSocket.beginSocketIO(SERVERIP, SERVERPORT);
	    //webSocket.setAuthorization("user", "Password"); // HTTP Basic Authorization
	    webSocket.onEvent(webSocketEvent);

	}

  
  bool connectRoom(){
    if(socketIsConnected) {
      webSocket.sendTXT("42[\"event\",\"" + CONSOLEID + "\"]");
    }
    return socketIsConnected;
  }
	
	void socketSend(String message){
	
		if(socketIsConnected) {
			webSocket.sendTXT("42[\"log\",\"" + message + "\",\"" + CONSOLEID + "\"]");
		}
	}

  bool hasRoom = false;



	void socketLoop() {
	    webSocket.loop();

	    if(socketIsConnected) {

		uint64_t now = millis();

		if((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
		    heartbeatTimestamp = now;
		    // socket.io heartbeat message
		    if(started){
		      webSocket.sendTXT("2probe");
		      started = 0;
		    }
		    else webSocket.sendTXT("2");
		}
	    }
	}
