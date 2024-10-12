# PTMS (Parkinson Tremor Monitoring System)

This repository contains code, circuit diagrams, references, and other related resources for the project.

## Synopsis

The PTMS project aims to develop a smart wearable device designed to detect tremors associated with Parkinson's Disease. By continuously monitoring the wearer's movements and analyzing the data, it can predict and alert the user about an impending tremor episode. This early warning system can help individuals manage their condition more effectively.

### Technical Overview

- **Microcontroller:** Arduino Nano
- **Sensor:** EXG Pill

The Arduino Nano collects data from the EMG sensor (EXG Pill). The readings can be viewed on the Serial Monitor of the Arduino IDE, and the data can be visualized using the Serial Plotter. The relevant code for this functionality is located in the following folder: [emg_codes](https://github.com/Azure9733/parkinson-tremor-monitoring-system-PTMS-/tree/main/emg_codes).

Additionally, a microSD card module is interfaced with the Arduino Nano to store sensor data. Code for testing the microSD card module's integration with the microcontroller can be found in the following folder: [SD_card_testing](SD_card_testing).
These codes can be used to:
- verify if the connections are correct
- check if the microSD card is functioning properly or is of compatible file system (FAT32 in this case)
- create a test file confirming that data can be written successfully

## Contents

- [Code](emg_codes/EMG_data_aqi_5.ino) for storing data
- Circuit diagrams
- Testing scripts for microSD card functionality
- Reference materials
