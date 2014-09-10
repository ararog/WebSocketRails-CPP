#ifndef WebSocketRailsDispatcher_h
#define WebSocketRailsDispatcher_h

#include <string.h>
#include <stdlib.h>
#include <WString.h>
#include <Arduino.h>
#include <HashMap/HashMap.h>  
#include <LinkedList/LinkedList.h>
#include "WebSocketRailsTypes.h"
#include "WebSocketRailsConnection.h"
#include "WebSocketRailsChannel.h"
#include "WebSocketRailsEvent.h"
#include "WebSocketRailsEventPayload.h"
#include "Client.h"

using namespace ArduinoJson;

class WebSocketRailsDispatcher
{
  public:
    WebSocketRailsDispatcher(String url);
    void dispatch(WebSocketRailsEvent event);
    void newMessage(LinkedList<WebSocketRailsEventPayload> data);
    void bind(String eventName, EventCompletionBlock callback);
    void trigger(String eventName, String data, EventCompletionBlock success, EventCompletionBlock failure);
    void triggerEvent(WebSocketRailsEvent event);                                
    WebSocketRailsChannel subscribe(String channelName);
    void unsubscribe(String channelName);
    void connect(Client &client);                 
    void disconnect();       
	String getState();
	String getUrl();
	HashMap<String, WebSocketRailsChannel, HASH_SIZE> getChannels();
	String getConnectionId();    
  private:
  	void connectionEstablished(String data);
  	void dispatchChannel(WebSocketRailsEvent event);
  	void pong();
  	HashMap<int, WebSocketRailsEvent, HASH_SIZE> queue;
  	HashMap<String, LinkedList<EventCompletionBlock>, HASH_SIZE> callbacks;
	HashMap<String, WebSocketRailsChannel, HASH_SIZE> channels;
  	WebSocketRailsConnection connection;
	String url;
	String state;
	String connectionId;
};

#endif                             
