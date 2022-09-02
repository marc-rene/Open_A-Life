# Welcome
![Open A-Life Logo](git/logo.svg)
## What is Open A-Life?
Open A-Life is an attempt at a modular and open source version of the A-Life system found in the S.T.A.L.K.E.R video game franchise, designed to be easily embedded into any application under the Apache 2.0 license!

Open A-Life simulates a world in the form of a 2D grid of cells. This world is then populated by different factions which may interact with eachother in various different ways. These could be traders seeking deals, diseases ravaging towns, armies seeking more land, or whatever you may want to add.

## How does it work?
Open A-Life is comprised of 3 distinct sections. They are:

 - **The Backend**: This is where the world and all of its factions are initialised and the AI's can run and update the API folder. If this was a restraunt, they would be the kitchen staff

 - **The Frontend**: This is what the user will see

 - **The API**: This is the intermidarary folder that both the Backend and Frontend read from and write to. If this was a restraunt, they would be our waitors


# The Backend

The backend is currently being offered in **C** and **C++** which are all currently still in development, and a **python** version will be entering development soon.
Every implementation of the backend _**MUST**_ accomplish the following requirements in order for everything to work smoothly: 

 - Read and set parametres from **../API/Settings.OALC**, and possibly update it should any changes to the factions occur
 
 - Read the state of the World from **../API/Ready.world** and write the current world to **../API/writing.world**
 
 - Read and adjust behaviour according to **../API/Operation.mode**. Operation.mode should be a number which corolates to a function, such as exiting, adjusting speed of execution, pausing, etc... _These codes can be found in the table below_


Further details of how each implementation works can be found in the **Readme.md** of each implementation's folder... _Which will be coming soon!_


Each implementation should be similiar enough in structure and should ideally follow the following format:



## Declarations

This is more specific to C and C++ but there should ideally be a Declarations.h file which should hold all of our macros, function declarations, and type definitions.
 
 
 
## World

This is where the World Cell class should be defined.

Each cell should have the following:

 1. The integer ID of the owning faction
 2. An integer value expressing how difficult the cell is to physically traverse
 3. A way of identitfying which weather and climate is currently active, can be done in an enum or integer, or whatever you may prefer in your own implementation!
 4. How many spare slots for other factions are there.  
 
