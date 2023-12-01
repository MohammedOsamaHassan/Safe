# Safe
Safe Project

Safe Project



##Components:



1. Atmega32 microcontroller.

2. LCD 16x2 display.

3. Keypad.

4. EEPROM memory.



##Description:



The Safe Project is designed to provide a secure storage solution with password protection. Upon the initial use of the safe, the user can set a password. Subsequent users will have two options: to check the entered password or to edit the existing password.



In the password check mode, the user is prompted to enter the password using the keypad. If the entered password is incorrect, the user has three attempts to enter the correct password before the safe enters a blocking mode. Once in the blocking mode, the safe can not exit from this mode until the blocking time ended.



Alternatively, in the password edit mode, the user is required to enter the old password first. If the old password is incorrect, the user only has three attempts and then the safe enters a blocking mode. However, if the old password is correct, the user can proceed to enter a new password, which will replace the old one.


