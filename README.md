# VehicleDataProcessor

A automotive project that simulates vehicle and ADAS messages,
processes them, and will eventually display the resulting state on a dashboard.

## Architecture

- `simulation/`: generates simulated vehicle messages.
- `processing/`: validates messages and maintains the latest vehicle state.
- `include/common/`: shared message definitions.
- `config/`: message and simulation configuration.
- `app/`: application entry point.
- `dashboard/`: reserved for a future Qt dashboard.
- `tests/`: reserved for automated tests.

The simulator and processor are deliberately independent of the future dashboard.
Messages are represented as JSON so that other transports or data sources can be
added later without coupling them to the UI.

## Requirements

- CMake 3.21 or newer
- C++17 compiler
- Qt 6 Core

## Build (Windows / Visual Studio)

```powershell
cmake -S . -B build
cmake --build build --config Debug
.\build\Debug\vehicle_data_processor.exe
```

For a single-configuration generator, the executable may be under `build/`
instead of `build/Debug/`.

## First milestone

The initial application periodically generates:
- vehicle status messages
- ADAS function status messages

The processor parses these messages and prints the latest processed state.

## Planned milestones

1. Add configuration-driven message definitions and emission rates.
2. Add message validation, timestamps, sequence numbers and error handling.
3. Add detailed ADAS signals (TTC, object distance, lane departure, etc.).
4. Add unit tests.
5. Add a Qt dashboard with separate panels for vehicle status and ADAS functions.
6. Add scenarios such as urban driving, highway driving and parking.
