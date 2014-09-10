#ifndef WebSocketRailsEvent_h
#define WebSocketRailsEvent_h

#include <string.h>
#include <stdlib.h>
#include <WString.h>
#include <Arduino.h>
#include <ArduinoJson/JsonParser.h>
#include <HashMap/HashMap.h>
#include "WebSocketRailsTypes.h"
#include "WebSocketRailsEventPayload.h"

using namespace ArduinoJson::Parser;

class WebSocketRailsEvent
{
  public:
	WebSocketRailsEvent();
	WebSocketRailsEvent(WebSocketRailsEventPayload data);
    WebSocketRailsEvent(WebSocketRailsEventPayload data, 
		EventCompletionBlock successCallback, 
		EventCompletionBlock failureCallback);   
    bool isChannel();
    bool isResult();
    bool isPing();
    String serialize();  
    HashMap<String, String, HASH_SIZE> attributes();
    void runCallbacks(bool success, String eventData);    
    String getName();
    int getId();
    String getChannel();
	String getData();
	bool isSuccess();
	bool operator==(WebSocketRailsEvent otherEvent);
    
  private:
	void init(WebSocketRailsEventPayload data, 
		EventCompletionBlock successCallback, 
		EventCompletionBlock failureCallback);   
	EventCompletionBlock successCallback;
	EventCompletionBlock failureCallback;
  	String name;     
  	String attr;
  	int id;
  	String channel;
  	String data;
  	String token;
  	String connectionId;
  	bool success;
  	bool result;  	
};

#endif
