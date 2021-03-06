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

// easier use for no / nc relays
//#define RELAY_ON              LOW;
//#define RELAY_OFF             HIGH;

// Live settings
int RELAY_ON  = LOW;
int RELAY_OFF = HIGH;
/* Test Env
int RELAY_ON  = HIGH;
int RELAY_OFF = LOW;
*/

// PIN USAGE
//#define PIN_A0                A0
//#define INNER_AIR_PROBE_PIN   A1  // lab temp and humidity probe pin
//#define OUTER_AIR_PROBE_PIN   A2  // outside temp (and humidity with DHT22 probe )
//#define SOIL_PROBE_PIN        A3  // humidity & temp with ??? probe)
//#define SOIL_MOIST_PROBE_PIN  A3  // humidity or (temp and humidity with DHT22 probe)
//#define SOIL_TEMP_PROBE_PIN   A4  // temp soil probe with 10K thermistor
//#define PROXIMITY_PROBE_PIN   A5  // know when to make displays visible when a person is nearby

#define INNER_AIR_PROBE_PIN   A6  // lab temp and humidity probe pin
#define OUTER_AIR_PROBE_PIN   A7  // outside temp (and humidity with DHT22 probe )
#define PROXIMITY_PROBE_PIN   A8  // know when to make displays visible when a person is nearby
//#define AQUA_STOP_PROBE_0_PIN A6
//#define AQUA_STOP_PROBE_1_PIN A7
//#define PIN_A8                A8
#define WATER_TEMP_0_PIN      A9
#define WATER_TEMP_1_PIN      A10

#define LIGHT_PROBE_0_PIN     A11
#define LIGHT_PROBE_1_PIN     A12
#define PIN_A13               A13
#define PIN_A14               A14
#define AMPERAGE_PROBE_PIN    A15  // current usage probe

// shield reserved pins -- DO NOT CHANGE USAGE
#define SERIAL_RX_0_PIN       0  // reserved by Serial
#define SERIAL_TX_0_PIN       1  // reserved by Serial
#define INTERRUPT_0           2  // PWM & Interrupt 0
#define INTERRUPT_1           3  // PWM & Interrupt 1
/*
#define FAN_DIRECTION_PIN     4  // PWM  - reserved by MOTOR shield & romeo
#define FAN_SPEED_PIN         5  // PWM - reserved by MOTOR shield & romeo
#define PUMP_SPEED_PIN        6  // PWM - reserved by MOTOR shield & romeo
#define PUMP_DIRECTION_PIN    7  // PWM - reserved by MOTOR shield & romeo
*/
#define ANDEE_SHIELD_PIN      8  // PWM  - reserved by ANDEE shield
// ClimeCase output pins
#define AIR_TEMP_CTRL_PIN     9  // PWM - for air heating intensity control
#define SOIL_TEMP_CTRL_PIN   10  // PWM - for soil heating intensity control

//#define LAMP_0_CTRL_PIN      11  
//#define LAMP_1_CTRL_PIN      12
//#define PIN_11               11  // PWM - for lamp brigthness control
//#define HUMIDIFIER_CTRL_PIN  12  // PWM - humidifier on/off control pin
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

#define LAMP_0_CTRL_PIN      22  
#define LAMP_1_CTRL_PIN      23

#define AQUA_PUMP_CTRL_PIN   24  
#define AQUA_PUMP_0_CTRL_PIN 24  
#define AQUA_PUMP_1_CTRL_PIN 25  
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
DHT inner_dht( INNER_AIR_PROBE_PIN, DHTTYPE );
DHT outer_dht( OUTER_AIR_PROBE_PIN, DHTTYPE );

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
AndeeHelper lampBrigthSetting;
AndeeHelper sunnyDaySetting;
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
char user_title_set[32];
char project_title[40] = "GrowSmart";
char project_title_default[40] = "GrowSmart";
char day_start_title[20];
char night_start_title[20];
char time_string[30];
char air_string[20];

int ios_day;
int ios_month;
int ios_year;
int ios_hour; 
int ios_minute;
int ios_second;

