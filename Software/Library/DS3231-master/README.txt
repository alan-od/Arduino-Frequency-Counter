DS3231
======

A Modified Library for using a DS3231 RTC with an Arduino Mega.

The initial library was created by Eric Ayars in 2011 and modified in 2012 by John Hubert.

I have added 3 new functions.
1) CheckEOSC    Checks the status of the EOSC (Enable Oscillator Flag) bit
2) CheckINTCN   Checks the status of the INTCN(Interupt Flag) bit
3) enableINTCN  Enables/disables the INTCN bit

For fuller details please look at the datasheet for the DS3231 Chip which is available from:-
http://datasheets.maximintegrated.com/en/ds/DS3231.pdf
