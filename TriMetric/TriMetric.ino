#include <SoftwareSerial.h>

SoftwareSerial TriMetric(2, 3); // RX, TX for TM-2030
SoftwareSerial SC2030(4, 5); // RX, TX for SC-2030

void setup(){

  Serial.begin(9600);     // UART Serial for comm w/ PC
  TriMetric.begin(2400);  // TriMetric
  SC2030.begin(2400);     // SC2030
  
}

void loop(){

  // Read the TriMetric data stream being sent to the SC-2030
  // Includes :
  //  V = Volts (Batt 1)
  //  FV = Filtered Volts (Batt 1)
  //  V2 = Volts (Batt 2)
  //  A = Amps
  //  FA = Filtered Amps
  //  PW = ??  (This value appears to also be in Hex for some reason, as I have some values like 10A, 10D, and so on)
  //  AH = Amp Hours (Since ???  Since Charged?)
  //  T% = State of charge?
  //  W = Watts
  //  DSC = Days Since Charged
  //  DSE = Days Since Equalized
  //  PW = ? (Why is PW here twice??  Value is NOT always a repeat of PW above??)
  //  r% = Replaced Percent?  How is this calculated?  Percent of last used, or percent of all used since last full charge, or percent of amount used over some time?
  //  pD = ???
  
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

  
  if (SC2030.available() > 0) {
    char a = SC2030.read();
   Serial.write(a);
  }


}
