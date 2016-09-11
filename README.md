# Airbutton

[![Build Status](https://travis-ci.org/gallochri/gallAButton.svg?branch=master)](https://travis-ci.org/airbutton/airbutton-firmware)

[![](http://img.youtube.com/vi/AoWVcrVlDQk/0.jpg)](http://www.youtube.com/watch?v=AoWVcrVlDQk)


Getting Started with QT Creator
---

**Install Platformio CLI and QTCreator**

```
$ git clone https://github.com/airbutton/airbutton-firmware.git

$ cd airbutton-firmware

$ platformio init --ide qtcreator

$ mv platformio.pro airbutton.pro
````

**Open QTCreator**

Click on File -> Open File or Project -> (select airbutton.pro) -> Configure Project

(Left panel) Projects ->

![](images/qtcreator1.png)

![](images/qtcreator2.png)

![](images/qtcreator3.png)

```
Build -> "Build All" or hammer icon   = Build project
Build -> Rebuild All                  = Clean and Build
Build -> Clean All                    = Clean all
Build -> Deploy All                   = Clean,Build & Upload
Build -> Run                          = Clean,Build,Upload & open Serial Monitor
````

> Remenber to close serial monitor window before re-deploy.

References
---
- https://github.com/teopost/iot-button
