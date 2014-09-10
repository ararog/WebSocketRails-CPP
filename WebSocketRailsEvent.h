#ifndef WebSocketRailsEvent_h
#define WebSocketRailsEvent_h

#include <string.h>
#include <stdlib.h>
#include <WString.h>
#include <ArduinoJson/JsonParser.h>
#include <HashMap/HashMap.h>
#include "Arduino.h"
#include "WebSocketRailsTypes.h"
#include "WebSocketRailsEventPayload.h"

using namespace ArduinoJson::Parser;

class WebSocketRailsEvent
{
  public:
    WebSocketRailsEvent(WebSocketRailsEventPayload data, EventCompletionBlock success, EventCompletionBlock failure);   
	WebSocketRailsEvent(WebSocketRailsEventPayload data);
    bool isChannel();
    bool isResult();
    bool isPing();
    String serialize();  
    HashMap<String, String, HASH_SIZE> attributes();
    void runCallbacks(bool success, JsonObject eventData);    
    String getName();
    int getId();
    String getChannel();
	JsonObject getData();
	bool isSuccess();
    
  private:
	void init(WebSocketRailsEventPayload data, EventCompletionBlock success, EventCompletionBlock failure);   
  	String name;     
  	String attr;
  	int id;
  	String channel;
  	JsonObject data;
  	String token;
  	String connectionId;
  	bool success;
  	bool result;  	  
};

#endif
