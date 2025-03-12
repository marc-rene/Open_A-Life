
# Overview

  

Welcome to my repository for Open A-Life. An attempt to make an open source version of the **A-Life** system found in [GSC Game Worlds' S.T.A.L.K.E.R](https://en.wikipedia.org/wiki/S.T.A.L.K.E.R.) video game franchise.

  

### What is the "A-Life" System [S.T.A.L.K.E.R]

  

In many open world video games, the world can very often feel static. Actions done by the player may have very little recongnition from others or have little to no impact on the world around them. The purpose of A-life is to simulate this open world in the background. Any actions taken by the players should have a real impact on their enviorment and the economy.

In S.T.A.L.K.E.R, NPCs in the world have their own objectives and their own simulated free will. The player might be given a mission in another region to *"Save Brian from Bandits"*, but after 30 minutes, a Military Convoy could accidentally come across the bandits, apprehending them, and releasing Brain from captivity.

Another example is when the player is in the wilderness, if they were to eliminate an enemy, leave them, and come back after a few hours, there is a chance that other animals could come over and investigate the remains.

This level of simulation in the outside world is what made the A-Life system such a special and unique feature in the S.T.A.L.K.E.R franchise.

  

### What is the "A-Life" System [My version]

  

The ultimate goal of the Open A-Life project, is to make an open source, application & platform agnostic version of the A-Life system found in the S.T.A.L.K.E.R franchise. Open A-Life will be written mostly in **C++20**, and should be able to compile to **Linux and Windows**. Build scripts have a `.bat` and `.sh` versions.

The Open A-Life Core will serve as a framework for other developers to implement their own simulations for their open worlds. An `Example Engine` is included in the respository to demostrate how users can use the Open A-Life system, and possibly how they may incorporate it into their own systems.

  

I have many plans for how to improve the core functionality, but for now this is a huge **work-in-progress** and is no where near complete

  
  

## Architecture

  

Open A-Life is seperated into a **Core + Application** architecture. In this repo, the ``Example Engine`` serves as the **Application** and the ``Core`` serves as the, well... the **Core**, or the **OAL Core Runtime**

  

### Application

The App will always rely on the **Core**.

The main purpose of the App will be to use the libraries and functionality of the Core in a way that suits the needs for the project in question.

If the project is a game that uses Unreal Engine, Unreal would be the Application in this instance and would be responcible for ``#include``ing' the Core libraries and functionality.

  

### Core

The Open A-Life Core Runtime is **Multi-threaded** by default and that is the main focus, but it can also be run on the same thread thanks the the flexibility of the C++ ``Future`` library.

  

The Core is comprised of multiple smaller libraries that tackle different tasks. Some of these modules aren't yet included in the master branch but will be shortly.

  

The Libraries in question as they are now are as follows:


| Name         | Purpose | Information  |
|--------------|---------|--------------|
|``SPDLog``    | Logging | **SPDlog** is a fantastic tool for logging in C++. It supports colours and seperation of **Core** and **App** logging. More information can be found on [their Git repo](https://github.com/gabime/spdlog). |
|``CSV-Parser``| CSV I/O | This CSV library has fantastic functionality with CSV files are used heavily in OAL. More information can be found on [their Git repo](https://github.com/vincentlaucsb/csv-parser). |
|``mINI``      | INI I/O |**Mini INI** is a great library for configuring settings in the form of .ini files. More information can be found on [their Git repo](https://github.com/metayeti/mINI).|
|``File Wizard``| General File Management| **File Wizard** is a custom library for the purpose of managing various files and directories. It encorporates mINI and CSV-Parser in its operation. |
|``Director``| Managing World Events| The **Director** is concerned with triggering various events in the world. This is to make sure that no absolute monopolies or deadlocks happen and that the world stays eventful, preventing it from stalling.|
|``Packet Ninja``|Network Communication| The **Packet Ninja** is responcible for comunicating with between the OAL Core and Application. If a major event happens in the Application, there must be a way of notifying the Core Runtime. Networking will ideally be done over localhost.|
|``Log``|Logging| The **Log** library *(better name coming soon)* acts as a wrapper for ``SPDLog``. Should You ever wish to use a different method to Log events then you would do so by overwriting the methods found in this Class.|

### Pseudocode

    onTick():
    
    
    for  map  in  Universe:     # Each map could have an "event" (Thunderstorms, floods, etc..) to spicen up the current map
        director.should_start_map_event(map)
    
        
        Pre_Tick:    # Apply attrition + modifiers
            for  node  in  map:
                if  node.has_modifiers() ==  True:
                    for  group  in  node:
                        group.apply_attrition_modifier()
    
    
        Faction_AI_Stage:    # Now the factions must make their choices and submit them
            for  faction  in  Factions:
                faction.make_choices()
                faction.submit_choices()
   
    
        Faction_Choice_Evaluation_Stage:     # Now we must resolve/decide all conflicts
            for  choice  in  all_submitted_choices:
                director.evaluate(choice)
                
            if  choice.conflict ==  True:
                all_conflicting_choices.append(choice)
            else:
                director.grant(choice)
          
    
        Conflict_Resolution_Stage:   # Now we must figure out what conflicts and fires we need to sort out
            for  conflict  in  all_conflicting_choices:
                director.resolve(conflict)
    

        Post_tick:
            for  event  in  map.all_current_map_events:
                event.remaining_duration -=  1.0
                if  event.remaining_duration <=  0.0:
                    map.all_current_map_events.remove(event)
    
    
    wait(minimum_wait_duration)

  
  

# Installation

  
1. It is **strongly** recommended that you use ``git clone --recursive`` to make sure that all dependencies are downloaded
2. Please run the relevant setup-script found in the ``.\Scripts\`` folder.

  

# How to use

  

You must initialise the Core in your application.

An example of how to do this can be found in the ``Example Engine``.

  

You must call ``Core::Initialise()``.

  

Additional parameters configuration is coming soon...

  

# Please Note

  

This entire project is still a major work in progress. Nothing is finished.

Work has been focused onto **[Project 43](https://github.com/marc-rene/Projekt_43)**
