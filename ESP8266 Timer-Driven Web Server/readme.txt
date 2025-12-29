This project implements a non-blocking web server on the ESP8266 that is serviced using a hardware timer interrupt instead of relying on the main loop() timing.

A timer interrupt periodically sets a flag, and when this flag is detected in the main loop, the ESP8266 processes incoming HTTP client requests using ESP8266WebServer. This design allows the microcontroller to handle web requests at fixed time intervals while still leaving room for other tasks to run concurrently.

🔧 Key Features

Uses ESP8266 hardware timer interrupts for precise periodic execution

Runs an HTTP web server without blocking the main loop

Timer prescaler configured for longer interval timing (DIV256)

Flag-based interrupt handling (safe ISR design)

Suitable for multitasking systems (sensors, control logic, automation)

🧠 How It Works

A hardware timer triggers an interrupt at a defined interval

The interrupt sets a boolean flag (timerFlag)

The main loop checks this flag

When set, the web server processes incoming client requests

Prevents long blocking delays and improves responsiveness

🧩 Libraries Used

ESP8266WiFi.h

ESP8266WebServer.h

ESP8266TimerInterrupt.h

🎯 Typical Use Cases

IoT dashboards

Periodic web-controlled devices

ESP8266 projects requiring accurate timing + networking

Systems that must stay responsive while doing background tasks

If you want, next code can be named consistently (same project family) or more product-like names (e.g. industrial / IoT style).