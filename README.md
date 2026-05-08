# SUMO + OMNeT++ + Veins Simulation Project

This project demonstrates vehicular network simulation using **SUMO**, **OMNeT++**, and the **Veins Framework**.  
The simulation integrates real-time traffic mobility with wireless network communication for VANET (Vehicular Ad Hoc Network) simulations.

---

# Technologies Used

- SUMO (Simulation of Urban MObility)
- OMNeT++
- Veins Framework
- Python

---

# Prerequisites

Before running the project, install the following software.

---

# 1. Install OMNeT++

Download OMNeT++ from the official website:

https://omnetpp.org/download/

Install OMNeT++ and complete the setup process.

---

# 2. Install SUMO

Download SUMO from:

https://sumo.dlr.de/docs/Downloads.php

After installation, verify the SUMO executable path.

Example:

```bash
C:\Program Files (x86)\Eclipse\Sumo\bin\sumo.exe
```

---

# 3. Install Veins Framework

Clone or download the Veins framework from:

https://github.com/sommer/veins

This project uses:

```bash
veins-5.3.1
```

---

# Project Setup

## Step 1: Open OMNeT++

Launch OMNeT++ IDE.

---

## Step 2: Import the Project

Import:
- Veins framework
- Your simulation project

into the OMNeT++ workspace.

---

## Step 3: Clean and Build the Project

Before running the simulation:

1. Right click on the project
2. Click:
   - Clean Project
3. Then click:
   - Build Project

This compiles all required files and dependencies.

---

# Running the Simulation

Open the **OMNeT++ terminal** and execute the following command:

```bash
cd veins-5.3.1/veins-veins-5.3.1 && python ./sumo-launchd.py -vv -c "C:\Program Files (x86)\Eclipse\Sumo\bin\sumo.exe"
```

---

# Start the Simulation

After running the command:

1. Open the simulation configuration in OMNeT++
2. Click the **Run** button
3. SUMO GUI and OMNeT++ will connect automatically
4. The vehicular simulation will start

You will now be able to visualize:
- Vehicle movement
- Traffic flow
- Communication between vehicles
- Network events in OMNeT++

---

# Simulation Architecture

```text
+-------------------+
|       SUMO        |
| Traffic Mobility  |
+-------------------+
          ^
          |
          v
+-------------------+
|       Veins       |
| Coupling Interface|
+-------------------+
          ^
          |
          v
+-------------------+
|      OMNeT++      |
| Network Simulator |
+-------------------+
```

---

# Features

- Vehicular traffic simulation
- Vehicle-to-Vehicle (V2V) communication
- Real-time traffic visualization
- Integrated mobility and network simulation
- VANET simulation support

---

# Important Notes

- Ensure Python is installed and added to PATH
- Verify the SUMO executable path before running the command
- Always perform:
  - Clean Project
  - Build Project

before starting the simulation.

- OMNeT++ and Veins versions should be compatible.

---

# References

## OMNeT++

https://omnetpp.org/

## SUMO

https://sumo.dlr.de/docs/

## Veins

https://veins.car2x.org/

---

# Author

Developed using SUMO, OMNeT++, and Veins Framework for vehicular network simulation research and experimentation.
