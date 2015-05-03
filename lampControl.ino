
boolean is_daytime() {
  /*
  int   day_start_set;
  int   night_start_set;
  */  
  Serial.print( "Day Start Set: " );
  Serial.println( day_start_set );
  Serial.print( "Day Start Calc: " );
  day_start_hh_set = day_start_set / 10000;
  Serial.print( day_start_hh_set );
  Serial.print( ":" );
  day_start_mm_set = ( day_start_set % 10000 ) / 100;
  Serial.println( day_start_mm_set );
  Serial.print( "Night Start: " );
  Serial.println( night_start_set );
  Serial.print( "Night Start Calc: " );
  night_start_hh_set = night_start_set / 10000;  
  Serial.print( night_start_hh_set );
  Serial.print( ":" );
  night_start_mm_set = ( night_start_set % 10000 ) / 100;
  Serial.println( night_start_mm_set );
  Serial.println();
  DateTime   now = RTC.now();
  Serial.print( "Current Time: " );
  Serial.print( now.hour() );
  Serial.print( ":" );
  Serial.print( now.minute() );
  Serial.println();

  // it is night if now it is before (less than) day start
  if ( now.hour() < day_start_hh_set ) return false;
  Serial.println( "Now is not before day break" );
  // it is night if now is after (greater than) night start
  if ( now.hour() > night_start_hh_set ) return false; 
  Serial.println( "Now is not after night start" ); 
  /*
  if ( ( day_start_hh_set == now.hour() ) && ( day_start_mm_set > now.minute() ) ) return false;
  Serial.println( "Now is equal to Day Start Hour & GREATER than minutes" );
  if ( day_start_hh_set > now.hour() ) return false;
  Serial.println( "Now is greater than Day Start Hour" );
  if ( night_start_hh_set < now.hour() ) return false;
  Serial.println( "Now is less than night Start Hour & GREATER than Day start Hour" );
  if ( ( night_start_hh_set == now.hour() ) && ( day_start_mm_set < now.minute() ) ) return false;
  */
  Serial.println( "It must be daytime hours" );
  return true;
}

void lamp_control() {
  int light_reading; 
  light_reading = map( analogRead( LIGHT_PROBE_PIN ), 0, 1023, 0, 100); 

  if ( is_daytime() ) {
    Serial.println( "Daylight Hours" );
    // turn on lamp 5% early (to avoid a flicker at tranisition times)
    if ( light_reading < sunny_day_set - 5 ) {
      Serial.println( "Dim ambient light - turn lamp *ON*" );
      digitalWrite( LAMP_CTRL_PIN, RELAY_ON );
      //analogWrite( LAMP_CTRL_PIN, lamp_gright_set );
    // if it brighter than the low light condition -- turn OFF the lamp
    } else if ( light_reading > sunny_day_set ) {
      Serial.println( "Bright sunny day - turn lamp *OFF*" );
      digitalWrite( LAMP_CTRL_PIN, RELAY_OFF );
    }
  } else {
    Serial.println( "Its night -- turn lamp *OFF*" );
    digitalWrite( LAMP_CTRL_PIN, RELAY_OFF );
  }
  Serial.println();
}
