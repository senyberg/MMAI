# MMAI

Purpose:

- Implement a reverb algorithm in C/C++.

What should the project do:
- Our program has to:
  - read wav files
  - play them in real time withe reverberation effect on it
  
The implementation should have controls for:
- a dry-wet
- early reflections
- a late reverberation size
- a spectral control (damping or equalizer)

Our program has to:
- have a CLI
- be runnable on at least Linux

Libraries that have to be used for sound file and audio I/O:
- libsndfile
- portaudio

Milestones

Week 15: project plan
- What have we researched about the reverbs?
- How will we implement a reverb?
- interface description
- base algorithm

How will we share the work between us?
- tasks
- responsability
- schedule

Week 16: first version of the reverberation
- working algorithm
- can be non real-time and/ or non cross-platform
- the executable has to be uploaded to GitHub's releases
- this for at least 3 major operating systems

Week 17: reverb with fine-tuned basic control parameters
- an executable with CLI controls for the reverbs
- almost final version of the DSP

Week 18: a real-time reverb with UI
- functions included:
- read wav-file
- trigger playback with UI or a hotkey
- save result to a file

Week 19: debugging meeting
Monday:
- last session
- listening test of the reverb
- submission of the project online one day before the course presentation
Thursday:
- address the rubric topics as best as possible
explain:
- Why were different algorithm blocks used?
Quality of the presentation:
- structure
- content
- team work
Who was responsible for what?
- collaborative programming organization
Expected content of the repository:

building instructions
signs of activity
comments
issues
task tracking
