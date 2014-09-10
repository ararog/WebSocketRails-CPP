#ifndef WebSocketRailsEventPayload_h
#define WebSocketRailsEventPayload_h

#include <string.h>
#include <stdlib.h>
#include <WString.h>
#include <Arduino.h>
#include <HashMap/HashMap.h>

class WebSocketRailsEventPayload
{
  public:
    WebSocketRailsEventPayload();
	String getEventName();
	void setEventName(String name);
	String getData();
	void setData(String data);
	String getConnectionId();
	void setConnectionId(String connectionId);
  private:
  	String eventName;
  	String data;
  	String connectionId;
};

#endif
