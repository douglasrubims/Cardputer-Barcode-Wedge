#include "M5Cardputer.h"
#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

const String defaultCode = "827212654851";
String currentCode = defaultCode;

uint32_t lastEnterMs = 0;
const uint32_t ENTER_DEBOUNCE_MS = 250;

void beepOK() { M5Cardputer.Speaker.tone(1000, 60); }

void drawFitCenter(const String& text, int y, int maxSize, int minSize, uint16_t color, int padding = 8) {
  int cx = M5Cardputer.Display.width() / 2;
  int avail = M5Cardputer.Display.width() - padding * 2;
  int size = maxSize;
  while (size >= minSize) {
    M5Cardputer.Display.setTextSize(size);
    int w = M5Cardputer.Display.textWidth(text);
    if (w <= avail) break;
    size--;
  }
  if (size < minSize) size = minSize;
  M5Cardputer.Display.setTextDatum(top_center);
  M5Cardputer.Display.setTextColor(color);
  M5Cardputer.Display.drawString(text, cx, y);
}

void drawUI(const String& hint = "", uint16_t hintColor = 0x07E0) {
  M5Cardputer.Display.clear();
  const int cx = M5Cardputer.Display.width() / 2;
  const int bottom = M5Cardputer.Display.height();
  M5Cardputer.Display.setTextDatum(top_center);
  M5Cardputer.Display.setTextFont(&fonts::Font0);
  M5Cardputer.Display.setTextColor(0x07E0);
  M5Cardputer.Display.setTextSize(2);
  M5Cardputer.Display.drawString("USB Barcode Wedge", cx, 6);
  M5Cardputer.Display.setTextColor(0xFFFF);
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.drawString("Value", cx, 28);
  int valueY = 46;
  drawFitCenter(currentCode.length() ? currentCode : "(empty)", valueY, 4, 1, 0xFFE0, 8);
  if (!hint.isEmpty()) {
    M5Cardputer.Display.setTextDatum(top_center);
    M5Cardputer.Display.setTextColor(hintColor);
    M5Cardputer.Display.setTextSize(2);
    M5Cardputer.Display.drawString(hint, cx, valueY + 40);
  }
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.setTextColor(0xC67F);
  M5Cardputer.Display.drawString("Type 0-9  |  Enter=send", cx, bottom - 26);
  M5Cardputer.Display.drawString("Backspace=del  |  Hold Backspace=clear", cx, bottom - 14);
}

inline char hidDigit(uint8_t hid, bool numpad) {
  if (!numpad) {
    if (hid >= 0x1E && hid <= 0x26) return char('1' + (hid - 0x1E));
    if (hid == 0x27) return '0';
    return 0;
  } else {
    if (hid >= 0x59 && hid <= 0x61) return char('1' + (hid - 0x59));
    if (hid == 0x62) return '0';
    return 0;
  }
}

void sendCode(const String &code) {
  if (code.isEmpty()) return;
  Keyboard.print(code);
  beepOK();
  drawUI("Sent!", 0x07E0);
}

bool backspaceDown = false;
bool backspaceCleared = false;
uint32_t backspaceDownMs = 0;
const uint32_t BACKSPACE_CLEAR_MS = 700;

void setup() {
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Speaker.begin();
  M5Cardputer.Speaker.setVolume(200);
  Keyboard.begin();
  USB.begin();
  Serial.begin(115200);
  drawUI();
}

void loop() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isChange()) {
    if (M5Cardputer.Keyboard.isPressed()) {
      Keyboard_Class::KeysState ks = M5Cardputer.Keyboard.keysState();
      bool pressedEnter = false;
      bool appendedDigit = false;
      bool backspaceNow = false;
      for (auto hid : ks.hid_keys) {
        if (hid == 0x28) pressedEnter = true;
        else if (hid == 0x2A) backspaceNow = true;
        char d = hidDigit(hid, false);
        if (d) { currentCode += d; appendedDigit = true; continue; }
        d = hidDigit(hid, true);
        if (d) { currentCode += d; appendedDigit = true; continue; }
      }
      if (backspaceNow && !backspaceDown) {
        backspaceDown = true;
        backspaceCleared = false;
        backspaceDownMs = millis();
        if (currentCode.length()) currentCode.remove(currentCode.length() - 1);
        drawUI();
      }
      if (pressedEnter) {
        uint32_t now = millis();
        if (now - lastEnterMs > ENTER_DEBOUNCE_MS) {
          lastEnterMs = now;
          sendCode(currentCode);
        }
      } else if (appendedDigit) {
        drawUI();
      }
    } else {
      if (backspaceDown) {
        backspaceDown = false;
        backspaceCleared = false;
      }
    }
  }
  if (backspaceDown && !backspaceCleared) {
    uint32_t held = millis() - backspaceDownMs;
    if (held >= BACKSPACE_CLEAR_MS) {
      currentCode = "";
      backspaceCleared = true;
      drawUI("Cleared", 0xF800);
    }
  }
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 's' || c == 'S') sendCode(currentCode);
  }
}

