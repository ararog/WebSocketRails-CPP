#ifndef WebSocketRailsEventPayload_h
#define WebSocketRailsEventPayload_h

#include <string.h>
#include <stdlib.h>
#include <WString.h>
#include <HashMap/HashMap.h>
#include "Arduino.h"

class WebSocketRailsEventPayload
{
  public:
    WebSocketRailsEventPayload();
	String getEventName();
	void setEventName(String name);
	JsonObject getData();
	void setData(JsonObject data);
	String getConnectionId();
	void setConnectionId(String connectionId);
  private:
  	String eventName;
  	JsonObject data;
  	String connectionId;
};

#endif
