# Cardputer Barcode Wedge

A simple **barcode scanner simulator** for the [M5Stack Cardputer](https://shop.m5stack.com/products/m5stack-cardputer-kit-w-m5stamps3) (ESP32-S3).  
It turns your Cardputer into a **USB HID keyboard** that "types" barcode numbers into any connected host (PC, POS system, etc).

---

## ✨ Features

- **Default value**: starts with a pre-configured code (`827212654851`).
- **Type numbers** directly on the Cardputer's keyboard to change the current value.
- **Enter**: sends the current value as keyboard input.
- **Backspace**: deletes the last digit.
- **Hold Backspace** (0.7s): clears the entire value.
- **Adaptive display**: font size shrinks automatically for longer numbers.
- **Feedback messages**:  
  - ✅ *Sent!* (in green) after sending  
  - ❌ *Cleared* (in red) after clearing
- **Audio feedback**: short beep on send.

---

## 🖥️ How it works

The Cardputer emulates a USB keyboard using the ESP32-S3 native USB HID.  
When you press **Enter**, it sends the current number as if typed on a normal barcode scanner.

This allows you to test barcode input fields in POS software, ERP systems, or any app that accepts keyboard input.

---

## ⌨️ Controls

| Key             | Action                       |
|-----------------|------------------------------|
| `0–9`           | Append digit to current value|
| `Enter`         | Send current value           |
| `Backspace`     | Delete last digit            |
| `Hold Backspace`| Clear entire value           |

---

## 🚀 Getting Started

### Requirements
- **M5Stack Cardputer (StampS3 / ESP32-S3)**
- Arduino IDE with:
  - **ESP32 Board Support** (≥ v2.0.7)
  - Libraries: [M5Cardputer](https://github.com/m5stack/M5Cardputer), [M5Unified](https://github.com/m5stack/M5Unified), [M5GFX](https://github.com/m5stack/M5GFX)

### Upload

#### Option 1: Arduino IDE
1. Clone this repository.
2. Open `Cardputer-Barcode-Wedge.ino` in Arduino IDE.
3. Select **M5Cardputer** as board and enable **USB CDC On Boot**.
4. Upload to the Cardputer via USB-C.

#### Option 2: Arduino CLI (Command Line)
1. Install [Arduino CLI](https://arduino.github.io/arduino-cli/).
2. Install ESP32 board support:
   ```bash
   arduino-cli core install esp32:esp32
   ```
3. Install required libraries:
   ```bash
   arduino-cli lib install "M5Cardputer"
   arduino-cli lib install "M5Unified"
   arduino-cli lib install "M5GFX"
   ```
4. Use the provided makefile for easy compilation and upload:
   ```bash
   # Compile the project
   make compile
   
   # Upload to device (adjust PORT in makefile if needed)
   make upload
   
   # Compile and upload in one command
   make all
   
   # Open serial monitor
   make monitor
   
   # Clean build files
   make clean
   
   # Show available commands
   make help
   ```

   **Note**: Update the `PORT` variable in the makefile to match your device's serial port (e.g., `/dev/cu.usbmodem11301` on macOS, `COM3` on Windows).

#### Makefile Configuration
The project includes a makefile with the following configurable variables:
- `PROJECT_NAME`: Project name (Cardputer-Barcode-Wedge)
- `FQBN`: Fully Qualified Board Name (esp32:esp32:m5stack_cardputer)
- `PORT`: Serial port for uploads (adjust for your system)
- `BAUD`: Serial monitor baud rate (115200)
- `SRC_DIR`: Source directory (current directory)

Available makefile targets:
- `all`: Compile and upload in sequence
- `compile`: Compile the Arduino sketch
- `upload`: Upload compiled binary to device
- `monitor`: Open serial monitor
- `clean`: Remove build artifacts
- `help`: Show available commands

---

## 📷 Preview

```
USB Barcode Wedge
Value
827212654851
Sent!
```

*(Display adapts font size depending on the number length.)*

---

## 🔧 Customization

- Change the **default code** by editing:
  ```cpp
  const String defaultCode = "827212654851";
  ```

* Adjust the **long-press clear time**:

  ```cpp
  const uint32_t BACKSPACE_CLEAR_MS = 700; // milliseconds
  ```

---

## 🛠️ Future Ideas

* Support for symbols like `-` and `.`
* Bluetooth HID mode (wireless barcode wedge)
* Save/load last value to NVS (persistent storage)

---

## 📄 License

MIT License. See [LICENSE](LICENSE) for details.

