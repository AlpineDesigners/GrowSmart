void lamp_control() {
  int light_reading; 
  // now.hour();
  // now.minute();
  light_reading = map( analogRead( LIGHT_PROBE_PIN ), 0, 1023, 0, 100); 
  // if ( daytime ) {
    if ( light_reading < low_light_in ) {
      //turn on light
      digitalWrite( LAMP_CTRL_PIN, HIGH );
    } else if (light_reading > low_light_in + 5) {
      // turn off light -- LAMP_CTRL_PIN
      digitalWrite( LAMP_CTRL_PIN, LOW );
    }
  // } else {
  //   // turb off light
  // }
}

