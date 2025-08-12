# Запрос

Platformio + VS Code
CONFIGURATION: https://docs.platformio.org/page/boards/raspberrypi/pico.html
PLATFORM: Raspberry Pi RP2040 (1.17.0+sha.651837d) > Raspberry Pi Pico
HARDWARE: RP2040 133MHz, 256KB RAM, 2MB Flash.

Напиши код на C++, чтобы плата RP2040 при подключении по USB определялась в Windows 10 как USB-MIDI-контроллер. Никаких действий от контроллера пока не требуется - только правильное определение. 

Для обмена по USB используй максимально популярную и изученную библиотеку или несколько библиотек. Код должен быть максимально простым. Количество внешних зависимостей - минимально возможным.

# Ответ

Вот минимальный и надёжный способ, как на Raspberry Pi Pico (RP2040) реализовать USB-MIDI-устройство, чтобы Windows 10 его сразу определяла — без лишних зависимостей и максимально просто.

---

## Библиотека и подход

Рекомендуется использовать **TinyUSB**, а точнее — **Adafruit TinyUSB Library** (Arduino-обёртка над TinyUSB). Эта библиотека широко применяема, поддерживает MIDI-устройствa и является популярной и изученной ([Reddit][1], [PlatformIO Registry][2]).

---

## Каркас C++ кода в PlatformIO + Arduino-фреймворк

### Пример `platformio.ini`

```ini
[env:pico]
platform = https://github.com/maxgerhardt/platform-raspberrypi.git
board = pico
framework = arduino
board_build.core = earlephilhower
lib_deps =
  adafruit/Adafruit TinyUSB Library
build_flags = -DUSE_TINYUSB
```

Здесь подключён core `earlephilhower` и включена TinyUSB-система ([PlatformIO Community][3], [GitHub][4]).

---

### Пример `src/main.cpp`

```cpp
#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

Adafruit_USBD_MIDI usbMIDI;

void setup() {
  usbMIDI.begin();
}

void loop() {
  // Ничего не отправляем/не принимаем — только чтобы Windows увидел устройство
}
```

Это максимально простой вариант: сразу после загрузки RP2040 будет объявлять себя USB-MIDI-устройством в системе.

---

## Советы на случай проблем

* Если Pico не определяется как MIDI-устройство на Windows, попробуйте собрать и загрузить проект через **Arduino IDE**: многие пользователи отмечают, что Midi-устройство корректно определяется там, тогда как при сборке через PlatformIO USB-стек иногда не инициализируется (TinyUSBDevice.mounted() остаётся false) ([GitHub][4]).
* Убедитесь, что TinyUSB действительно используется (флаг `USE_TINYUSB` корректен, ссылка на core верная).

---

## Резюме

| Компонент               | Что делать                                         |
| ----------------------- | -------------------------------------------------- |
| Библиотека              | Adafruit TinyUSB Library                           |
| Framework               | Arduino (core earlephilhower)                      |
| Конфиг (platformio.ini) | Как выше с `-DUSE_TINYUSB`, `lib_deps`             |
| Код                     | Инициализация `usbMIDI.begin()` — и всё            |
| Проверка                | Тест с Arduino IDE, если PlatformIO не срабатывает |

---

Если потребуется добавить какие-то функции (отправка MIDI-сообщений или реакция на них) — легко расширяется. Сейчас же дадим минимальный, работающий вариант, чтобы Windows 10 распознал устройство как USB-MIDI-контроллер.

Дай знать, если нужно — помогу подключить MIDI-task, обработку событий или отладку!

[1]: https://www.reddit.com/r/raspberrypipico/comments/1go4g7e/usb_midi_in_and_out_examples_with_tinyusb/?utm_source=chatgpt.com "USB MIDI in and out examples with tinyUSB : r/raspberrypipico"
[2]: https://registry.platformio.org/libraries/adafruit/Adafruit%20TinyUSB%20Library?utm_source=chatgpt.com "Adafruit TinyUSB Library for Arduino - PlatformIO Registry"
[3]: https://community.platformio.org/t/problem-with-rasberry-pi-pico-and-tinyusb-for-usbmidi/26815?utm_source=chatgpt.com "Problem with Rasberry Pi Pico and TinyUSB for usbMIDI"
[4]: https://github.com/earlephilhower/arduino-pico/issues/501?utm_source=chatgpt.com "USB Device not detected by host when using platformIO #501 - GitHub"

# Источник
https://chatgpt.com/share/689b8e9b-0e10-800e-b841-c2cbb3c48143
