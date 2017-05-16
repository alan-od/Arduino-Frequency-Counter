# Arduino Based Frequency Counter

**Introduction:**

This project was designed as a construction exercise for members of the Crystal Palace Radio club in South London.



The design goals were:

- Low Cost
- Ease of construction
- Easily Programmed
- Good Performance

To achieve the goals of low cost and ease of programming the design was based around an Arduino Nano which are cheaply available from China via Ebay and are easily programmed using the Arduino IDE (integrated development environment) using a suitable PC.

The performance of a frequency counter is determined by the accuracy and stability of the reference clock used within the device, as a minimum the clock should be crystal controlled and ideally the crystal should be temperature controlled (TXCO). In this design the clock source is provided by a DS3231 RTC (real time clock) module which is available cheaply from Ebay. The DS3231 integrates a TXCO onto a chip and was designed as a high accuracy clock for use within devices that require time and date information. The DS3231's crystal oscillator runs at 32KHz and by judicious programming a 1Hz signal can be produced from one of its pins, it's this pulse that's used as the reference time source within this design.

To enable club members to build the device it was necessary to develop a suitable PCB (printed circuit board) and to ease construction I deliberately chose to use through hole mounted components. When laying out the PCB I also included tracking for a prescaler which provides a separate “divide by ten” facility using a MC12080. The prescaler necessitates the use of surface mount components and although is adds additional functionality the counter works perfectly well without it.

**Performance**:

The prototype used NXP HC series logic and I found that using such chips the highest frequency that could be measured was around 75MHz. I then found that RS Components could source 74AC393 and 74AC00 chips in DIL packages made by Toshiba. Substituting the 74HC393 for a Toshiba 74AC393 but still using the original NXP 74HC00 chips increased the high frequency performance to around 115MHz. I then used all AC series chips and found that the HF performance dropped back to 75MHz which was unexpected.

Since around the end of 2016 RS stopped selling the Toshiba chips and obtaining such chips is now very difficult.  Texas 74HC393 DIL chips are readily available and to this end I purchased a number of SN75HC393 from Farnell and these worked up to around 70MHz.

At the low end the frequency counter measures to 1KHz.

**Tooling**:

The PCB was developed using KiCad and the files are available under the hardware directory along with documentation pertaining to the circuit design.

The software was developed using the Arduino IDE, all source code is included along with documentation. Currently the source code is around 1000 lines and due to its size I have divided it into a number of modules and header files. For users wishing to compile the programme it will be necessary to include the Arduino library for the DS3231. Ideally I would have used a different software tool set, however I deliberately chose to stay with the Arduino IDE so as to allow others to easily import the software files into this development environment.

**Circuit Boards**

Originally twenty boards were manufactured most of which were bought by members of the Crystal Palace Radio and Electronic Club (CPREC) and the Bromley and District Amateur Radio Society (BDARS). I was contacted by Alan VK5ZFJ who was interested in using the frequency counter as a project for the Crawley Amateur Radio Club (CARC). As more boards were required and following discussions with Alan I redesigned the board layout correcting a few problems with the original, reducing the board size. moving the Arduino to the edge of the board to ease the connection of a USB plug when the unit is boxed plus a number of other cosmetic upgrades.

![pics]/Hardware/pics.jpgs)


**General**:

No originality is claimed for the design as I have taken ideas from many sources. The majority of the software is original although a few algorithms have been taken from other sources and where I have done so I have tried to acknowledge those for their work.

*Alan
G8NKM 16th November 2016*
