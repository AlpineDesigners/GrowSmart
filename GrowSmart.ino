// the classroom (less-precise) edition of controlled greenhouse
// THIS CODE / PROJECT is planned for a Arduino MEGA 
// (ANDEEs SPI on an Uno would also use pins 10-13)

// LIBRRIES
#include <SPI.h>
#include "DHT.h"
#include <math.h>
#include <Wire.h>
#include <Servo.h>
#include <Andee.h>
// RTC Library with our clocks
// https://github.com/mizraith/RTClib/tree/master/examples
#include <RTClib.h>
#include <RTC_DS1307.h>
// LCD I2C Backpack Interface
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
#include <LiquidCrystal_I2C.h>

// PIN USAGE
#define LIGHT_PROBE_PIN       A0
#define INNER_AIR_PROBE_PIN   A1  // lab temp and humidity probe pin
//#define SOIL_MOIST_PROBE_PIN  A2  // humidity or (temp and humidity with DHT22 probe)
//#define SOIL_PROBE_PIN        A3  // humidity & temp with ??? probe)
//#define SOIL_TEMP_PROBE_PIN   A3  // temp soil probe with 10K thermistor
#define OUTER_AIR_PROBE_PIN   A4  // outside temp (and humidity with DHT22 probe )
#define PROXIMITY_PROBE_PIN   A5  // know when to make displays visible when a person is nearby
#define AQUA_STOP_PROBE_PIN   A6
//#define AQUA_STOP_PROBE_0_PIN A6
//#define AQUA_STOP_PROBE_1_PIN A7
#define PIN_A8                A8
#define PIN_A9                A9
#define PIN_A10               A10
#define PIN_A11               A11
#define PIN_A12               A12
#define PIN_A13               A13
#define PIN_A14               A14
#define AMPERAGE_PROBE_PIN    A15  // current usage probe

// shield reserved pins -- DO NOT CHANGE USAGE
#define SERIAL_RX_PIN         0  // reserved by Serial
#define SERIAL_TX_PIN         1  // reserved by Serial
//#define INTERRUPT_0           2  // PWM & Interrupt 0
//#define INTERRUPT_1           3  // PWM & Interrupt 1
#define FAN_DIRECTION_PIN     4  // PWM  - reserved by MOTOR shield & romeo
#define FAN_SPEED_PIN         5  // PWM - reserved by MOTOR shield & romeo
#define PUMP_SPEED_PIN        6  // PWM - reserved by MOTOR shield & romeo
#define PUMP_DIRECTION_PIN    7  // PWM - reserved by MOTOR shield & romeo
#define ANDEE_SHIELD_PIN      8  // PWM  - reserved by ANDEE shield
// ClimeCase output pins
#define AIR_TEMP_CTRL_PIN     9  // PWM - for air heating intensity control
#define SOIL_TEMP_CTRL_PIN   10  // PWM - for soil heating intensity control
#define LAMP_CTRL_PIN        11  // PWM - for lamp brigthness control
#define HUMIDIFIER_CTRL_PIN  12  // PWM - humidifier on/off control pin
#define WINDOW_CTRL_PIN      13  // PWM - for winow servo control
// reserved usage pins
#define PIN_14               14  // TX
#define PIN_15               15  // RX
#define PIN_16               16  // TX
#define PIN_17               17  // RX
#define PIN_18               18  // TX  & interrupt 5
#define PIN_19               19  // RX  & interrupt 4

#define I2C_TWI_SDA_PIN      20  // SDA & interrupt 3
#define I2C_TWI_SCL_PIN      21  // SCL & interrupt 2
#define AQUA_PUMP_CTRL_PIN   22  
#define PIN_23               23  
#define PIN_24               24  
#define PIN_25               25
#define PIN_26               26
#define PIN_27               27
#define PIN_28               28
#define PIN_29               29

#define PIN_30               30
#define PIN_31               31
#define PIN_32               32  
#define PIN_33               33  
#define PIN_34               34  
#define PIN_35               35
#define PIN_36               36
#define PIN_37               37
#define PIN_38               38
#define PIN_39               39

