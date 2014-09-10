#include "WebSocketRailsConnection.h"
#include "WebSocketRailsDispatcher.h"

WebSocketRailsConnection::WebSocketRailsConnection(String url, 
	WebSocketRailsDispatcher* dispatcher) {
	
 	this->url = url;
 	this->dispatcher = dispatcher;
	message_queue = LinkedList<WebSocketRailsEvent>();
}

void WebSocketRailsConnection::trigger(WebSocketRailsEvent event) {

	if (! dispatcher->getState().equals("connected"))
		message_queue.add(event);
	else
		webSocket.sendData(event.serialize());	
}

void WebSocketRailsConnection::flushQueue() {
	
	WebSocketRailsEvent event;
	for(int i = 0; i < message_queue.size(); i++){
		event = message_queue.get(i);
		String serializedEvent = event.serialize();
		webSocket.sendData(serializedEvent);	
	}	
}

void WebSocketRailsConnection::connect(Client &client) {

    webSocket.handshake(client);
}

void WebSocketRailsConnection::disconnect() {
	
    webSocket.disconnect();
}


