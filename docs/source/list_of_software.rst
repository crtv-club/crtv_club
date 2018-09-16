Список ПО
=========

Intel 8051
----------

Для работы с МК на основе 8051 вам понадобятся:

- IDE (среда разработки) - `Keil C51 <https://www.keil.com/demo/eval/c51.htm>`_
- драйвер на программатор - `Zadig <http://zadig.akeo.ie/>`_ (там нужно установить libusb-win32)
- утилита для прошивки - `ProgISP <http://exploreembedded.com/wiki/AT89S_Series_8051_programmer>`_
- open-source эмулятор - `EdSim51 <https://www.edsim51.com/>`_
- боле навороченный эмулятор - Proteus (платный)

AVR (Arduino и прочие)
----------------------

Для работы с МК на основе AVR вам понадобятся:

- IDE (среда разработки) - `Atmel Studio <http://www.microchip.com/development-tools/atmel-studio-7>`_
- драйвер на программатор - `Zadig <http://zadig.akeo.ie/>`_
- утилита для прошивки - `AVRDUDE <http://www.electrodragon.com/w/ProgISP>`_ с различными `GUI <http://blog.zakkemble.co.uk/avrdudess-a-gui-for-avrdude/>`_

Raspberry
---------

Для работы с Raspberry вам понадобятся:

- разум

В общем-то, этого хватит. А дальше, в зависимости от подхода:

- `PyCharm Professional <https://www.jetbrains.com/student/>`_ - IDE для python.
  Можно писать код на компе, а запускать и отлаживать на Raspberry Pi
- `QtCreator <https://www1.qt.io/download-open-source/#section-9>`_ - IDE для C и C++.
  Можно писать код на компе, а запускать и отлаживать на Raspberry Pi
- dd, `Etcher <https://www.raspberrypi.org/documentation/installation/installing-images/README.md>`_ и прочие:
  для прошивки образов (ОС) на карту памяти
- `Ninja IDE <http://ninja-ide.org/>`_ - ставится на саму Raspberry Pi, IDE для Python.

Также могут быть полезны:

- SSH - для удаленного доступа
- `PuTTY <https://elinux.org/RPi_Serial_Connection#Windows_terminal_set-up>`_ и
  `прочие <https://learn.sparkfun.com/tutorials/terminal-basics/serial-terminal-overview->`_ -
  для удаленного доступа и отладки по UART
