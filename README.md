# TUC-ECE-Thesis [![CC BY-NC 4.0][cc-by-nc-shield]][cc-by-nc] ![GitHub repo size](https://img.shields.io/github/repo-size/CSpyridakis/TUC-ECE-Thesis) [![wakatime](https://wakatime.com/badge/user/1d822293-dbdb-48db-9b57-0fc9df520d2c/project/1d62f158-1b82-4fa4-8a62-7bbf2c6b27d1.svg)](https://wakatime.com/badge/user/1d822293-dbdb-48db-9b57-0fc9df520d2c/project/1d62f158-1b82-4fa4-8a62-7bbf2c6b27d1)

# Thesis title
Design and implementation of a low cost embedded system for localization of drones flying in swarms

# Abstract
The requirement for object localization has existed for thousands of years, and over the past 70 years, we have even taken advantage of digital methods to achieve it.
The following thesis focuses on the attempt to combine the above idea with the most advanced technology of UAVs and implement the first generation of a low-cost system for estimating the position of an object with the help of a swarm of drones.
The prosecution of prior art research has distinguished the number of different methods already used in the literature to solve similar problems.
In such methods, we often use Radio Frequencies - like GPS, WiFi, UWB, cellular, and Lora networks -, sound waves, or vision-related ones by operating cameras and LiDAR.
It was also essential to understand the mathematical background behind these approaches and determine their complexities since the selection of the hardware for this kind of embedded systems often relies on the operating principles and resources that each one needs.
These are related to how we calculate distances and angles by applying RSSI, TDoA, AoA, or even Stereo Vision techniques, and how we utilize this information in algorithms like Triangulation, Trilateration, or Hyperbolic Positioning to achieve localization.
By comprehending each approach necessity, this work presents a two-tier system, in which worker nodes estimate the distance between the object of interest and camera through monocular vision and structure from reference. Then, through the principle of Multilateration, we finally achieve estimating its position by the system orchestrator node, called master.
We first performed experiments in both indoor and outdoor scenarios from single worker nodes. Then, we used the data taken from the above procedure to simulate the operation of the entire proposed system. To complete this work, we also introduce a mechanism to estimate the ID of the detected object through frequency analysis of flashing led.

# System
## Single node view
![single-drone-view](Images/Experiments-Results/node-view.png)
## Multiple nodes view
![multiple-drones-view](Images/Experiments-Results/multiple-nodes/combined/myimage.gif)
## Position Estimations
![position-estimations](Images/Experiments-Results/nodes-pos-with-est-angle.png)
## Proposed System
![proposed-system](Images/Design-Implementation/thesis-system.jpg)


# Documents
* Thesis proposal is available [here](doc/Thesis%20Proposal%20-%20Design%20and%20Implementation%20of%20a%20Low%20Cost%20Embedded%20System%20for%20Localization%20of%20Drones%20Flying%20in%20Swarms.pdf).
* Init version of technical specification document is available [here](doc/drone-mocap-technical-specs.pdf).
* Complete Thesis document is available [here](https://doi.org/10.26233/heallink.tuc.91531) and [here](doc/Design%20and%20Implementation%20of%20a%20Low%20Cost%20Embedded%20System%20for%20Localization%20of%20Drones%20Flying%20in%20Swarms.pdf).
* Code for this thesis implementation is available [here](https://github.com/CSpyridakis/ros_drone_swarm_mocap).
* Video from the presentation is available [here](https://youtu.be/7qfMd4-FWC4).

# Bibliographic Citation
Christos Spyridakis, "Design and implementation of a low cost embedded system for localization of drones flying in swarms", Diploma Work, School of Electrical and Computer Engineering, Technical University of Crete, Chania, Greece, 2022 https://doi.org/10.26233/heallink.tuc.91531


# License
[![CC BY-NC-SA 4.0][cc-by-nc-image]][cc-by-nc]

[cc-by-nc]: http://creativecommons.org/licenses/by-nc/4.0/
[cc-by-nc-image]: https://licensebuttons.net/l/by-nc/4.0/88x31.png
[cc-by-nc-shield]: https://img.shields.io/badge/License-CC%20BY--NC%204.0-lightgrey.svg
