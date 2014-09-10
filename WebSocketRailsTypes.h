#ifndef WebSocketRailsTypes_h
#define WebSocketRailsTypes_h

#include <ArduinoJson/JsonParser.h>

using namespace ArduinoJson::Parser;

const byte HASH_SIZE = 10;

typedef void (*EventCompletionBlock)(JsonObject data);

#endif
