# README.md
# RPL Security – Attack Simulation & Mitigation (Contiki-NG, Z1)

This project implements and evaluates security mechanisms for the RPL routing protocol used in IoT networks.
Multiple routing attacks are simulated on Z1 motes, and a custom security module is developed to detect and mitigate them.

------------------------------------------------------------
TECHNOLOGIES & TOOLS
------------------------------------------------------------
- Contiki-NG
- Cooja Network Simulator
- Z1 Motes
- RPL (IPv6 Routing Protocol for Low-Power Networks)
- C Programming

------------------------------------------------------------
PROJECT STRUCTURE
------------------------------------------------------------
build-z1/
│
├── normal/              → Standard RPL operation (baseline)
├── blackhole/           → Blackhole attack implementation
├── rank/                → Rank manipulation attack
├── selective-forward/   → Selective forwarding attack
├── sybil/               → Sybil attack
└── security-module/     → Proposed defense mechanism

Each folder contains:
- Makefile configured for Z1 motes
- Main source file (*.c)
- Generated firmware (*.z1)

------------------------------------------------------------
RUNNING ANY SCENARIO IN COOJA
------------------------------------------------------------
cd contiki-ng/tools/cooja
ant run        # start Cooja

Then:
1. Create a New Simulation
2. Add Z1 motes
3. Click "Load Firmware" and select the .z1 file from the chosen scenario
4. Run simulation and observe:
   - RPL DAG formation
   - Routing changes
   - Packet delivery ratio
   - Attack impact vs secured behavior

------------------------------------------------------------
IMPLEMENTED ATTACKS
------------------------------------------------------------
Normal Scenario          → Baseline RPL network without malicious nodes
Blackhole Attack         → Malicious node drops all packets
Rank Attack              → Fake low rank to attract traffic
Sybil Attack             → Node claims multiple identities
Selective Forwarding     → Drops selective packets to bias routing

------------------------------------------------------------
SECURITY MODULE (DEFENSE)
------------------------------------------------------------
The security mechanism is designed to:
- Detect abnormal rank changes
- Track forwarding behavior
- Identify identity duplication (Sybil)
- Improve network stability during attacks

------------------------------------------------------------
EXPECTED RESULTS
------------------------------------------------------------
- Reduced Packet Delivery Ratio (PDR) under attacks
- Increased latency and routing instability
- Improved stability with security module active

------------------------------------------------------------
OPTIONAL: MANUAL COMPILATION
------------------------------------------------------------
cd build-z1/<scenario-folder>
make clean TARGET=z1
make TARGET=z1

This generates the .z1 firmware file for Cooja.

------------------------------------------------------------
LICENSE
------------------------------------------------------------
This project is intended for academic and research purposes only.
Code may be reused for learning or scientific publications.

------------------------------------------------------------
AUTHOR
------------------------------------------------------------
Name:  Narimene
Field: Cybersecurity & IoT Security
Contact: your-email@example.com