#define PIN_40               40
#define PIN_41               41  // PWM
#define PIN_42               42  // PWM
#define PIN_43               43  // PWM
#define PIN_44               44  // PWM
#define PIN_45               45
#define PIN_46               46
#define PIN_47               47
#define PIN_48               48
#define PIN_49               49
#define SPI_MISO_50          50  // SPI: 50 (MISO), 51 (MOSI), 52 (SCK), 53 (SS)
#define SPI_MOSI_51          51  // SPI: 50 (MISO), 51 (MOSI), 52 (SCK), 53 (SS)
#define SPI_SCK_52           52  // SPI: 50 (MISO), 51 (MOSI), 52 (SCK), 53 (SS)
#define SPI_SS_53            53  // SPI: 50 (MISO), 51 (MOSI), 52 (SCK), 53 (SS)

// define the rtc (real-time-clock)
#define RTC_ADDRESS          0x32

#define DHTTYPE              DHT22   // DHT 22  (AM2302)
//#define DHTTYPE              DHT21   // DHT 21 (AM2301)
//#define DHTTYPE              DHT11   // DHT 11 
DHT inner_dht(INNER_AIR_PROBE_PIN, DHTTYPE);
DHT outer_dht(OUTER_AIR_PROBE_PIN, DHTTYPE);

// state which clock we are using
RTC_DS1307 RTC;      // inexpensive indoor clock

// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd( 0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE );  // Set the LCD I2C address
//LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

// servo settings
Servo window;

// define inputs for sliders
AndeeHelper titleSetting;
AndeeHelper lampSetting;
AndeeHelper lowLightSetting;
AndeeHelper dayStartSetting;
AndeeHelper nightStartSetting;
AndeeHelper minAirHumiditySetting;
AndeeHelper maxAirHumiditySetting;
AndeeHelper dayAirTempSetting;
AndeeHelper nightAirTempSetting;
AndeeHelper minSoilMoistureSetting; // Discrete input slider
AndeeHelper maxSoilMoistureSetting; // Discrete input slider
AndeeHelper SoilTempSetting;
AndeeHelper nightSoilTempSetting;
AndeeHelper fanRunMinSetting;
AndeeHelper fanOffMinSetting;
AndeeHelper resevoirAlertSetting;
AndeeHelper buttonResetPosition;

// This is where you change your device name:
char newBluetoothName[] = "GrowSmart"; // New device name
char cmdReply[64]; // String buffer
char commandString[100]; // String to store the new device name and device command into one
char user_title_in[32];
char project_title[40] = "GrowSmart";
char project_title_default[40] = "GrowSmart";
char day_start_title[20];
char night_start_title[20];
char time_string[20];
char air_string[20];

int day;
int month;
int year;
int hour; 
int minute;
int second;

int   ss_in                     = 0;
int   ss_default                = 0;
int   lamp_in                   = 100;
int   lamp_default              = 100;
int   low_light_default         = 75;
float day_start_default         = 6.5;
int   day_start_hh_default      = 06;
int   day_start_mm_default      = 30;
float night_start_default       = 19.0;
int   night_start_hh_default    = 19;
int   night_start_mm_default    = 30;

int   min_air_humidity_default  = 50;
int   max_air_humidity_default  = 75;
float day_air_temp_default      = 22.0;
float night_air_temp_default    = 14.0;

int   min_soil_moisture_default = 25;
int   max_soil_moisture_default = 75;
float day_soil_temp_default     = 25.0;
float night_soil_temp_default   = 18.0;

float fan_run_min_default       = 5.0;
float fan_off_min_default       = 10.0;
int   resevoir_alert_default    = 20;

int   low_light_in;
float day_start_in;
int   day_start_hh_in;
int   day_start_mm_in;
int   day_start_ss_in;
float night_start_in;
int   night_start_hh_in;
int   night_start_mm_in;
int   night_start_ss_in;
int   min_air_humidity_in;
int   max_air_humidity_in;
float day_air_temp_in;
float night_air_temp_in;
int   min_soil_moisture_in;
int   max_soil_moisture_in;
float soil_temp_in;
float night_soil_temp_in;
float fan_run_min_in;
float fan_off_min_in;
int   resevoir_alert_in;

int wait_delay = 4000;

boolean time_synced = false;


// define sensing values
float
box_temp,
box_humidity,
room_temp,
room_humidity,
soil_temp,
soil_humidity;

