# rfid-interface
Arduino RFID Interface code

## Notes

-	To operate properly all 8 readers need to be plugged in
-	An update will be sent out over serial approximately 3 times a second
-	Serial connection is over USB at a baud rate of 115200.
-	On program start the command start; will be sent out.
-	Every time a serial connection is initiated the program will restart on the Arduino.
-	The system will always return 8 x 8 character strings separated by a comma (,) and terminated with a semi-colon (;)
-	Each block of 8 characters represents the 4 byte unique identifier from the RFID card if present
-	Other codes sent are;
o	ffffffff – standard reply, no card present.
o	00000000 – failed read or other error. (I’ve never seen it throw this error under test)
o	conflict – This happens if 2 readers are too close to each other and they both read the same card number at the same time. It can also happen if a card is moved to another reader very quickly. Individual instants of  this error can be ignored.
-	If messages are returning slowly (less than once a second) it means a reader has failed or is not connected correctly

