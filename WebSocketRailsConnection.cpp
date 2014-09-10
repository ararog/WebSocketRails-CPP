#include "WebSocketRailsConnection.h"

WebSocketRailsConnection::WebSocketRailsConnection(String url, 
	WebSocketRailsDispatcher dispatcher) {
	
 	this.url = url;
 	this.dispatcher = dispatcher;
	message_queue = LinkedList<WebSocketRailsEvent *>();
}

void WebSocketRailsConnection::trigger(WebSocketRailsEvent event) {

	if (! "connected".equals(dispatcher.getState()))
		message_queue.add(event);
	else
		webSocket.send(event.serialize());	
}

void WebSocketRailsConnection::flushQueue() {
	
	WebSocketRailsEvent *event;
	for(int i = 0; i < message_queue.size(); i++){
		event = message_queue.get(i);
		String serializedEvent = event.serialize();
		webSocket.send(serializedEvent);	
	}	
}

void WebSocketRailsConnection::connect() {

	
}

void WebSocketRailsConnection::disconnect() {
	
	
	
}
