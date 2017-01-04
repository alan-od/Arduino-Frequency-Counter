#Arduino Based Frequency Counter Kit
***Construction Details***

Please read these instructions prior to building the circuit board.

Before constructing the Frequency Counter give some thought as to how you wish to mount the device in an enclosure.  The 'Counter can be constructed “as is” with the display mounted to the circuit card.  An alternative is to connect the display via a set of flying wires to ease packaging within a standard style case. 

Solder the components to the board in steps 1 to 8 as set out in this document i.e. resistors first followed by capacitors, diodes etc.

**Step 1 -  Resistors**

Use a meter to check resistance values.

R1 R6  R11 R12 R13  R14 R15 R16			10K (8)

R8 R9							1M (2) R8 has capacitor attached

R7							220K (1)

R17							330 (1)

**Step 2 - Capacitors**

C6 C8 C9 C10 C11 C13 				100nF (6)

C5 C12 C14 C15 10nF (4)  Note C5 leads need adjusting for mounting holes.

C1							33pF (1)

C16							3.9pF (1) See R8

**Step 3 - Diodes**

Pay attention to the polarity of the diodes.

D1 D2 1N4148 (2)

D4 IN5817 (1)

**Step 4 - Variable Resistor**

RV1 RV2						10K trimmers (2)

**Step 5 - Integrated Circuits**

Note there's a cut out at the top of the dual in line integrated circuits.  This indent should should be opposite the white silk screen text printed on the board.  Also see the direction the chips are placed in the attached picture.

U1 74HC74 (1)

U3 U4 74AC00 (2)

U7							74AC393 (1)

U6							Arduino (1) – do not push the module hard 								down to the board, it should be positioned 2 to 							3mm above the board.



**Note - Clock Module ** The pins on this modules needs to be straighten. Care needs to be taken while straightening these pins such that no strain is placed upon the solder joints between the header pins and the board (use small long nose pliers to support the pin leg close to the plastic header).  If excessive strain is applied to the joints while the pins are straightened the module will fail.

U5 Clock module (1) – straighten pins with long nose pliers. The module should not be pressed hard down to the board, it should be positioned 2 to 3mm above the board.

**Step 6 - Connectors**

P2 P4 P6 P5						Not required (see photo)

P1 P3 							2 pin header
						
DS1 connector					16 pin header

The multi-pin header supplied should be cut to the appropriate length by cutting along an indent on the strip using side cutters.

For the display (DS1), position the header on the underside of the board such that the shorter pins pass through the board.  You will solder the display header from the top side of the board.  

Solder only one pin ensuring the header is perpendicular to the board.  If it is at a slight angle apply the soldering iron to the one soldered pin and adjust the header while the solder is molten.  Only solder the entire header once it is perpendicular to the board.




**Step 7 - Switches**

Mount the switches on the underside of the board – see photo.

SW1 SW2 SW3					Push switches (3) 

**Step 8 - Display**

Important
Prior to soldering the display use insulating tape to protect the circuit board (see photo).  Note the display is mounted on the underside of the board.

DS1							2 x 16 LCD module (1)

##Setting up 

Apply power to the 'Counter either using a USB lead connected between a power source (computer or PSU) and the Ardino or a 9V DC supply to the power pin P3 ensuring correct polarity.

Using a small screw driver adjust RV2 until characters can be viewed on the display.  Adjust for best contrast.  

With a digital voltmeter adjust RV1 until the voltage between ground and the wiper of the RV1 (top of R7 220k resistor) is approximately 2.4 volts.

To enter the menu system press the left hand switch and scroll back and forth using the other two switches.  Set up the time and date “Confirming” the selections.  Calibration should not be required but does provide an offset of 0.1Hz per MHz if required (each unit displayed is 0.1Hz).  This granularity may be changed in the future.

The device should measure between 1KHz and 75MHz. 





*AOD 1st January '16*