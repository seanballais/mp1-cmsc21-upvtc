/*
 * JsonUtil.h
 *
 * Abstracts the lower layers of jansson.
 *
 */

#ifndef JSONUTIL_H
#define JSONUTIL_H

    #include <stdio.h>

    // Included libraries
    #include "../../include/jansson.h"

    json_t JsonUtil_loadJSON(const char* text);

#endif
