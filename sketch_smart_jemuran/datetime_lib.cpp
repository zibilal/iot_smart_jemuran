
#include "datetime_lib.h"

String getCurrentDateTime(NTPClient timeClient) {

  unsigned long epochTime = timeClient.getEpochTime();
  time_t atime = (time_t)epochTime;

  char hour_txt[25];
  char minute_txt[25];
  char second_txt[25];
  sprintf(hour_txt, "%d", hour(atime));
  sprintf(minute_txt, "%d", minute(atime));
  sprintf(second_txt, "%d", second(atime));

  char day_txt[25];
  char month_txt[25];
  char year_txt[25];
  sprintf(day_txt, "%d", day(atime));
  sprintf(month_txt, "%d", month(atime));
  sprintf(year_txt, "%d", year(atime));

  String adate = String(year_txt) + String(month_txt) + String(day_txt) + String(hour_txt) + String(minute_txt) + String(second_txt);

  return adate;
}

String getId(NTPClient timeClient) {

  unsigned long epochTime = timeClient.getEpochTime();
  time_t atime = (time_t)epochTime;

  char hour_txt[25];
  char minute_txt[25];
  char second_txt[25];
  sprintf(hour_txt, "%d", hour(atime));
  sprintf(minute_txt, "%d", minute(atime));
  sprintf(second_txt, "%d", second(atime));

  char day_txt[25];
  char month_txt[25];
  char year_txt[25];
  sprintf(day_txt, "%d", day(atime));
  sprintf(month_txt, "%d", month(atime));
  sprintf(year_txt, "%d", year(atime));

  String separator1 = "/";
  String separator2 = ":";
  String separator3 = "/";

  String adate = String(year_txt) + separator1 + String(month_txt) + separator1 + String(day_txt) + separator3 + String(hour_txt) + separator2 + String(minute_txt) + separator2 + String(second_txt);
  return adate;
}