int   ss_set                    = 0;
int   ss_default                = 0;
int   lamp_bright_set           = 100;
int   lamp_bright_default       = 100;
int   sunny_day_default         = 95;
int   day_start_hh_default      = 04;
int   day_start_mm_default      = 45;
int   day_start_ss_default      = 00;
//long  day_start_default         = (long)day_start_hh_default * 10000 + (long)day_start_mm_default * 100;
int   night_start_hh_default    = 23;
int   night_start_mm_default    = 45;
int   night_start_ss_default    = 00;
//float  night_start_default       = (long)night_start_hh_default * 10000 + (long)night_start_mm_default * 100;

int   min_air_humidity_default  = 50;
int   max_air_humidity_default  = 75;
float day_air_temp_default      = 22.0;
float night_air_temp_default    = 14.0;

int   min_soil_moisture_default = 25;
int   max_soil_moisture_default = 75;
float soil_temp_default         = 20.0;
float day_soil_temp_default     = 25.0;
float night_soil_temp_default   = 18.0;

// run for 4 mins & 30 seconds
float fan_run_min_default       = 4.5;
// off for 15 mins & 30 seconds
float fan_off_min_default       = 15.5;
int   resevoir_alert_default    = 20;

int   sunny_day_set             = sunny_day_default;
int   day_start_hh_set          = day_start_hh_default;
int   day_start_mm_set          = day_start_mm_default;
int   day_start_ss_set          = 00;
long  day_start_set             = (long)day_start_hh_set * 10000 + (long)day_start_mm_set * 100;
int   night_start_hh_set        = night_start_hh_default;
int   night_start_mm_set        = night_start_mm_default;
int   night_start_ss_set        = 00;
long  night_start_set           = (long)night_start_hh_set * 10000 + (long)night_start_mm_set * 100;
int   min_air_humidity_set      = min_air_humidity_default;
int   max_air_humidity_set      = max_air_humidity_default;
float day_air_temp_set          = day_air_temp_default;
float night_air_temp_set        = night_air_temp_default;
int   min_soil_moisture_set     = min_soil_moisture_default;
int   max_soil_moisture_set     = max_soil_moisture_default;
float soil_temp_set             = soil_temp_default;
float day_soil_temp_set         = day_soil_temp_default;
float night_soil_temp_set       = night_soil_temp_default;
float fan_run_min_set           = fan_run_min_default;
float fan_off_min_set           = fan_off_min_default;
int   resevoir_alert_set        = resevoir_alert_default;

int   wait_delay = 4000;

boolean time_synced = false;
boolean time_synched = false; 


// define sensing values
float
box_temp,
box_humidity,
room_temp,
room_humidity,
soil_temp,
soil_humidity;

void setup() {
  
  //init_variables();
  
  // setup serial debugging
  Serial.begin( 9600 );
  Serial.println("BioBox Serial Defined:\n");
  delay( 500 );
  Serial.println( "Setup" );
  Serial.println();
  Serial.println( "Day Start Default: " );
  Serial.print( day_start_hh_default );
  Serial.print( ":" );
  Serial.println( day_start_mm_default );
  Serial.println( "Day Start Set: " );
  Serial.print( day_start_hh_set );
  Serial.print( ":" );
  Serial.println( day_start_mm_default );
  Serial.println();
  Serial.println( "Night Start Default: " );
  Serial.print( night_start_hh_default );
  Serial.print( ":" );
  Serial.println( night_start_mm_default );
  Serial.println( "Night Start Set: " );
  Serial.print( night_start_hh_set );
  Serial.print( ":" );
  Serial.println( night_start_mm_default );
  
  init_config();
  
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

// Arduino will run instructions here repeatedly until you power it off.
void loop() {
  // do on first loop 
  Serial.println( "start loop" );
  // do Andee processing if connected
  andee();
  
  // update lcd display
  lcd_display();
  
  lamp_control();
  Serial.println( "---------" );
  Serial.println( );
  delay(1000); // Always leave a short delay for Bluetooth communication
}
