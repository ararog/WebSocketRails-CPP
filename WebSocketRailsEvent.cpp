#include "WebSocketRailsEvent.h"

WebSocketRailsEvent::WebSocketRailsEvent() {

}

WebSocketRailsEvent::WebSocketRailsEvent(WebSocketRailsEventPayload payload, 
	EventCompletionBlock success, EventCompletionBlock failure) {

	init(payload, success, failure);
}

WebSocketRailsEvent::WebSocketRailsEvent(WebSocketRailsEventPayload payload) {

	init(payload, NULL, NULL);
}
    
void WebSocketRailsEvent::init(WebSocketRailsEventPayload payload, 
	EventCompletionBlock successCallback, EventCompletionBlock failureCallback) {

 	name = payload.getEventName();
	connectionId = payload.getConnectionId();

 	data = payload.getData();
 	if (data != NULL)
 	{
		JsonParser<16> parser;

		char buffer[data.length() + 1];
		data.toCharArray(buffer, data.length() + 1);

		JsonObject attr = parser.parse(buffer);

 		if (attr["id"].success())
 			id = attr["id"];
 		else
 			id = rand();
 		
		channel = attr["channel"];
 		
		data = attr["data"];
 		
		token = attr["token"];
 		
 		if (attr["success"].success()) {
 			result = true;
 			success = attr["success"];
 		}
 	}
 	
 	this->successCallback = successCallback;
 	this->failureCallback = failureCallback;
}

bool WebSocketRailsEvent::isChannel() {
	
}

bool WebSocketRailsEvent::isResult() {
	
	return result;
}

bool WebSocketRailsEvent::isPing() {
	
	return name.equals("websocket_rails.ping");	
}

String WebSocketRailsEvent::serialize() {
	
}

HashMap<String, String, HASH_SIZE> WebSocketRailsEvent::attributes() {
	
}

void WebSocketRailsEvent::runCallbacks(bool success, String eventData) {

	if (success && successCallback)
		successCallback(eventData);
	else {
		if (failureCallback)
			failureCallback(eventData);
	}	
}

bool WebSocketRailsEvent::isSuccess() {

	return success;
}

bool WebSocketRailsEvent::operator==(WebSocketRailsEvent otherEvent) {

	return this->getId() == otherEvent.getId();
}
