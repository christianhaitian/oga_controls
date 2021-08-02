# AnberPorts-Joystick
Emulated keyboard / mouse / joystick for the RGB10/OGA 1.1 (BE), RG351 P/M/V, RK2020/OGA 1.0, OGS, and the Chi

# How to build
## Prereqs
libevdev-dev

### Build
```
git clone https://github.com/christianhaitian/oga_controls.git -b universal
cd oga_controls
make all
```
# Howto
Launch with `sudo ./oga_controls your-program your-rk3326-device`.  Ex. `sudo ./oga_controls bgdi oga`

Allowed rk3326-device values = anbernic, chi, oga, ogs, rk2020

# /etc/udev/rules.d
```
SUBSYSTEM=="misc", KERNEL=="uinput", MODE="0660", GROUP="uinput"
```

## Support the project

[<img src="https://raw.githubusercontent.com/krishenriksen/AnberPorts/master/sponsor.png" width="200"/>](https://github.com/sponsors/krishenriksen)

[Become a sponsor to Kris Henriksen](https://github.com/sponsors/krishenriksen)
