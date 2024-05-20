# weather-widget

A simple little C++/QML application using weatherapi.com to display current weather/temperature (in fahrenheit) for some cities around the world.

Ideally, this application should be cross-compiled and loaded onto the STM32MP157F-DK2 discovery board using its 800x480 screen.

Of course, you could load this onto anything, but your results may vary.

If you wish to use this application, register for a weatherapi.com account and paste your API key into the corresponding text file. The application will read this file during run-time.

If you are interested on loading this onto a board, let's say a Raspberry Pi or Beaglebone, and don't know where to start, then you should check out Buildroot or the Yocto Project.
