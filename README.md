# VEXT 
VEXT provides extensions to regular VEX V5 functionality

We wrote a library to abstract away movement code and allow for writing autons much faster. We created this to help maximize our time efficiency: previously, if time was utilized building the robot, this meant we couldn’t have the bot to test autons. Therefore, we couldn’t code until the last minute. To help save time, we took the bot and put together some common actions: for example, move forward by a certain amount of inches, turn by a certain amount of degrees. We tuned and adjusted the bot until that these actions were reliable. Because we wrote this code in a reusable manner, we could now write autons without having physical access to the bot. This saved us time in the long run and allowed for the creation of a 10-point programming skills auton.

Features
  * Drive code with customizable control set
  * Easy extension for new button setups
  * Two and Four Wheel Drive options
  * Inertial Drive using inertial sensor and Proportional-Derivative control theory for auton movement
  * Bot tracks alliance and reverses turns based on side
  * Extensible Proportional-Derivative system for other uses

