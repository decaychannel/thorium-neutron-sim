# Thorium Neutron Simulation

Geant4 simulation for studying thermal neutron interactions with Th-232 (Thorium) fuel rod.

## Features

- **Th-232 Fuel Rod**: Cylindrical thorium fuel rod (2cm diameter, 20cm length)
- **Thermal Neutron Source**: 0.025 eV neutrons
- **Interaction Logging**: MT-safe logging for fission and capture events
- **HP Physics**: FTFP_BERT_HP for accurate low-energy neutron transport

## Project Structure

```
thorium-neutron-sim/
├── CMakeLists.txt
├── main.cc
├── include/
│   ├── DetectorConstruction.hh
│   ├── Materials.hh
│   ├── ActionInitialization.hh
│   ├── PrimaryGeneratorAction.hh
│   └── SteppingAction.hh
├── src/
│   ├── DetectorConstruction.cc
│   ├── Materials.cc
│   ├── ActionInitialization.cc
│   ├── PrimaryGeneratorAction.cc
│   └── SteppingAction.cc
└── macros/
    ├── vis.mac
    └── run.mac
```

## Materials

- **Th-232**: Pure Thorium-232 (fertile material, ρ = 11.7 g/cm³)
- **U-235**: Enriched Uranium (93% U-235, available for comparison)

## Building

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

## Running

### Interactive Mode (Visualization)
```bash
./thorium_sim
```

### Batch Mode
```bash
./thorium_sim macros/run.mac > output.log
```

## Neutron Interactions

The simulation logs:
- **CAPTURE**: Neutron capture events → Th-232 + n → Th-233 + γ
- **FISSION**: Fission events (rare for Th-232)

## Requirements

- Geant4 11.x with HP data libraries
- CMake 3.16+
- C++17 compiler
