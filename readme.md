# Lab 15: Space Invaders

This project is a simple Space Invaders recreation that runs on the TM4C123GH6PM microcontroller (Tiva Launchpad).  
It takes input from the user from buttons and a slide potentiometer and uses a Nokia5110 screen.
This project builds on the work that I have done over several previous labs developing modules for a DAC, ADC, outputting sound, handling user input, etc.
I completed this project in December 2023

# Notes

I decided to move on from project after getting a fully functional but simple game.  
I Could have spent more time making the game more complex but I completed all of my learning objectives;
time spent making the game more fleshed-out and fixing bugs will be better spent learning more from different projects.
I may return in the future to do some refactoring.

# What I learned:
* Edge-triggered interrupts
* Implemented a timer that wasn't SysTick
* Implemented objects, inheritance and polymorphism in C, improving my understanding of OOP and how it works underneath the hood, specifically the use of vtables
* Implemented interrupts of different priorities so that the high frequency sound driver can interrupt the low frequency game logic
* Created a game engine and game from scratch using OOP in C
* Implemented everything without using the heap to improve my understanding of the challenges of programming without it.
  * i.e. local variables get erased when the program moves out of scope, so pointers cannot be passed from functions to its calling function; the pointer must originate in the calling function
	* This is an area that I could do more research into how people handle this problem

# Issues:
* There are some gameplay bugs that are low-priority to fix
* Although the code is somewhat modularized, it is far from ideal.  Refactoring is needed 
* The function documentation is incomplete
* A lot of the logic in the play() function needs to be extracted into helper functions for readability
* I did not use git during the development and only added it after I was mostly done.
