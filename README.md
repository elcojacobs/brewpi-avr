brewpi-avr
==========

This is the code that runs on the BrewPi AVR/Arduino, and also as a simulator on the desktop.

This project uses Git Flow. The development branch is the newest branch. The master branch is the latest stable branch. This branch works out of the box with the official BrewPi shields. If you do not want to add your own code, you can just download the latest HEX file from http://dl.brewpi.com and use the web interface to upload it to your Arduino.


Project Layout
--------------
The project layout is skewed by the requirement of Atmel Stutio to have all the source files in the project folder.

 - brewpi_avr - all files for building the arduino code
 - brewpi_cpp - "overlay" files that are used in preference to the files in brewpi_avr for building the desktop simulator
 - brewpi_lib - Netbeans project - a static lib from brewpi_cpp/brewpi_avr. NetBeans-integrated unit tests (simpleunit) and Google Test. 
     To run the tests, right click the "Test Files" folder and choose "Test". Simple tests are integrated into the IDE test runner, while GTests are not.
 - brewpi_sim - Netbeans project - a executable application that runs the brewpi-avr code on the desktop as a command line program. Right-click and choose "Run"

This layout is transient and will most like change as we work with the project. 

Include dirs:

 - ./brewpi_cpp
 - ./brewpi_avr
 - ./brewpi_avr/fallback



