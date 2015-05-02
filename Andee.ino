// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialAndeeData() {  
  
  // Set Project Title
  titleSetting.setId(0);
  titleSetting.setType(KEYBOARD_IN); // Sets object as a text input button
  titleSetting.setLocation(0,0,ONE_QUART);
  titleSetting.setTitle( project_title_default );
  titleSetting.setKeyboardType(ALPHA_NUMERIC); 
  
  // LAMP Setting
  lampBrigthSetting.setId(10);
  lampBrigthSetting.setType(SLIDER_IN);
  lampBrigthSetting.setLocation(1,0,ONE_QUART);
  lampBrigthSetting.setTitle("Lamp Brightness");
  lampBrigthSetting.setSliderMinMax(0, 100, 0); // Display 2 decimal places
  lampBrigthSetting.setSliderInitialValue( lamp_default ); 
  lampBrigthSetting.setSliderNumIntervals(100); // Set to 0 for continuous slider
  lampBrigthSetting.setSliderReportMode(ON_VALUE_CHANGE);

  // LIGHT Settings
  sunnyDaySetting.setId(11);
  sunnyDaySetting.setType(SLIDER_IN);
  sunnyDaySetting.setLocation(1,1,ONE_QUART);
  sunnyDaySetting.setTitle( "Sunny Value" );
  sunnyDaySetting.setSliderMinMax(0, 100, 0); // Display 2 decimal places
  sunnyDaySetting.setSliderInitialValue( sunny_day_default );  // Set slider position to 50
  sunnyDaySetting.setSliderNumIntervals(100); // Set to 0 for continuous slider
  sunnyDaySetting.setSliderReportMode(ON_VALUE_CHANGE);
  
  //Daylight Start
  dayStartSetting.setId(12);
  dayStartSetting.setType(TIME_IN); // Sets object as a time input button
  dayStartSetting.setLocation(1,2,ONE_QUART);
  sprintf(day_start_title, "Day Start: %02d:%02d", day_start_hh_default, day_start_mm_default);
  dayStartSetting.setTitle( day_start_title );
  // Optional Setting. When the user opens up the time picker,
  dayStartSetting.setDefaultTime(day_start_hh_default, day_start_mm_default, ss_default); // Format: hour, minute, second

  //Daylight End
  nightStartSetting.setId(13);
  nightStartSetting.setType(TIME_IN); // Sets object as a time input button
  nightStartSetting.setLocation(1,3,ONE_QUART);
  sprintf( night_start_title, "Night Start: %02d:%02d", night_start_hh_default, night_start_mm_default);
  nightStartSetting.setTitle( night_start_title );
  // Optional Setting. When the user opens up the time picker,
  nightStartSetting.setDefaultTime( night_start_hh_default, night_start_mm_default, ss_default); // Format: hour, minute, second
  
  // AIR CONTROL SETTINGS
  minAirHumiditySetting.setId(20);  
  minAirHumiditySetting.setType(SLIDER_IN); // Set object as a slider
  minAirHumiditySetting.setLocation(2, 0, ONE_QUART); 
  minAirHumiditySetting.setTitle("Min Air Humidity");
  minAirHumiditySetting.setSliderMinMax( 0, 100, 0 );
  minAirHumiditySetting.setSliderInitialValue( min_air_humidity_default );
  minAirHumiditySetting.setSliderNumIntervals(100);
  minAirHumiditySetting.setSliderReportMode(ON_VALUE_CHANGE);

  // Let's draw a continuous slider! ///////////////////////////////////////
  maxAirHumiditySetting.setId(21);
  maxAirHumiditySetting.setType(SLIDER_IN);
  maxAirHumiditySetting.setLocation(2,1,ONE_QUART);
  maxAirHumiditySetting.setTitle("Max Air Humidity");
  maxAirHumiditySetting.setSliderMinMax(0, 100, 0); // Display 2 decimal places
  maxAirHumiditySetting.setSliderInitialValue( max_air_humidity_default );  // Set slider position to 50
  maxAirHumiditySetting.setSliderNumIntervals(100); // Set to 0 for continuous slider
  maxAirHumiditySetting.setSliderReportMode(ON_VALUE_CHANGE);
 
  //Day Air Temp
  dayAirTempSetting.setId(22);
  dayAirTempSetting.setType(SLIDER_IN);
  dayAirTempSetting.setLocation(2,2,ONE_QUART);
  dayAirTempSetting.setTitle("Day Air Temp");
  dayAirTempSetting.setSliderMinMax(-40, 50, 1); // Display 2 decimal places
  dayAirTempSetting.setSliderInitialValue( day_air_temp_default );  // Set slider position to 50
  dayAirTempSetting.setSliderNumIntervals(0); // Set to 0 for continuous slider
  dayAirTempSetting.setSliderReportMode(ON_VALUE_CHANGE);

  //Night Air Temp
  nightAirTempSetting.setId(23);
  nightAirTempSetting.setType(SLIDER_IN);
  nightAirTempSetting.setLocation(2,3,ONE_QUART);
  nightAirTempSetting.setTitle("Night Air Temp");
  nightAirTempSetting.setSliderMinMax(-40, 50, 1); // Display 2 decimal places
  nightAirTempSetting.setSliderInitialValue( night_air_temp_default );  // Set slider position to 50
  nightAirTempSetting.setSliderNumIntervals(0); // Set to 0 for continuous slider
  nightAirTempSetting.setSliderReportMode(ON_VALUE_CHANGE);

  // SOIL SETTINGS
  minSoilMoistureSetting.setId(1);  
  minSoilMoistureSetting.setType(SLIDER_IN); // Set object as a slider
  minSoilMoistureSetting.setLocation(0, 1, ONE_QUART); 
  minSoilMoistureSetting.setTitle("Min Soil Moisture");
  minSoilMoistureSetting.setSliderMinMax( 0, 100, 0 );
  minSoilMoistureSetting.setSliderInitialValue( min_soil_moisture_default );
  minSoilMoistureSetting.setSliderNumIntervals(100);
  minSoilMoistureSetting.setSliderReportMode(ON_VALUE_CHANGE);
  minSoilMoistureSetting.setSliderColor(THEME_GREY_DARK); // Slider bar colour
  minSoilMoistureSetting.setColor(THEME_GREY); // Slider background colour

  // Let's draw a continuous slider! ///////////////////////////////////////
  maxSoilMoistureSetting.setId(2);
  maxSoilMoistureSetting.setType(SLIDER_IN);
  maxSoilMoistureSetting.setLocation(0,2,ONE_QUART);
  maxSoilMoistureSetting.setTitle("Max Soil Moisture");
  maxSoilMoistureSetting.setSliderMinMax(0, 100, 0); // Display 2 decimal places
  maxSoilMoistureSetting.setSliderInitialValue( max_soil_moisture_default );  // Set slider position to 50
  maxSoilMoistureSetting.setSliderNumIntervals(100); // Set to 0 for continuous slider
  maxSoilMoistureSetting.setSliderReportMode(ON_FINGER_UP);
  maxSoilMoistureSetting.setSliderColor(THEME_MIDNIGHT_DARK);
  maxSoilMoistureSetting.setColor(THEME_MIDNIGHT);

  //Day Soil Temp
  SoilTempSetting.setId(3);
  SoilTempSetting.setType(SLIDER_IN);
  SoilTempSetting.setLocation(0,3,ONE_QUART);
  SoilTempSetting.setTitle("Soil Temp");
  SoilTempSetting.setSliderMinMax(-40, 50, 1); // Display 2 decimal places
  SoilTempSetting.setSliderInitialValue( day_soil_temp_default );  // Set slider position to 50
  SoilTempSetting.setSliderNumIntervals(0); // Set to 0 for continuous slider
  SoilTempSetting.setSliderReportMode(ON_VALUE_CHANGE);
  
  //Fan on (min)
  fanRunMinSetting.setId(30);
  fanRunMinSetting.setType(SLIDER_IN);
  fanRunMinSetting.setLocation(3,0,ONE_QUART);
  fanRunMinSetting.setTitle("Fan On (mins)");
  fanRunMinSetting.setSliderMinMax(0, 60, 1); // Display 2 decimal places
  fanRunMinSetting.setSliderInitialValue( fan_run_min_default );  // Set slider position to 50
  fanRunMinSetting.setSliderNumIntervals(0); // Set to 0 for continuous slider
  fanRunMinSetting.setSliderReportMode(ON_VALUE_CHANGE); 

  // Fan off (min)
  fanOffMinSetting.setId(31);
  fanOffMinSetting.setType(SLIDER_IN);
  fanOffMinSetting.setLocation(3,1,ONE_QUART);
  fanOffMinSetting.setTitle("Fan Off (mins)");
  fanOffMinSetting.setSliderMinMax(0, 60, 1); // Display 2 decimal places
  fanOffMinSetting.setSliderInitialValue( fan_off_min_default );  // Set slider position to 50
  fanOffMinSetting.setSliderNumIntervals(0); // Set to 0 for continuous slider
  fanOffMinSetting.setSliderReportMode(ON_VALUE_CHANGE);
 
  // Resovoir Alert Level (%)
  resevoirAlertSetting.setId(32);
  resevoirAlertSetting.setType(SLIDER_IN);
  resevoirAlertSetting.setLocation(3,2,ONE_QUART);
  resevoirAlertSetting.setTitle("Resevoir Alert");
  resevoirAlertSetting.setSliderMinMax(0, 100, 0); // Display 2 decimal places
  resevoirAlertSetting.setSliderInitialValue( resevoir_alert_default );  // Set slider position to 50
  resevoirAlertSetting.setSliderNumIntervals(100); // Set to 0 for continuous slider
  resevoirAlertSetting.setSliderReportMode(ON_VALUE_CHANGE);
  
  // Button to reset slider positions 
  buttonResetPosition.setId(33); // Don't forget to assign a unique ID number
  buttonResetPosition.setType(BUTTON_IN); // Defines object as a button
  buttonResetPosition.setLocation(3,2,ONE_QUART);
  buttonResetPosition.setTitle("Reset 2 Defaults");
  buttonResetPosition.setColor(THEME_RED);
  buttonResetPosition.setTitleColor(THEME_RED_DARK);
  
}    // END of andee setup


