# Hearth Peltier Brew Rig

Controller firmware, thermal hardware and configuration profiles for the
Peltier-heated brew rig.

The controller runs a current-limited PID loop on a MOSFET bank. The cold plate
holds six Peltier modules in two strings; the firmware derates the setpoint
when the plate differential exceeds 32 K.

## Contents

- `controller/brew_controller.ino` — control loop and display menu
- `controller/pid.h` — PID helper used by the controller
- `hardware/thermal_plate.kicad_sch` — cold plate and module wiring
- `config/profile.yaml` — mash and sparge profiles
- `docs/wiring.md` — mains wiring and safety notes
