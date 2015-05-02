
boolean is_daytime() {
  /*
  int   day_start_hh_set;
  int   day_start_mm_set;
  int   night_start_hh_set;
  int   night_start_mm_set;
  */  
  DateTime   now = RTC.now();
  if ( day_start_hh_set > now.hour() ) return false;
  if ( night_start_hh_set < now.hour() ) return false;
  if ( ( day_start_hh_set == now.hour() ) && ( day_start_mm_set > now.minute() ) ) return false;
  if ( ( night_start_hh_set == now.hour() ) && ( day_start_mm_set < now.minute() ) ) return false;
  return true;
}

void lamp_control() {
  int light_reading; 
  light_reading = map( analogRead( LIGHT_PROBE_PIN ), 0, 1023, 0, 100); 

  if ( is_daytime() ) {
    Serial.println( "Daylight Hours" );
    // turn on lamp 5% early (to avoid a flicker at tranisition times)
    if ( light_reading < sunny_day_set - 5 ) {
      Serial.println( "Dim ambient light - turn on LAMP" );
      digitalWrite( LAMP_CTRL_PIN, RELAY_ON );
      //analogWrite( LAMP_CTRL_PIN, lamp_gright_set );
    // if it brighter than the low light condition -- turn OFF the lamp
    } else if ( light_reading > sunny_day_set ) {
      Serial.println( "Bright sunny day - disable grow LAMP" );
      digitalWrite( LAMP_CTRL_PIN, RELAY_OFF );
    }
  } else {
    Serial.println( "Its night -- turn off Grow Lamp" );
    digitalWrite( LAMP_CTRL_PIN, RELAY_OFF );
  }
}
