include <SoftwareSerial.h>

SoftwareSerial TriMetric(2, 3); // RX, TX for TM-2030
SoftwareSerial SC2030(4, 5); // RX, TX for SC-2030

void setup(){

  Serial.begin(9600);     // UART Serial for comm w/ PC
  TriMetric.begin(2400);  // TriMetric
  SC2030.begin(2400);     // SC2030
  
}   // End Setup

void loop(){

  // Read the TriMetric data stream being sent to the SC-2030
  // Includes :
  //  V = Volts (Batt 1)
  //  FV = Filtered Volts (Batt 1)
  //  V2 = Volts (Batt 2)
  //  A = Amps
  //  FA = Filtered Amps
  //  PW = Charge controller pulse width (First number is charge state, then is hex number defineing pulse width from 0-FF hex.)
          // Charge State Values
          // 0 - Discharging, < 98% Full : See section 4.5.3 of http://www.bogartengineering.com/sites/default/files/docs/SC2030-9-10-15-UsersInstruc.pdf
          // 1 - Bulk Charge
          // 2 - Absorb
          // 3 - Float
          // 4 - Finish
          // 5 - Max Voltage Finish
          // 6 - Was in float, now discharging, still > 98% Full  
  //  AH = Amp Hours From Full
  //  T% = State of charge
  //  W = Watts
  //  DSC = Days Since Charged
  //  DSE = Days Since Equalized
  //  PW = (Why is PW here twice??  No effing clue)
  //  r% = Replaced Percentage Data - Replaced percentage of used AH since last full charge
  //  pD = Lowest previous discharge Amp Hours.  Total used, remaining capacity?  I dunno yet.
  
  // Contents partially documented here : http://www.bogartengineering.com/sites/default/files/docs/TM2025-TM2030%20Technical%20Information%20On%20Serial%20Data%20Output_0.pdf
  // This is MOSTLY an ASCII data stream, but the PW values appear to be in Hex?
  // You'll have to sanitize the data to drop high ASCII garbage characters, and then parse as you see fit for further handling.
  
  if (TriMetric.available() > 0) {
    char a = TriMetric.read();
   Serial.write(a);
  }


  // Read the SC-2030 data stream being sent to the TriMetric
  // Contents not documented that I can find.  Appears to contain only 2 values :
  // This is a mixed ASCII and Hex data stream.  You'll need to use something like CoolTerm and view the Hex data being sent for these values.
  //  T = Battery Temp (If SC2030 is equipped).  Presented as 2 Hex bytes, duplicated.  E.G. T=1212 -> Hex 12 -> 18° C
  //  A = Solar current.  Presented as 2 Hex Bytes.  Unknown if first is a multiplier, or if this is a 4 digit hex number.  Suspect the latter.
  // You'll have to sanitize the data to drop high ASCII garbage characters, and then parse as you see fit for further handling.
  // Haven't yet figured out how I'm going to read both without them stepping on each other.

  
//  if (SC2030.available() > 0) {
//    char a = SC2030.read();
//   Serial.write(a);
//  }

} // End Loop
