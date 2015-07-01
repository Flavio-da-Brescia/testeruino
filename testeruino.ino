#include <LCD.h>
#include <LiquidCrystal_I2C.h>

/* YourDuino.com Example Software Sketch
 16 character 2 line I2C Display
 Backpack Interface labelled "YwRobot Arduino LCM1602 IIC V1"
 terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.


/*-----( Declare Constants )-----*/
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

#include <SoftwareSerial.h>
#include <stdio.h> // for function sprintf

//_________________________________________________________________________________________PIN
//#define                0 
//#define                1 
//#define                2
//#define                3
//#define                4 
//#define                5
#define       btnSu      6 
#define       btnGiu     7
#define       btnSelect  8 
//#define                9 
//#define               10 
//#define               11    
//#define               12
//#define               13
//------------
//#define               A6
//#define     pinASette A7
//#define               A5 SCL
//#define               A4 SDA 
//#define               A3
//#define               A2 
//#define               A1 
#define       pinAZero  A0 

//_________________________________________________________________________________________VARIABILI
float      valoreAZero;
float      mediaAZeroI      =    0;
float      mediaAZeroC      =    0;
float      massimoAZero     =    0;
float      minimoAZero      = 1023;
int        iterAZero        =    3;
int        campioniAZero    =    3;


int        btnStateSu              =    LOW;
int        btnStateGiu             =    LOW;
int        btnStateSelect          =    LOW;
int        pagina                  =      0;



//_________________________________________________________________________________________SETUP
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  pinMode            (pinAZero,       INPUT);
  pinMode            (btnSu,          INPUT);
  pinMode            (btnGiu,         INPUT);
  pinMode            (btnSelect,      INPUT);
 Serial.begin(9600);  // Used to type in characters
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight

// ------- Quick 2 blinks of backlight  -------------
  for(int i = 0; i< 2; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on 
} 

//_________________________________________________________________________________________LOOP
void loop ()
{
  lcd.clear();
  sensoreAZero ();
  if (pagina == 0)
  {
      lcd.setCursor(0,0);
      lcd.print("Attuale= ");
      lcd.setCursor(9,0);
      lcd.print(valoreAZero);      
  }
  else if (pagina == 1)
  {
      lcd.setCursor(0,0);
      lcd.print("Max=    ");
      lcd.setCursor(9,0);
      lcd.print(massimoAZero);      
  }
  else if (pagina == 2)
  {
      lcd.setCursor(0,0);
      lcd.print("Min=    ");
      lcd.setCursor(9,0);
      lcd.print(minimoAZero);      
  }
  else if (pagina == 3)
  {
      lcd.setCursor(0,0);
      lcd.print("Campioni= ");
      lcd.setCursor(10,0);
      lcd.print(campioniAZero);      
  }
  else if (pagina == 4)
  {
      lcd.setCursor(0,0);
      lcd.print("   Iter=  ");
      lcd.setCursor(10,0);
      lcd.print(iterAZero);      
  }
  else if (pagina > 4)
  {
      pagina = 0;      
  }
  
  lcd.setCursor(0,1);
  lcd.print(mediaAZeroI);
  lcd.setCursor(10,1);
  lcd.print(mediaAZeroI/204.6);
  lcd.setCursor(14,1);
  lcd.print("V");
  delay(200);
  btnStateSelect = digitalRead(btnSelect);
  btnStateSu     = digitalRead(btnSu    );
  btnStateGiu    = digitalRead(btnGiu   );
  if (btnStateSelect == HIGH) {pagina = pagina + 1; delay (500);}
  if (btnStateSu     == HIGH && pagina == 1) {massimoAZero  =                 0; delay (500);}
  if (btnStateSu     == HIGH && pagina == 2) {minimoAZero   =              1023; delay (500);}
  if (btnStateSu     == HIGH && pagina == 3) {campioniAZero = campioniAZero + 1; delay (500);}
  if (btnStateSu     == HIGH && pagina == 4) {iterAZero     = iterAZero     + 1; delay (500);}
  if (btnStateGiu    == HIGH && pagina == 1) {massimoAZero  =                 0; delay (500);}
  if (btnStateGiu    == HIGH && pagina == 2) {minimoAZero   =              1023; delay (500);}
  if (btnStateGiu    == HIGH && pagina == 3) {campioniAZero = campioniAZero - 1; delay (500);}
  if (btnStateGiu    == HIGH && pagina == 4) {iterAZero     = iterAZero     - 1; delay (500);}
  
}
  

//_________________________________________________________________________________________FUNCTIONS
void sensoreAZero ()
{ mediaAZeroC = 0;
  for (int x = 0; x < campioniAZero; x++)
  {
    valoreAZero = analogRead(pinAZero);
    mediaAZeroC = mediaAZeroC + valoreAZero;
  }
  mediaAZeroC = mediaAZeroC / campioniAZero;
  mediaAZeroI = ((mediaAZeroI * (iterAZero - 1) + mediaAZeroC)/iterAZero);
    if (mediaAZeroC> massimoAZero)
    {
      massimoAZero = mediaAZeroC;
    }

    // record the minimum sensor value
  if (mediaAZeroC < minimoAZero)
    {
      minimoAZero = mediaAZeroC;
    }
  
}


    

    
    

  



