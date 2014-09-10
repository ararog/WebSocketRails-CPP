#ifndef WebSocketRailsChannel_h
#define WebSocketRailsChannel_h

#include <string.h>
#include <stdlib.h>
#include <WString.h>
#include <HashMap/HashMap.h>
#include "Arduino.h"
#include "WebSocketRailsTypes.h"

class WebSocketRailsDispatcher;

class WebSocketRailsChannel
{
  public:
    WebSocketRailsChannel(String name, WebSocketRailsDispatcher dispatcher, bool isPrivate);
	void bind(String eventName, EventCompletionBlock callback);
	void dispatch(String eventName, String message);
	void destroy();
	void trigger(String eventName, String message);
	bool isPrivate();
  private:
  	String eventName;
  	HashMap<String, EventCompletionBlock, HASH_SIZE> callbacks;
  	String channelName;
  	String token;
  	WebSocketRailsDispatcher* dispatcher;
};

#endif
