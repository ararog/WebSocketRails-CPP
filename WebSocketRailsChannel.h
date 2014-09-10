#ifndef WebSocketRailsChannel_h
#define WebSocketRailsChannel_h

#include <string.h>
#include <stdlib.h>
#include <WString.h>
#include <Arduino.h>
#include <ArduinoJson/JsonGenerator.h>
#include <HashMap/HashMap.h>
#include <LinkedList/LinkedList.h>
#include "WebSocketRailsTypes.h"

using namespace ArduinoJson;

class WebSocketRailsDispatcher;

class WebSocketRailsChannel
{
  public:
	WebSocketRailsChannel();
    WebSocketRailsChannel(String name, WebSocketRailsDispatcher* dispatcher, bool isPrivate);
	void bind(String eventName, EventCompletionBlock callback);
	void dispatch(String eventName, String data);
	void destroy();
	void trigger(String eventName, String data);
	bool isPrivate();
  private:
  	String eventName;
  	HashMap<String, LinkedList<EventCompletionBlock>, HASH_SIZE> callbacks;
  	String channelName;
  	String token;
  	WebSocketRailsDispatcher* dispatcher;
	bool _private;
};

#endif
