/*
 * JsonUtil.c
 *
 * Abstracts the lower layers of jansson.
 *
 */

#include "JsonHandler.h"

json_t
JsonUtil_loadJSON(const char* text)
{
    /*
     * Load the JSON file and pass it to a JSON object.
     */

    json_t *root;
    json_error_t error;

    root = json_loads(text, 0, &error);
    if (root) {
        return root;
    } else {
        fprintf(stderr, "JSON error on line %d: %s\n", error.line, error.text);
        return (json_t *) 0;
    }
}
