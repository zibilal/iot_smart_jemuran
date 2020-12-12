#ifndef MY_LIB_H
#define MY_LIB_H

#include <NTPClient.h>
#include <TimeLib.h>

String getId(NTPClient timeClient);
String getCurrentDateTime(NTPClient timeClient);

#endif
