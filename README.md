# Welcome

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="git/Yellow_on_black.svg">
  <source media="(prefers-color-scheme: light)" srcset="git/Black_on_yellow.svg">
  <img alt="OAL Logo" src="git/Just_Black.svg">
</picture>

## What is Open A-Life?
Open A-Life is an attempt at a modular and open source version of the A-Life system found in the S.T.A.L.K.E.R video game franchise, designed to be easily embedded into any application under the Apache 2.0 license!

Open A-Life simulates a world in the form of a 2D grid of cells. This world is then populated by different factions which may interact with eachother in various different ways. These could be traders seeking deals, diseases ravaging towns, armies seeking more land, or whatever you may want to add.

## How does it work?
Open A-Life is comprised of 3 distinct sections. They are:

 - **The Backend**: This is where the world and all of its factions are initialised and the AI's can run and update the API folder. If this was a restraunt, they would be the kitchen staff

 - **The Frontend**: This is what the user will see

 - **The API**: This is the intermidarary folder that both the Backend and Frontend read from and write to. If this was a restraunt, they would be our waitors


# The Backend

The backend is currently being offered in **C++** which is currently still in development *(it was originally being coded in C, hense why much of the code is closer to C than C++)* , and a **python** version will be entering development soon.
Every implementation of the backend _**MUST**_ accomplish the following requirements in order for everything to work smoothly: 

 - Read and set parametres from **/API/Settings.ALC**, and possibly update it should any changes to the factions occur
 
 - Read the state of the World from **/API/World.csv** and write the current world to **/API/World.w**
 
 - Read and adjust behaviour according to **/API/What.todo**. Operation.mode should be a number which corolates to a function, such as exiting, adjusting speed of execution, pausing, etc... _These codes can be found in the table below_


Further details of how each implementation works can be found in the **Readme.md** of each implementation's folder... _Which will be coming soon!_


Each implementation should be similiar enough in structure and should ideally follow the following format:



## C++

### Declarations

This is more specific to C and C++ but there should ideally be a Declarations.h file which should hold all of our macros, function declarations, and type definitions.
 
 
 
### World

This is where the World Cell class should be defined.

Each cell should have the following:

 1. The **integer ID** of the owning faction
 
 2. An **integer** value expressing how difficult the cell is to physically traverse
 
 3. A way of identitfying which weather and climate is currently active, can be done in an **enum** or **integer**, or whatever you may prefer in your own implementation!
 
 4. How many spare slots for other agents are there, best use an **integer** for this.  
 
 5. An **array** of Agent ID's in those slots and their buffs and debuffs there.
 
 6. The local population size
 
 7. How large the local munitions stockpile is. This will determine the governing force's ability to:
  - **Attack** neighbouring cells
  - **Defend** against attacks both domestic and foreign
 
 8. How large the local supplies stockpile is. This would be medicine, goods, etc... 
 
 9. Local population contentness, this should just be an integer how happy or subjugated the local population is
 
 
 
 ### Faction
 
 There are 4 distinct Faction types so far
 
  - A Faction could be commanded from a central HQ. Holds land and needs a "home" cell. **Eg: An organised army**
  
  - A Faction could be autonomous. Holds land but does not need a home cell. **Eg: Bandits**
  
  - Traders/Travellers also qualify as a faction. They don't hold land but travel to targetted cells based on certain conditions.
  
  - Diseases act like Traders, except they just enter into adjacent territory
  
  
Factions can also have **agents**. The purpose of agents is to give each faction some more character. Let's say there is a **Red Army** Faction, the Red Army could have an agent which could be a person or squad which is traversing the world on their own mission. They can also visit individual cells and participate in missions such as trade, sabotage, or just visiting. 

Agents should contain:
 
 - The owning Faction's ID
 
 - A Unique ID
 
 - A Unique Name
 
 - Targetted Location *(Where they're going to)*
 
 - What their mission is *(Trade, diplomacy, sabotage, etc... Can be done with a simple enum)*
 
 - How much of a difference will they make in their mission. Will they bring
 
 
  
  
# API

The API folder is where all of our API files shall be. The required files and their responsibility are as follows:

## Required Files

 - **Settings.ALC**: This is where our settings and parametres will be. It should hold all of our parametres and be strctured in a similar enough way to a .ini file. For saftey reasons, all parametres should ideally have a **;** at the end.
 
 - **Factions.CSV**: A .csv file of all of our factions and their details. .CSV files are the most easy to edit as libraries already exist to edit them.
 
 - **World.w**: This is the status of the world, who owns what and the status of each cell. The 'W' file extension should show that this file could still be written to and is not yet completed
 
 - **World.csv**: This is the fully completed version of World.w. Is ready to be read from and copied

 - **Status.log**: This file should be written to by our backend. It should involve the status of the backend and notify the frontend of it's own operation, such as *Working normally* or *Severe error X encountered... Exiting*

 - **What.ToDo**: This file will be read by our backend and it will determine all of it's actions based on the code it recieves. The code lookup table can be found below:
 

### What.todo Code lookup table

| Code Number | Description |
| ----------- | ----------- |
| C ***Epoch timestamp*** | Continue running as normal. The timestamp is there to shut down the backend if the stamp hasn't been updated after a specified time |
| A | Continue running as normal. I don't advise using this as the backend must be shutdown manually if there is no frontend to shut it down |
| S | Run at slowest settings |
| F | Run at normal settings |
| T ***X*** | Set the Speed divider of the backend to ***X*** |  
| P | Pause the backend immediately |
| U ***X*** | Pause the backend for ***X*** seconds |


# Quickstart

## Backend

### C/C++

To get started using the **C/C++**, simply go to the appropriate folder and compile **main.cpp**.

All nessesary files should be in the one folder and no additional includes are needed in compiler arguements
