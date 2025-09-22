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
1. Clone this repository.
2. Open `main.ino` in Arduino IDE.
3. Select **M5Cardputer** as board and enable **USB CDC On Boot**.
4. Upload to the Cardputer via USB-C.

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

