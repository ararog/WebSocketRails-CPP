#include "WebSocketRailsChannel.h"
#include "WebSocketRailsDispatcher.h"
#include "WebSocketRailsEventPayload.h"

WebSocketRailsChannel::WebSocketRailsChannel() {

}

WebSocketRailsChannel::WebSocketRailsChannel(String channelName, 
	WebSocketRailsDispatcher* dispatcher, bool isPrivate) {

	String eventName = "";
	if (isPrivate)
		eventName = "websocket_rails.subscribe_private";
	else
		eventName = "websocket_rails.subscribe";
	
	this->_private = isPrivate;
	this->channelName = channelName;
	this->dispatcher = dispatcher;

	Generator::JsonObject<1> frame;
	frame["channel"] = channelName;

	char buffer[256];
	frame.printTo(buffer, sizeof(buffer));

	WebSocketRailsEventPayload payload;
	payload.setEventName(eventName);
	payload.setData(buffer);
	payload.setConnectionId(dispatcher->getConnectionId());
	
	WebSocketRailsEvent event(payload, NULL, NULL);

	this->callbacks = HashMap<String, LinkedList<EventCompletionBlock>, HASH_SIZE>();
	dispatcher->triggerEvent(event);	
}

void WebSocketRailsChannel::bind(String eventName, EventCompletionBlock callback) {
	
	if (! callbacks.contains(eventName))
		callbacks[eventName] = LinkedList<EventCompletionBlock>();
	
	LinkedList<EventCompletionBlock> eventCallbacks = callbacks[eventName];
	eventCallbacks.add(callback);	
}

void WebSocketRailsChannel::trigger(String eventName, String data) {

	Generator::JsonObject<3> frame;
	frame["channel"] = channelName;	
	frame["data"] = data;	
	frame["token"] = token;	

	char buffer[256];
	frame.printTo(buffer, sizeof(buffer));

	WebSocketRailsEventPayload payload;
	payload.setEventName(eventName);
	payload.setData(buffer);
	payload.setConnectionId(dispatcher->getConnectionId());

	WebSocketRailsEvent event(payload, NULL, NULL);
 	
 	dispatcher->triggerEvent(event);	
}

void WebSocketRailsChannel::dispatch(String eventName, 
	String data) {
	
	if(eventName.equals("websocket_rails.channel_token")) {
		JsonParser<16> parser;	

		char buffer[data.length() + 1];
		data.toCharArray(buffer, data.length() + 1);

		Parser::JsonObject frame = parser.parse(buffer);
		this->token = frame["token"];
	}
	else {
		if (! callbacks.contains(eventName))
			return;
		
		LinkedList<EventCompletionBlock> eventCallbacks = callbacks[eventName];
		for(int i = 0; i < eventCallbacks.size(); i++){
			EventCompletionBlock callback = eventCallbacks.get(i);
			callback(data);
		}
	}	
}

void WebSocketRailsChannel::destroy() {
	
	String eventName = "websocket_rails.unsubscribe";

	Generator::JsonObject<1> frame;
	frame["channel"] = channelName;

	char buffer[256];
	frame.printTo(buffer, sizeof(buffer));

	WebSocketRailsEventPayload payload;
	payload.setEventName(eventName);
	payload.setData(buffer);
	payload.setConnectionId(dispatcher->getConnectionId());

	WebSocketRailsEvent event(payload);
		
	dispatcher->triggerEvent(event);
}

bool WebSocketRailsChannel::isPrivate() {
	
	return _private;
}
