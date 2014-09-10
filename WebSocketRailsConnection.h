#ifndef WebSocketRailsConnection_h
#define WebSocketRailsConnection_h

#include <string.h>
#include <stdlib.h>
#include <WString.h>
#include <Arduino.h>
#include <LinkedList/LinkedList.h>
#include <Arduino-Websocket/WebSocketClient.h>
#include "WebSocketRailsEvent.h"
#include "Client.h"

class WebSocketRailsDispatcher;

class WebSocketRailsConnection
{
  public:
    WebSocketRailsConnection(String url, WebSocketRailsDispatcher* dispatcher);
    void trigger(WebSocketRailsEvent event);
    void flushQueue();
    void connect(Client &client);
    void disconnect();
  private:
  	String url;
  	WebSocketRailsDispatcher* dispatcher;
  	LinkedList<WebSocketRailsEvent> message_queue;
	WebSocketClient webSocket;
};

#endif
