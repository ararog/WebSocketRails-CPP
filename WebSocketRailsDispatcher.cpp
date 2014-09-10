#include "WebSocketRailsDispatcher.h"

WebSocketRailsDispatcher::WebSocketRailsDispatcher(String url) : connection(url, this) {
	
	url = url;
	state = "connecting";
	connectionId = "";	
}

void WebSocketRailsDispatcher::dispatch(WebSocketRailsEvent event) {
	
	if (! callbacks.contains(event.getName()))
		return;

	LinkedList<EventCompletionBlock> eventCallbacks = callbacks[event.getName()];
	for(int i = 0; i < eventCallbacks.size(); i++){
		EventCompletionBlock callback = eventCallbacks.get(i);
		callback(event.getData());
	}	
}

void WebSocketRailsDispatcher::newMessage(LinkedList<WebSocketRailsEventPayload> data) {

	for(int i = 0; i < data.size(); i++){
		WebSocketRailsEventPayload socket_message = data.get(i);
		WebSocketRailsEvent event(socket_message);
		if (event.isResult()) {
			if (queue.contains(event.getId())) {
				WebSocketRailsEvent boundEvent = queue[event.getId()];
				boundEvent.runCallbacks(event.isSuccess(), event.getData());
				queue.remove(event.getId());
			}
		} else if (event.isChannel()) {
			this->dispatchChannel(event);
		} else if (event.isPing()) {
			this->pong();
		} else {
			this->dispatch(event);
		}
		
		if (state.equals("connecting") && String("client_connected").equals(event.getName()))
			this->connectionEstablished(event.getData());
	}	
}

void WebSocketRailsDispatcher::connectionEstablished(JsonObject data) {
	
	state = "connected";
	connectionId = data["connection_id"];
	connection.flushQueue();

	WebSocketRailsEventPayload payload;
	payload.setEventName("connection_opened");
	payload.setData(NULL);
	payload.setConnectionId(connectionId);

	WebSocketRailsEvent connectionEstablishedEvent(payload);
	this->dispatch(connectionEstablishedEvent);
}

void WebSocketRailsDispatcher::bind(String eventName, EventCompletionBlock callback) {

	if (! callbacks.contains(eventName))
		callbacks[eventName] = LinkedList<EventCompletionBlock>();
	
	LinkedList<EventCompletionBlock> eventCallbacks = callbacks[eventName];
	eventCallbacks.add(callback);	
}

void WebSocketRailsDispatcher::trigger(String eventName, JsonObject data, EventCompletionBlock success, EventCompletionBlock failure) {
	
	WebSocketRailsEventPayload payload;
	payload.setEventName(eventName);
	payload.setData(data);
	payload.setConnectionId(connectionId);

	WebSocketRailsEvent event(payload, success, failure);
	queue[event.getId()] = event;
	connection.trigger(event);	
}

void WebSocketRailsDispatcher::triggerEvent(WebSocketRailsEvent event) {

	if (queue.contains(event.getId()) && queue[event.getId()] == event)
		return;
	
	queue[event.getId()] = event;
	connection.trigger(event);	
}

WebSocketRailsChannel WebSocketRailsDispatcher::subscribe(String channelName) {

	if (channels.contains(channelName))
		return channels[channelName];
	
	WebSocketRailsChannel channel(channelName, this, false);
	channels[channelName] = channel;
	
	return channel;	
}

void WebSocketRailsDispatcher::unsubscribe(String channelName) {
	
	if (! channels.contains(channelName))
		return;
	
	WebSocketRailsChannel channel = channels[channelName];
	channel.destroy();
	channels.remove(channelName);	
}

void WebSocketRailsDispatcher::dispatchChannel(WebSocketRailsEvent event) {
	
	if (! channels.contains(event.getChannel()))
		return;
	
	WebSocketRailsChannel channel = channels[event.getChannel()];
	channel.dispatch(event.getName(), event.getData());	
}

void WebSocketRailsDispatcher::pong() {

	WebSocketRailsEventPayload payload;
	payload.setEventName("websocket_rails.pong");
	payload.setData(NULL);
	payload.setConnectionId(connectionId);

	WebSocketRailsEvent pong(payload);
	connection.trigger(pong);	
}
  	
void WebSocketRailsDispatcher::connect() {
	connection.connect();
}

void WebSocketRailsDispatcher::disconnect() {
	connection.disconnect();
}

String WebSocketRailsDispatcher::getState() {
	
	return state;
}

String WebSocketRailsDispatcher::getUrl() {
	
	return url;
}

HashMap<String, WebSocketRailsChannel, HASH_SIZE> WebSocketRailsDispatcher::getChannels() {
	
	return channels;
}

String WebSocketRailsDispatcher::getConnectionId() {
	
	return connectionId;
}
