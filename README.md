# USBConsoleSuite

<!--toc:start-->

- [USBConsoleSuite](#usbconsolesuite)
  - [Building And Running](#building-and-running)
  <!--toc:end-->

## Building And Running

The project is built using CMake. The following options are available:

```bash
cd build
cmake ..
cmake --build .
```

The following will run the USBConsoleSuite application:

```bash
cd build/USBHIDConsoleApplication/Debug/
./USBHIDConsoleApplication.exe
```

## What is this?

The USB Console Suite is a set of applications that allow you to send and receive data from a USB HID device. The applications are written in C++ and use the [HIDAPI](https://github.com/libusb/hidapi) framework for the USB HID communication. The applications are cross platform and have been tested on Windows and Linux.

The applications are:

USBHIDConsoleApplication - A console application that allows you to send and receive data from a USB HID device. This application is useful for testing and debugging USB HID devices.
