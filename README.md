# mawaqitnode (wip)
Embedded MAWAQIT app for microcontrollers. Automatically get the most accurate prayer times for your region and get a little alarm for it.

## Example
The below example uses both OLED screen + passive speaker.
![esp32 example](static/setup.png)

## Setup
### 1. Setup the circuit
The circuit requires minimally an ESP32. You can add:
- a passive buzzer, which should be on any GPIO pin.
- an OLED screen, which should have SCL + SDA on 2 GPIO pins.

### 2. Download the repo using git
`git clone https://github.com/akramboussanni/mawaqitnode`

### 3. Setup the project
Open the new folder. Rename the `config.cpp.example` (in the `src` folder) file to `config.cpp` and change your settings to fit your needs.

If you did not add an OLED or passive buzzer, edit the `main.cpp` (in the `src` folder) and remove the `initDisplay()` (line 24) and `initSound()` (line 25) respectively.

### 4. Build the project
If you did not do so already, install PlatformIO (preferably with Visual Studio Code). Then, open the folder and upload it to your ESP32 using PlatformIO. It should not work properly.

## Features
*an issue is currently present where prayer times are not cached at all, and are loaded per minute. it will be fixed later :)
- Supports passive speaker + OLED screen natively. These features are implemented in driver files to make it easy to add/modify for your own components.
- Config + modular code (disable passive speaker, oled, etc before build)
- Alarm system that notifies you when it's prayer time!

## Developers
If you would like to modify this for your own components, the screen/sound drivers can be modified @ `lib/drivers/hardware`.

The project uses my own mawaqit scraper hosted @ `https://mrie.dev/`. You can modify the way to get mawaqit data @ `lib/drivers/api/mawaqit.cpp`.

For debugging, the tool prints on serial 115200 baud rate.