void config_lcd() {
  
  // initialize the lcd for 20 chars 4 lines, turn on backlight
  lcd.begin(20,4);
  // ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++) {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  Serial.println( "LCD blinked 3 times" );
  // finish with backlight on
  lcd.backlight();   
  //-------- Write characters on the display ------------------
  // NOTE: Cursor Position: (CHAR, LINE) start at 0  
  lcd.clear();
  lcd.setCursor(5,0); //Start at character 8 on line 0
  lcd.print("Smart Grow");
  lcd.setCursor(3,1);
  lcd.print("Class Edition");
  Serial.println("Wrote BioBox header");
  lcd.setCursor(1,3);
  lcd.print("Intializing...");  
  Serial.println("wrote Intializing...");
  lcd.print("LCD");  
  Serial.println( "initializing message on LCD" );
  delay(wait_delay);  
  Serial.println( "Leaving LCD Intialize" );
}

void lcd_display() {
  static   char print_str[20];
  static   unsigned long interval = 10000;
  static   unsigned long previousMillis;        // will store last time LED was updated
  unsigned long currentMillis = millis();
  if ( digitalRead( PROXIMITY_PROBE_PIN ) ) {
    //Serial.println( "someone nearby" );
    // save the last time you saw a person the LED 
    previousMillis = currentMillis;   
    lcd.backlight();
  }
  if (currentMillis - previousMillis >= interval) {
    //Serial.println( "no one nearby" );
    lcd.noBacklight();
  }
 
  DateTime now = RTC.now();
  lcd.setCursor(5,0); //Start at character 8 on line 0
  lcd.print( project_title );
  lcd.setCursor(2, 1);
  //lcd.print("Class Edition");
  lcd.print( "Brightness: " );
  lcd.print( map( analogRead( LIGHT_PROBE_PIN ), 0, 1023, 0, 99) );
  lcd.print( " %");
  lcd.setCursor(0,2);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  lcd.write("In  T=");
  lcd.print( inner_dht.readTemperature(),1 );
  lcd.write("c H=");
  lcd.print( inner_dht.readHumidity(),1 );
  lcd.write("%");
  //sprintf( print_str, "In  T=02%fc H=02%f\%", now.year(), now.month(), now.day(), now.hour(), now.minute() );
  lcd.setCursor(0,3);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  lcd.write("Out T=");
  lcd.print( outer_dht.readTemperature(),1 );
  lcd.write("c H=");
  lcd.print( outer_dht.readHumidity(),1 );
  lcd.write("%");
  //sprintf( time_string, "%04d-%02d-%02d %02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute() );
  //lcd.print( time_string );
  //Serial.println( "LCD - refresh" );
}

