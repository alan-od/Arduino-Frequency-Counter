#Arduino-Frequency-Counter

Introduction:

This project was designed as a construction exercise for members of the Crystal Palace Radio club
in South London.

The design goals were:
        Low Cost
        Ease of construction
        Easily Programmed
        Good Performance

To achieve the goals of low cost and ease of programming the design was based around an Arduino
Nano which are cheaply available from China via Ebay and can be easily programmed using the
Arduino IDE (integrated development environment) using a USB connection to a suitable PC.

The performance of a frequency counter is determined by the accuracy and stability of the reference
clock used within the device, as a minimum the clock should be crystal controlled and ideally the
crystal should be temperature controlled (TXCO). In this design the clock source is provided by a
DS3231 RTC (real time clock) module which is available cheaply from Ebay. The DS3231
integrates a TXCO onto a chip and was designed as a high accuracy clock for use within devices
that require time and date information. The DS3231's crystal oscillator runs at 32KHz and by
judicious programming a 1Hz signal can be produced from one of its pins, it's this pulse that's used
as the reference time source within this design.

To enable club members to build the device it was necessary to develop a suitable PCB (printed
circuit board) and to ease construction I deliberately chose to use through hole mounted
components. When laying out the PCB I also included tracking for a prescaler which provides a
separate “divide by ten” facility using a MC12080. The prescaler necessitates the use of surface
mount components and although is adds additional functionality the counter works perfectly well
without it.

Performance:

The prototype used HC series logic and I found that using such chips the highest frequency that
could be measured was around 75MHz. I then found that RS Components could source 74AC393
and 74AC00 chips in DIL packages made by Toshiba. Substituting the 74HC393 for a Toshiba
74AC393 increased the high frequency performance to 115MHz. At the low end the frequency
counter could measure 500Hz, although its low frequency performance may be better I don't have
the necessary equipment to test it.

Tooling:

The PCB was developed using KiCad and the files are available under the hardware directory along
with documentation pertaining to the circuit design.

The software was developed using the Arduino IDE, all source code is included along withdocumentation. 
Currently the source code is around 1000 lines and due to its size I have divided it
into a number of modules and header files. For users to compile the programme it will be necessary
for them to include the Arduino library for the DS3231. Ideally I would have used a different
software tool set, however I deliberately used the Arduino IDE so as to allow other users to easily
import the software files into the Arduino IDE.

General:

No originality is claimed for the design as I have taken ideas from many sources. The majority of
the software is original although a few algorithms have been taken from other sources, where I have
done so I have tried to acknowledge those for their work.


Alan
G8NKM 16 th November 2016
