#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

#define MIDI_RX_PIN 1  // UART1 RX ピン（DIN5のPin5から220Ω経由で接続）

// USB MIDIデバイスの作成
Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);

// MIDI受信バッファ
uint8_t midiMsg[3];
uint8_t inde = 0;
uint8_t expectedLength = 0;

void setup() {
  // TinyUSB 手動初期化（Pico系で必須）
  if (!TinyUSBDevice.isInitialized()) {
    TinyUSBDevice.begin();
  }

  Serial1.setRX(MIDI_RX_PIN);
  Serial1.begin(31250);  // MIDI DINのボーレート

  usb_midi.setStringDescriptor("pico");
  MIDI.begin(MIDI_CHANNEL_OMNI);  // 全チャンネル受信

  // USB再列挙（PCに認識させ直す）
  if (TinyUSBDevice.mounted()) {
    TinyUSBDevice.detach();
    delay(10);
    TinyUSBDevice.attach();
  }

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}

void loop() {

#ifdef TINYUSB_NEED_POLLING_TASK
  TinyUSBDevice.task();  // RP2040用
#endif

  // DINからのMIDIデータ読み取り
  if (Serial1.available()) {
    uint8_t byte = Serial1.read();

    if (byte & 0x80) { // ステータスバイト
      midiMsg[0] = byte;
      inde = 1;

      uint8_t status = byte & 0xF0;
      if (status == 0xC0 || status == 0xD0) {
        expectedLength = 2; // Program Change, Channel Pressure
      } else {
        expectedLength = 3;
      }
    } else if (inde > 0) {
      midiMsg[inde++] = byte;
    }

    if (inde == expectedLength) {
      uint8_t status = midiMsg[0] & 0xF0;
      uint8_t channel = (midiMsg[0] & 0x0F) + 1; // MIDIライブラリでは1〜16

      switch (status) {
        case 0x80: // Note Off
          MIDI.sendNoteOff(midiMsg[1], midiMsg[2], channel);
          break;
        case 0x90: // Note On
          MIDI.sendNoteOn(midiMsg[1], midiMsg[2], channel);
          break;
        case 0xA0: // Polyphonic Aftertouch
          MIDI.sendAfterTouch(midiMsg[2], midiMsg[1], channel);
          break;
        case 0xB0: // Control Change
          MIDI.sendControlChange(midiMsg[1], midiMsg[2], channel);
          break;
        case 0xC0: // Program Change
          MIDI.sendProgramChange(midiMsg[1], channel);
          break;
        case 0xE0: // Pitch Bend
          {
            int value = ((int)midiMsg[2] << 7) | midiMsg[1];
            MIDI.sendPitchBend(value - 8192, channel); // 中心を0に
          }
          break;
      }

      inde = 0;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // LED点滅で確認
    }
  }
}
