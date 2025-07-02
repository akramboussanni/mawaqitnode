# mawaqitnode (wip)
Embedded MAWAQIT app for microcontrollers.

## Features
*an issue is currently present where prayer times are not cached at all, and are loaded per minute. it will be fixed later :)
- Supports piezo speaker + OLED screen natively. These features are implemented in driver files to make it easy to add/modify for your own components.
- Config + modular code (disable piezo, oled, etc. before build)

## Installation
Project is built using PlatformIO. Modify `config.cpp.example` to fit your setup, then rename it to `config.cpp`.

## Developers
If you would like to modify this for your own components, the screen/sound drivers can be modified @ `lib/drivers/hardware`.

The project uses my own mawaqit scraper hosted @ `https://mrie.dev/`. You can modify the way to get mawaqit data @ `lib/drivers/api/mawaqit.cpp`.

For debugging, the tool prints on serial 115200 baud rate.