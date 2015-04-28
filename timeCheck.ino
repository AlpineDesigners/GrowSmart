void check_time() {
  // set clock time when first connected -- if arduino time is off? 
  DateTime   now = RTC.now();
  Serial.println( "Checking time" );
  
  if ( fix_time() ) {
    Serial.println( "Fixing time" );
    Andee.getDeviceDate(&ios_day, &ios_month, &ios_year);
    Andee.getDeviceTime(&ios_hour, &ios_minute, &ios_second);
    sprintf( time_string, "iOS:     %d-%02d-%02d, %02d:%02d:%02d", ios_year, ios_month, ios_day, ios_hour, ios_minute, ios_second);
    Serial.println( time_string );
    sprintf( time_string, "arduino: %d-%02d-%02d, %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second() );
    Serial.println( time_string );
    RTC.adjust( DateTime( ios_year, ios_month, ios_day, ios_hour, ios_minute, ios_second ) );
    Serial.println( "Time updated" );
  }
  //time_synced = true;
}

boolean fix_time() {
  
  DateTime   now = RTC.now();
  
  Andee.getDeviceDate(&ios_day, &ios_month, &ios_year);
  Andee.getDeviceTime(&ios_hour, &ios_minute, &ios_second);
  sprintf( time_string, "iOS:     %d-%d-%d, %02d:%02d:%02d", ios_year, ios_month, ios_day, ios_hour, ios_minute, ios_second);
  Serial.println( time_string );
  sprintf( time_string, "arduino: %d-%d-%d, %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second() );
  Serial.println( time_string );

  // if arduino time are not equal to ios time and ios times are not 0 
  //    then update the arudio's time

  if ( ios_year   != now.year()   && ios_year   != 0 ) return true;
  if ( ios_month  != now.month()  && ios_month  != 0 ) return true;
  if ( ios_day    != now.day()    && ios_day    != 0 ) return true;
  if ( ios_hour   != now.hour()   && ios_hour   != 0 ) return true;
  if ( ios_minute != now.minute() && ios_minute != 0 ) return true;
  
  Serial.println( "time ok - no update needed" );
  // no need to update the arduino's time if all time tests pass
  return false;
  
}
