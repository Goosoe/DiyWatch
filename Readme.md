# Intro 
This project is my take on making a personal time-keeping device with some sensors into the mix using an arduino board and multiple displays.

The final objective is to have a clock relying solely on the atmega 328p chip and the other necessary external components (not dependant on the arduino board).

# Update
Unfortunately, due to the chosen RTC only being able to store up to the seconds value it is impossible to create an arduino board independant hardware, as this implementation requires the use of milliseconds to run. Same goes to the chronometer implementation.

The clock will display time, temperature and altitude plus have an alarm.


# FAQ
## What is the objective of this project?
Mainly to learn about embedded programming and resource constrained systems :)

## Why not use classes on this implementation?
OOP usually shines when multiple instances of the same data-structure is required. For this project I've recognized that it was only needed one instance of each type and so I've done this implementation totally functional.

