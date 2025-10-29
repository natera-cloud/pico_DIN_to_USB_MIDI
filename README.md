# pico_DIN_to_USB_MIDI

A firmware to convert traditional 5-pin DIN MIDI input to USB MIDI using a Raspberry Pi Pico.

Raspberry Pi Picoを使用して、従来の5ピンDIN MIDI入力をUSB MIDIに変換するファームウェアです。

Overview / 概要
This project allows you to connect devices with a DIN-5 MIDI output, such as MIDI keyboards and synthesizers, to a PC, Mac, or smartphone with a single USB cable. It runs on a Raspberry Pi Pico and is recognized as a class-compliant USB-MIDI device without any special drivers.

このプロジェクトは、MIDIキーボードやシンセサイザーなどのDIN-5 MIDI出力を持つ機器を、USBケーブル1本でPCやMac、スマートフォンに接続できるようにするものです。Raspberry Pi Pico上で動作し、特別なドライバなしでクラスコンプライアントなUSB-MIDIデバイスとして認識されます。

Features / 特徴
Plug and Play: Recognized as a MIDI device just by connecting it to your PC.

Low Latency: Achieves low-latency conversion by leveraging the performance of the Raspberry Pi Pico.

Simple Circuitry: Can be assembled with minimal components.

High Compatibility: Works with major DAWs (Cubase, Logic Pro, Ableton Live, etc.) on Windows, macOS, Linux, iOS, and Android.

プラグアンドプレイ: PCに接続するだけでMIDIデバイスとして認識されます。

低遅延: Raspberry Pi Picoの性能を活かし、低レイテンシーな変換を実現します。

シンプルな回路: 最小限の部品で組み立て可能です。

高い互換性: Windows, macOS, Linux, iOS, Androidの主要なDAW（Cubase, Logic Pro, Ableton Liveなど）で動作します。

What You'll Need (Hardware) / 必要なもの
Raspberry Pi Pico or Pico W

DIN-5 MIDI Connector (Female)

Resistor: 220Ω × 1

Breadboard and jumper wires

Raspberry Pi Pico または Pico W

DIN-5 MIDIコネクタ (メス)

抵抗: 220Ω × 1

ブレッドボードとジャンパーワイヤー

Wiring / 回路
The circuit is very simple. 非常にシンプルな回路で構成されています。

MIDI DIN-5 Connector         Raspberry Pi Pico
--------------------         -----------------
Pin 5  ---[ 220Ω ]---        GP1 (UART1 RX)
Pin 2  -----------------        GND
Pin 4  (Not Connected)
Note: This is a simplified circuit that does not use an optocoupler as recommended by the official MIDI specification. However, it works fine with many MIDI devices.

注意: これは公式のMIDI規格で推奨されているフォトカプラを使用した回路ではありませんが、多くのMIDI機器で問題なく動作する簡略化された回路です。

Installation / インストール方法
1. Easy Way (Using the .uf2 file) / 簡単な方法 (.uf2ファイルを使用)
This is the easiest method and does not require you to compile the program yourself.

プログラムを自分でコンパイルする必要がない、最も簡単な方法です。

Press and hold the BOOTSEL button on your Raspberry Pi Pico, then connect it to your PC with a USB cable. Raspberry Pi Picoの BOOTSEL ボタンを押したまま、PCにUSBケーブルで接続します。

It will be recognized as a storage device named RPI-RP2. PCに RPI-RP2 という名前のストレージとして認識されます。

Download the pico_DIN_to_USB_MIDI.uf2 file from the Releases page. リリースページから pico_DIN_to_USB_MIDI.uf2 ファイルをダウンロードします。

Drag and drop the downloaded .uf2 file onto the RPI-RP2 drive. ダウンロードした .uf2 ファイルを RPI-RP2 ドライブにドラッグ＆ドロップします。

The Pico will automatically reboot once the copy is complete. You are all set! コピーが完了するとPicoが自動的に再起動し、準備完了です。

2. Building from Source (Arduino IDE) / ソースからビルドする方法 (Arduino IDE)
If you want to customize the code, you can build it from the source code using the following steps.

ご自身でコードをカスタマイズしたい場合は、以下の手順でソースコードからビルドできます。

Set up Arduino IDE

Install the Arduino IDE.

Open File > Preferences and add the following URL to "Additional Board Manager URLs":

https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
Open Tools > Board > Boards Manager, search for "rp2040", and install Raspberry Pi Pico/RP2040.

Install Libraries

Open Tools > Manage Libraries... and install the following libraries:

Adafruit TinyUSB Library

MIDI Library by Forty Seven Effects

Upload

Open the source code (pico_DIN_to_USB_MIDI.ino) from this repository in the Arduino IDE.

Select Raspberry Pi Pico from Tools > Board.

Connect your Pico to the PC, select the correct serial port, and press the "Upload" button.

Usage / 使い方
Wire the circuit as shown in the diagram. 上記の回路図通りに配線します。

Connect the MIDI OUT from your MIDI keyboard or other device to the circuit. プログラムを書き込んだPicoに、MIDIキーボードなどのMIDI OUTを接続します。

Connect the Pico to your PC via USB. PicoをPCにUSBで接続します。

Launch your DAW software. A new MIDI input device named Keytar.1 should appear. Select it, and you're ready to go. DAWソフトウェアを起動すると、Keytar.1 という名前の新しいMIDI入力デバイスが表示されます。これを選択すればすぐに使用できます。

License / ライセンス
This project is released under the MIT License. See the LICENSE file for details.

このプロジェクトは MITライセンス の下で公開されています。詳細は LICENSE ファイルをご覧ください。

Acknowledgements / 謝辞
This project was made possible by the following wonderful open-source projects:

このプロジェクトは、以下の素晴らしいオープンソースプロジェクトによって実現しました。

earlephilhower/arduino-pico

Adafruit TinyUSB Library

Arduino MIDI Library
