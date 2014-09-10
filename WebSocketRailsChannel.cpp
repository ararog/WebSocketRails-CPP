#include "WebSocketRailsChannel.h"
#include "WebSocketRailsEventPayload.h"

WebSocketRailsChannel::WebSocketRailsChannel(String channelName, 
	WebSocketRailsDispatcher dispatcher, bool isPrivate) {

	String eventName = NULL;
	if (isPrivate)
		eventName = "websocket_rails.subscribe_private";
	else
		eventName = "websocket_rails.subscribe";
	
	this.isPrivate = isPrivate;
	this.channelName = channelName;
	this.dispatcher = dispatcher;

	WebSocketRailsEventPayload payload = WebSocketRailsEventPayload();
	payload.setEventName(eventName);
	payload.setData({"channel" : channelName});
	payload.setConnectionId(dispatcher.getConnectionId());
	
	WebSocketRailsEvent event = WebSocketRailsEvent(payload, NULL, NULL);

	this.callbacks = HashMap<String, String, HASH_SIZE>();
	dispatcher.triggerEvent(event);	
}

void WebSocketRailsChannel::bind(String eventName, EventCompletionBlock callback) {
	
	if (! callbacks.contains(eventName))
		callbacks[eventName] = LinkedList<EventCompletionBlock>();
	
	LinkedList<EventCompletionBlock> eventCallbacks = callbacks[eventName];
	eventCallbacks.add(callback);	
}

void WebSocketRailsChannel::trigger(String eventName, String message) {

	HashMap<String, String, HASH_SIZE> data = HashMap<String, String, HASH_SIZE>();
	data["channel"] = channelName;	
	data["data"] = message;	
	data["token"] = token;	

	WebSocketRailsEventPayload payload = WebSocketRailsEventPayload();
	payload.setEventName(eventName);
	payload.setData(data);
	payload.setConnectionId(dispatcher.getConnectionId());

	WebSocketRailsEvent event = WebSocketRailsEvent(payload, NULL, NULL);
 	
 	dispatcher.triggerEvent(event);	
}

void WebSocketRailsChannel::dispatch(String eventName, 
	HashMap<String, String, HASH_SIZE> message) {
	
	if(eventName.equals("websocket_rails.channel_token")) {
		HashMap<String, String, HASH_SIZE> info = (HashMap<String, String, HASH_SIZE>) message;
		this.token = info["token"];
	}
	else {
		if (! callbacks.contains(eventName))
			return;
		
		LinkedList<EventCompletionBlock> eventCallbacks = callbacks[eventName];
		for(int i = 0; i < eventCallbacks.size(); i++){
			EventCompletionBlock callback = eventCallbacks.get(i);
			callback(message);
		}
	}	
}

void WebSocketRailsChannel::destroy() {
	
	String eventName = "websocket_rails.unsubscribe";

	WebSocketRailsEventPayload payload = WebSocketRailsEventPayload();
	payload.setEventName(eventName);
	payload.setData({"channel" : channelName});
	payload.setConnectionId(dispatcher.getConnectionId());

	WebSocketRailsEvent event = WebSocketRailsEvent(payload);
		
	dispatcher.triggerEvent(event);
	callbacks.clear();	
}

bool WebSocketRailsChannel::isPrivate() {
	
	return private;
}
