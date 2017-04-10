# MMAI 2017: Course project

- The purpose of the course project is to implement a reverb algorithm in **C/C++** language. 

- The program should be able to read **.wav** files and play them in real time with the reverberation effect applied. 
  
- The implementation should have controls at least for:
  - dry-wet
  - early reflections
  - late reverberation size
  - spectral control (like damping or equalizer). 

The program should have a **Command Line Interface (CLI)** and should be runnable at least on **Linux**. 

For sound file and audio I/O use using *libsndfile* and *portaudio* libraries.

# Milestones

Week 15: Project plan
- What have you researched about reverbs yourself?
###### Checked all the lecture slides and googled for some basic reverb code examples. Andreas has prior experience with different reverberation from years of playing around with different guitar reverb pedals and multi effects pedals. Other team members are unfamiliar with reverb, but are excited to learn more about it.
- How are you going to implement a reverb? (interface description, base algorithm, etc.)
###### Initial plan is to implement the *Schroeder Reverbs* - https://valhalladsp.com/2009/05/30/schroeder-reverbs-the-forgotten-algorithm/.
###### The interface - or the GUI - will be created in *Qt* or *Visual Studio*.
- How will the group work be organized? 
  - [Tasks, responsibility, schedule](https://github.com/senyberg/MMAI/blob/master/TasksResponsSchedule.md)
