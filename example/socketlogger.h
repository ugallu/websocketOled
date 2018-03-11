#ifndef SOCKETLOGGER_H
#define SOCKETLOGGER_H	



#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WebSocketsClient.h>

#include <Hash.h>

static const char SSID[] = "capybara";
static const char PASS[] = "K6D6R_bdpst_7465";

static const char SERVERIP[] = "webhook2websocket.herokuapp.com";
#define SERVERPORT 80

static ESP8266WiFiMulti WiFiMulti;
static WebSocketsClient webSocket;

#define HEARTBEAT_INTERVAL 25000
static String CONSOLEID = "SOMETHING";

static uint64_t messageTimestamp = 0;
static uint64_t heartbeatTimestamp = 0;
static bool socketIsConnected = false;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);

void socketInit();
bool connectRoom();

static int started = 1;

void socketSend(String message);

void socketLoop();

#endif
