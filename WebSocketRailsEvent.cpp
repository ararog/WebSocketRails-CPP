#include "WebSocketRailsEvent.h"

WebSocketRailsEvent::WebSocketRailsEvent(WebSocketRailsEventPayload data, 
	EventCompletionBlock success, EventCompletionBlock failure) {

	init(data, success, failure);
}

WebSocketRailsEvent::WebSocketRailsEvent(WebSocketRailsEventPayload data) {

	init(data, NULL, NULL);
}
    
void WebSocketRailsEvent::init() {

 	name = data[0];
 	attr = data[1];
 	if (attr)
 	{
 		if (attr.contains("id") && attr["id"] != NULL)
 			id = attr["id"];
 		else
 			id = rand();
 		
 		if (attr.contains("channel") && attr["channel"] != NULL)
 			channel = attr["channel"];
 		
 		if (attr.contains("data") && attr["data"] != NULL)
 			data = attr["data"];
 		
 		if (attr.contains("token") && attr[@"token"] != NULL)
 			token = attr["token"];
 		
 		if (data[2] != NULL)
 			connectionId = data[2];
 		else
 			connectionId = 0;
 		
 		if (attr.contains("success") && attr["success"] != NULL) {
 			result = true;
 			success = (bool) attr["success"];
 		}
 	}
 	
 	this.successCallback = success;
 	this.failureCallback = failure;
}

bool WebSocketRailsEvent::isChannel() {
	
}

bool WebSocketRailsEvent::isResult() {
	
	return result;
}

bool WebSocketRailsEvent::isPing() {
	
	return "websocket_rails.ping".equals(name);	
}

String WebSocketRailsEvent::serialize() {
	
}

HashMap<String, String> WebSocketRailsEvent::attributes() {
	
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
