//***************************************************************
//  TM2030_Serial_Data
//  v0.0.1b
//  Gordon Boulton
//  EorEquis@tristarobservatory.space
//
//  Version History
//  0.0.1b        03/25/2018        First master branch for sharing
//***************************************************************

#include <SoftwareSerial.h>

char buffer[1024];


SoftwareSerial TriMetric(2, 3); // RX, TX for TM-2030
SoftwareSerial SC2030(4, 5); // RX, TX for SC-2030

  // Function to return TriMetric data from pin 4 of the TriMetric. This is the stream being sent to the SC-2030 by the TriMetric.
  // Comments below document TM2030 data, TM2025 has fewer values
  // I've tried to indicate what's available for which unit (Both, or just 2030), but may be off, as I don't have a TM2025 to test with.
  // *********************************************************
  //  V = Volts (Batt 1)  *Both
  //  FV = Filtered Volts (Batt 1)  *Both
  //  V2 = Volts (Batt 2) *Both
  //  A = Amps  * Both
  //  FA = Filtered Amps (Batt 1) *Both
  //  PW = Charge controller pulse width (First number is charge state, then is hex number defineing pulse width from 0-FF hex.)  *2030
          // Charge State Values
          // 0 - Discharging, < 98% Full : See section 4.5.3 of http://www.bogartengineering.com/sites/default/files/docs/SC2030-9-10-15-UsersInstruc.pdf
          // 1 - Bulk Charge
          // 2 - Absorb
          // 3 - Float
          // 4 - Finish
          // 5 - Max Voltage Finish
          // 6 - Was in float, now discharging, still > 98% Full  
  //  AH = Amp Hours From Full  * Both
  //  T% = State of charge  * Both
  //  W = Watts * Both
  //  DSC = Days Since Charged  * Both
  //  DSE = Days Since Equalized  * Both
  //  PW = (Why is PW here twice??  No effing clue) *2030
  //  r% = Replaced Percentage Data - Replaced percentage of used AH since last full charge   *2030
  //  pD = Lowest previous discharge Amp Hours.  Total used, remaining capacity?  I dunno yet.    *2030
  
  void getTriMetric() {
    const char introChar = 'T';
    bool introCharRx = false;
    TriMetric.begin(2400);
    while (!introCharRx) {
      if (TriMetric.available() > 0) {
        char c = TriMetric.read();
        if (c == introChar) {
          Serial.print(c);
          introCharRx = true;
        }
      }
    }
    while (introCharRx) {
      if (TriMetric.available() > 0) {
        char c = TriMetric.read();
        if (c != introChar) {
          Serial.print(c);
        }
        else if (c == introChar) {
          introCharRx = false;
        }
      }
    }
    TriMetric.end();
  }

  // Function to return SC2030 data from pin 5 of the TriMetric. This is the stream being sent to the TriMetric by the SC-2030.
  // Contains only 2 values, Battery (T)emp and Solar (A)mps.
  //  I haven't yet figured out how the heck the (A)mps are calculated.  Still playing with this one.
  
  void getSC2030() {
    const char introChar = 'T';
    bool introCharRx = false;
    SC2030.begin(2400);
    while (!introCharRx) {
      if (SC2030.available() > 0) {
        char c = SC2030.read();
        if (c == introChar) {
          Serial.print(c);
          introCharRx = true;
        }
      }
    }
    while (introCharRx) {
      if (SC2030.available() > 0) {
        char c = SC2030.read();
        if (c != introChar) {
            Serial.print(c);
          }
        else if (c == introChar) {
          introCharRx = false;
        }
      }
    }
    SC2030.end();
  }
  
void setup(){

  Serial.begin(9600);     // UART Serial for comm w/ PC

}   // End Setup

void loop(){
while (Serial.available() > 0) {
      String strCmd = Serial.readStringUntil('#');
      if (strCmd == "tm") {
        getTriMetric();
        Serial.println();
      }
      else if (strCmd="sc") {
        getSC2030();
        Serial.println();
      }
}
} // End Loop