void setup() {
  
  // setup serial debugging
  Serial.begin( 96000 );
  Serial.println("BioBox Serial Defined:\n");

  // PIN USAGE
  // INPUT Probe Pins
  pinMode( A0 , INPUT );    // A0
  pinMode( A1 , INPUT );    // A1
  pinMode( A2 , INPUT );    // A2
  pinMode( A3 , INPUT_PULLUP );    // A3
  pinMode( A4 , INPUT_PULLUP );    // A4
  pinMode( A5 , INPUT_PULLUP );    // A5
  /*  RESERVED PINS for other uses
  pinMode(  0 , ????? );    //  0  --  RX
  pinMode(  1 , ????? );    //  1  --  TX
  pinMode(  2 , ????? );    //  2  --  TWI/I2C -- Data
  pinMode(  3 , ????? );    //  3  --  TWI/I2C -- Clock
  */
  // DFRobot Motor Shield & ROMEO board
  pinMode(  4 , OUTPUT );   //  4  -- FAN  -- Motor 1 Direction
  pinMode(  5 , OUTPUT );   //  5  -- FAN  -- Motor 1 Speed
  pinMode(  6 , OUTPUT );   //  6  -- PUMP -- Motor 2 Speed
  pinMode(  7 , OUTPUT );   //  7  -- PUMP -- Motor 2 Direction
  // ANDEE SHIELD
  //pinMode(  8 , ?????? ); // ANDEE SHIELD
  pinMode(  9 , OUTPUT );   // 
  pinMode( 10 , OUTPUT );
  pinMode( 11 , OUTPUT );
  pinMode( 12 , OUTPUT );
  pinMode( 13 , OUTPUT );
  
  Andee.begin();
  Andee.clear();
  // We need to combine the new device name with the device command
  sprintf(commandString, "SET BT NAME %s", newBluetoothName);
  // Send command to change device name
  Andee.sendCommand(commandString, cmdReply);
  setInitialAndeeData(); // Define ANDEE object types and their appearance
  
  // setup the software communication real-time clock
  Wire.begin();   //write to the real-time clock
  
  // setup clock
  RTC.begin();
  if (! RTC.isrunning() ) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  delay(wait_delay);  
  
  // setup the lcd pannel
  config_lcd();  
  lcd.clear();
}

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
  static   print_str[20];
  static   unsigned long interval = 10000;
  static   unsigned long previousMillis;        // will store last time LED was updated
  unsigned long currentMillis = millis();
  if ( digitalRead( PROXIMITY_PROBE_PIN ) ) {
    Serial.println( "someone nearby" );
   // save the last time you saw a person the LED 
    previousMillis = currentMillis;   
    lcd.backlight();
  }
  if (currentMillis - previousMillis >= interval) {
    Serial.println( "no one nearby" );
    lcd.noBacklight();
  }
  //lcd.backlight();
  //lcd.clear();
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
  Serial.println( "LCD - refresh" );
}

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
  lampSetting.setId(10);
  lampSetting.setType(SLIDER_IN);
  lampSetting.setLocation(1,0,ONE_QUART);
  lampSetting.setTitle("Lamp Brightness");
  lampSetting.setSliderMinMax(0, 100, 0); // Display 2 decimal places
  lampSetting.setSliderInitialValue( lamp_default );  // Set slider position to 50
  lampSetting.setSliderNumIntervals(100); // Set to 0 for continuous slider
  lampSetting.setSliderReportMode(ON_VALUE_CHANGE);

  // LIGHT Settings
  lowLightSetting.setId(11);
  lowLightSetting.setType(SLIDER_IN);
  lowLightSetting.setLocation(1,1,ONE_QUART);
  lowLightSetting.setTitle("Lamp Trigger");
  lowLightSetting.setSliderMinMax(0, 100, 0); // Display 2 decimal places
  lowLightSetting.setSliderInitialValue( low_light_default );  // Set slider position to 50
  lowLightSetting.setSliderNumIntervals(100); // Set to 0 for continuous slider
  lowLightSetting.setSliderReportMode(ON_VALUE_CHANGE);
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
    lowLightSetting.moveSliderToValue(low_light_default);
    //dayStartSetting.moveSliderToValue( day_start_default );
    sprintf( day_start_title, "Day Start: %02d:%02d", day_start_hh_default, day_start_mm_default);
    dayStartSetting.setTitle( day_start_title );
    dayStartSetting.setDefaultTime(day_start_hh_default, day_start_mm_default, ss_default); // Format: hour, minute, secon
    //nightStartSetting.moveSliderToValue( night_start_default );
    sprintf( night_start_title, "Night Start: %02d:%02d", night_start_hh_default, night_start_mm_default);
    dayStartSetting.setTitle( day_start_title );
    dayStartSetting.setDefaultTime(night_start_hh_default, night_start_mm_default, ss_default); // Format: hour, minute, secon
    //
    lampSetting.moveSliderToValue( lamp_default );
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
    memset( user_title_in, 0x00, 32 ); // Empty the contents of the string before receiving user input
    titleSetting.ack(); // Acknowledge button press or else phone will be left waiting
    titleSetting.getKeyboardMessage( user_title_in ); // Display keyboard and store input into userInput
    sprintf( project_title, "%s", user_title_in );
    titleSetting.setTitle( project_title );   
    sprintf(commandString, "SET BT NAME %s", user_title_in );
    Andee.sendCommand( commandString, cmdReply );
  }
  titleSetting.update();
  
  if( dayStartSetting.isPressed() ) { 
    dayStartSetting.ack();
    // Display time picker and store it in the three variables - hh, mm, and ss
    dayStartSetting.getTimeInput(&day_start_hh_in, &day_start_mm_in, &ss_in); 
    // String the three variables into a single time string
    sprintf(day_start_title, "Day Start: %02d:%02d", day_start_hh_in, day_start_mm_in);
    dayStartSetting.setTitle( day_start_title );
    // Optional Setting. When the user opens up the time picker,
    dayStartSetting.setDefaultTime(day_start_hh_in, day_start_mm_in, ss_default); // Format: hour, minute, second
  }
  dayStartSetting.update();
  
  if( nightStartSetting.isPressed() ) { 
    nightStartSetting.ack();
    // Display time picker and store it in the three variables - hh, mm, and ss
    nightStartSetting.getTimeInput(&night_start_hh_in, &night_start_mm_in, &ss_in); 
    // String the three variables into a single time string
    sprintf( night_start_title, "Night Start: %02d:%02d", night_start_hh_in, night_start_mm_in);
    nightStartSetting.setTitle( night_start_title );
    // Optional Setting. When the user opens up the time picker,
    nightStartSetting.setDefaultTime(night_start_hh_in, night_start_mm_in, ss_default); // Format: hour, minute, second
  }
  nightStartSetting.update();
  
  lamp_in               = lampSetting.getSliderValue( INT );
  low_light_in          = lowLightSetting.getSliderValue( INT );
  day_start_in          = dayStartSetting.getSliderValue( FLOAT );
  night_start_in        = nightStartSetting.getSliderValue( FLOAT );
  min_air_humidity_in   = minAirHumiditySetting.getSliderValue( INT ); // Retrieve integer value
  max_air_humidity_in   = maxAirHumiditySetting.getSliderValue( INT ); // Retrieve float value
  day_air_temp_in       = dayAirTempSetting.getSliderValue( FLOAT );
  night_air_temp_in     = nightAirTempSetting.getSliderValue( FLOAT );
  min_soil_moisture_in  = minSoilMoistureSetting.getSliderValue( INT ); // Retrieve integer value
  max_soil_moisture_in  = maxSoilMoistureSetting.getSliderValue( INT ); // Retrieve float value
  soil_temp_in          = SoilTempSetting.getSliderValue( FLOAT );
  night_soil_temp_in    = nightSoilTempSetting.getSliderValue( FLOAT );
  fan_run_min_in        = fanRunMinSetting.getSliderValue( FLOAT );
  fan_off_min_in        = fanOffMinSetting.getSliderValue( FLOAT );
  resevoir_alert_in     = resevoirAlertSetting.getSliderValue( INT );
  
  lampSetting.update();
  lowLightSetting.update();
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
    RTC.adjust( DateTime( year, month, day, hour, minute, second ) );
    time_synced = true;
  }
}     // END of ANDEE UPDATE

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

// Arduino will run instructions here repeatedly until you power it off.
void loop() {
  
  //Serial.println( Andee.isConnected() );
  Serial.println();
  Serial.println( "Start loop" );
  
  // do Andee processing if connected
  if  ( Andee.isConnected() ) {
    Serial.println( "iOS connected -- update Andee" );
    andee_update();
  // } else if ( !( Andee.isConnected() ) && ( time_synced ) ) {
  } else if ( time_synced ) {
    Serial.println( "iOS! Disconnected" );
    Serial.println( "Next connect - will sync time" );
    time_synced = false;
  }
  
  // update lcd display
  lcd_display();
  
  lamp_control();
  
  delay(500); // Always leave a short delay for Bluetooth communication
}
