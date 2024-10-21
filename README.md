# PTMS (Parkinson Tremor Monitoring System)

This repository contains code, circuit diagrams, references, and other related resources for the project.

## Contents
- [Synopsis](https://github.com/Azure9733/parkinson-tremor-monitoring-system-PTMS-/tree/main#synopsis)
- [Wiring Instructions](https://github.com/Azure9733/parkinson-tremor-monitoring-system-PTMS-/tree/main?tab=readme-ov-file#wiring-instructions) 
- [EMG sensor Codes](emg_codes)
- [Testing scripts for microSD card functionality](SD_card_testing)
- [Illustrations](Illustrations)
- [Acknowledgements](https://github.com/Azure9733/parkinson-tremor-monitoring-system-PTMS?tab=readme-ov-file#acknowledgements)

## Synopsis

The PTMS project aims to develop a smart wearable device designed to detect tremors associated with Parkinson's Disease. By continuously monitoring the wearer's movements and analyzing the data, it can predict and alert the user about an impending tremor episode. This early warning system can help individuals manage their condition more effectively.

This research project is under the Department of Instrumentation and Control Engineering (ICE) of MIT Manipal. (Due to confidentiality, part of the project is not made public on this repository)

### Technical Overview

- **Microcontroller:** Arduino Nano
- **Sensor:** Upside Downlabs EXG Pill

The Arduino Nano collects data from the EMG sensor (EXG Pill). The readings can be viewed on the Serial Monitor of the Arduino IDE, and the data can be visualized using the Serial Plotter. The relevant code for this functionality is located in the following folder: [emg_codes](https://github.com/Azure9733/parkinson-tremor-monitoring-system-PTMS-/tree/main/emg_codes).

Additionally, a microSD card module is interfaced with the Arduino Nano to store sensor data. Code for testing the microSD card module's integration with the microcontroller can be found in the following folder: [SD_card_testing](SD_card_testing).
These codes can be used to:
- verify if the connections are correct
- check if the microSD card is functioning properly or is of compatible file system (FAT32 in this case)
- create a test file confirming that data can be written successfully

## Wiring Instructions

### Arduino Nano to EXG Pill and SD Card Module

#### SD Card Module:
- **SS(Slave Select)/CS(Chip Select)**: Connect to any digital pin except 11, 12, 13 (e.g., D4)
- **SCK**: D13
- **MOSI**: D11
- **MISO**: D12
- **Vcc**: +5V
- **GND**: GND

#### EXG Pill:
- **Vcc**: 5V
- **GND**: GND
- **OUT**: A0

### ESP32 38pin to EXG Pill and SD Card Module

#### SD Card Module:
- **SS(Slave Select)/CS(Chip Select)**: Connect to any digital pin except 11, 12, 13 (e.g., D4) P5
- **SCK**: P18
- **MOSI**: P23
- **MISO**: P19
- **Vcc**: +5V
- **GND**: GND

#### EXG Pill:
- **Vcc**: 5V
- **GND**: GND
- **OUT**: P35

## Acknowledgements
- Thanks to the Department of Instrumentation and Control Engineering (ICE) of MIT Manipal for providing resources and equipment needed for this project.
- Codes for EXG PILL sensor is derived from [Upside Downlabs EXG PILL Repository](https://github.com/upsidedownlabs/BioAmp-EXG-Pill)
