/*
* Arduino JSON library
* Benoit Blanchon 2014 - MIT License
*/

#include <string.h> // for strcmp()
#include "JsonArray.h"
#include "JsonObject.h"
#include "JsonValue.h"

using namespace ArduinoJson::Parser;
using namespace ArduinoJson::Internal;

DEPRECATED JsonArray JsonObject::getArray(const char* key)
{
    return (*this)[key];
}

/*
* Returns the token for the value associated with the specified key
*/
JsonValue JsonObject::getValue(const char* desiredKey)
{
    // sanity check
    if (desiredKey == 0 || !token.isObject())
        return JsonValue::null();

    // skip first token, it's the whole object
    JsonToken runningToken = token.firstChild();

    // scan each keys
    for (int i = 0; i < token.size() / 2; i++)
    {
        // get 'key' token string
        char* key = runningToken.getText(json);

        // move to the 'value' token
        runningToken = runningToken.nextSibling();

        // compare with desired name
        if (strcmp(desiredKey, key) == 0)
        {
            // return the value token that follows the key token
            return JsonValue(json, runningToken);
        }

        // skip nested tokens
        runningToken = runningToken.nextSibling();
    }

    // nothing found, return NULL
    return JsonValue::null();
}