void andee_update() {

  if( buttonResetPosition.isPressed() ) {
    buttonResetPosition.ack();
    titleSetting.setTitle( project_title_default );
    sunnyDaySetting.moveSliderToValue(sunny_day_default);
    //dayStartSetting.moveSliderToValue( day_start_default );
    sprintf( day_start_title, "Day Start: %02d:%02d", day_start_hh_default, day_start_mm_default);
    dayStartSetting.setTitle( day_start_title );
    dayStartSetting.setDefaultTime(day_start_hh_default, day_start_mm_default, ss_default); // Format: hour, minute, secon
    //nightStartSetting.moveSliderToValue( night_start_default );
    sprintf( night_start_title, "Night Start: %02d:%02d", night_start_hh_default, night_start_mm_default);
    dayStartSetting.setTitle( day_start_title );
    dayStartSetting.setDefaultTime(night_start_hh_default, night_start_mm_default, ss_default); // Format: hour, minute, secon
    //
    lampBrigthSetting.moveSliderToValue( lamp_default );
    minAirHumiditySetting.moveSliderToValue( min_air_humidity_default );
    maxAirHumiditySetting.moveSliderToValue( max_air_humidity_default );
    dayAirTempSetting.moveSliderToValue( day_air_temp_default );
    nightAirTempSetting.moveSliderToValue( night_air_temp_default );
    minSoilMoistureSetting.moveSliderToValue( min_soil_moisture_default );
    maxSoilMoistureSetting.moveSliderToValue( max_soil_moisture_default );
    SoilTempSetting.moveSliderToValue( day_soil_temp_default );
    nightSoilTempSetting.moveSliderToValue( night_soil_temp_default );
    fanRunMinSetting.moveSliderToValue( fan_run_min_default );
    fanOffMinSetting.moveSliderToValue( fan_off_min_default );
    resevoirAlertSetting.moveSliderToValue( resevoir_alert_default );
  } 
  
  if ( titleSetting.isPressed() ) {
    memset( user_title_set, 0x00, 32 ); // Empty the contents of the string before receiving user input
    titleSetting.ack(); // Acknowledge button press or else phone will be left waiting
    titleSetting.getKeyboardMessage( user_title_set ); // Display keyboard and store input into userInput
    sprintf( project_title, "%s", user_title_set );
    titleSetting.setTitle( project_title );   
    sprintf(commandString, "SET BT NAME %s", user_title_set );
    Andee.sendCommand( commandString, cmdReply );
  }
  titleSetting.update();
  
  if( dayStartSetting.isPressed() ) { 
    dayStartSetting.ack();
    // Display time picker and store it in the three variables - hh, mm, and ss
    dayStartSetting.getTimeInput(&day_start_hh_set, &day_start_mm_set, &ss_set); 
    // String the three variables into a single time string
    sprintf(day_start_title, "Day Start: %02d:%02d", day_start_hh_set, day_start_mm_set);
    dayStartSetting.setTitle( day_start_title );
    // Optional Setting. When the user opens up the time picker,
    dayStartSetting.setDefaultTime(day_start_hh_set, day_start_mm_set, ss_default); // Format: hour, minute, second
  }
  dayStartSetting.update();
  
  if( nightStartSetting.isPressed() ) { 
    nightStartSetting.ack();
    // Display time picker and store it in the three variables - hh, mm, and ss
    nightStartSetting.getTimeInput(&night_start_hh_set, &night_start_mm_set, &ss_set); 
    // String the three variables into a single time string
    sprintf( night_start_title, "Night Start: %02d:%02d", night_start_hh_set, night_start_mm_set);
    nightStartSetting.setTitle( night_start_title );
    // Optional Setting. When the user opens up the time picker,
    nightStartSetting.setDefaultTime(night_start_hh_set, night_start_mm_set, ss_default); // Format: hour, minute, second
  }
  nightStartSetting.update();
  
  lamp_bright_set        = lampBrigthSetting.getSliderValue( INT );
  sunny_day_set          = sunnyDaySetting.getSliderValue( INT );
  day_start_set          = dayStartSetting.getSliderValue( FLOAT );
  night_start_set        = nightStartSetting.getSliderValue( FLOAT );
  min_air_humidity_set   = minAirHumiditySetting.getSliderValue( INT ); // Retrieve integer value
  max_air_humidity_set   = maxAirHumiditySetting.getSliderValue( INT ); // Retrieve float value
  day_air_temp_set       = dayAirTempSetting.getSliderValue( FLOAT );
  night_air_temp_set     = nightAirTempSetting.getSliderValue( FLOAT );
  min_soil_moisture_set  = minSoilMoistureSetting.getSliderValue( INT ); // Retrieve integer value
  max_soil_moisture_set  = maxSoilMoistureSetting.getSliderValue( INT ); // Retrieve float value
  soil_temp_set          = SoilTempSetting.getSliderValue( FLOAT );
  night_soil_temp_set    = nightSoilTempSetting.getSliderValue( FLOAT );
  fan_run_min_set        = fanRunMinSetting.getSliderValue( FLOAT );
  fan_off_min_set        = fanOffMinSetting.getSliderValue( FLOAT );
  resevoir_alert_set     = resevoirAlertSetting.getSliderValue( INT );
  
  lampBrigthSetting.update();
  sunnyDaySetting.update();
  dayStartSetting.update();
  nightStartSetting.update();
  minAirHumiditySetting.update();
  maxAirHumiditySetting.update();
  dayAirTempSetting.update();
  nightAirTempSetting.update();
  minSoilMoistureSetting.update();
  maxSoilMoistureSetting.update();
  SoilTempSetting.update();
  nightSoilTempSetting.update();
  fanRunMinSetting.update();
  fanOffMinSetting.update();
  resevoirAlertSetting.update();
  buttonResetPosition.update();

  /*
  if ( (!time_synced) ) {
    Serial.println( "first iOS Connection" );
   // Retrieve date and store in variables: day, month, and year
    Andee.getDeviceDate(&day, &month, &year);
    // Retrieve time and store in variables: hour, minute, second
    Andee.getDeviceTime(&hour, &minute, &second);
    sprintf(time_string, "%d-%d-%d, %02d:%02d:%02d", year, month, day, hour, minute, second);
    DateTime ios_time ( year, month, day, hour, minute, second );
    // set clock time (first time)?
    //RTC.adjust(DateTime(__DATE__, __TIME__));
    Serial.println( "RTC Time updated" );
    //RTC.adjust( DateTime( year, month, day, hour, minute, second ) );
    RTC.adjust( DateTime( ios_year, ios_month, ios_day, ios_hour, ios_minute, ios_second ) );

  }
  */
}     // END of ANDEE UPDATE

