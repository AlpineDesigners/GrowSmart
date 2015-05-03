void init_config() {
 
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
  
}
