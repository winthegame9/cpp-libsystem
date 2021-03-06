CPP Project HiOA 2017
===================

[![N|Solid](http://d33sqmjvzgs8hq.cloudfront.net/wp-content/themes/oneqt/assets/images/favicon-32x32.png)](https://nodesource.com/products/nsolid)

This is the final C++ project for group 3 at the university college of applied science in Oslo and Akershus.

### The group members :
	- El Morabeti Mohamed

>The main purpose of what we've build is to provide a library system
>that can solve any librarians needs, the system can be implemented by anyone and due to its user-friendliness is very simple to use.

### Installation
**You can either choose to download the ELF binary executable, or compile the source code, instructions down below.**

For projects that need to be built differently on each target platform, with many subdirectories, you can run qmake with each of the following options to set the corresponding platform-specific variable in each project file:



**-unix**
qmake will run in unix mode. In this mode, Unix file naming and path conventions will be used, additionally testing for unix (as a scope) will succeed. This is the default mode on all Unices.



**-macx**
qmake will run in Mac OS X mode. In this mode, Unix file naming and path conventions will be used, additionally testing for macx (as a scope) will succeed. This is the default mode on Mac OS X.



**-win32**
qmake will run in win32 mode. In this mode, Windows file naming and path conventions will be used, additionally testing for win32 (as a scope) will succeed. This is the default mode on Windows.

**Warning**
If you see QtCored4.dll is missing that means you must add Qt bin to the $PATH!


For more info please see: http://doc.qt.io/qt-4.8/qmake-running.html

**For windows**
```sh
$ git clone https://github.com/winthegame9/cpp-libsystem
$ gunzip -c cpp-libsystem.tar.gz | tar -xvf -
$ cd cpp-libsystem/
$ configure.bat -platform win32-g++
$ configure.bat -platform win32-msvc2010

```
**For Unix/Linux**
```sh
$ git clone https://github.com/winthegame9/cpp-libsystem
$ gunzip -c cpp-libsystem.tar.gz | tar -xvf -
$ cd cpp-libsystem/
$ sudo su
$./configure -platform linux-clang
$./configure -platform linux-g++
$./configure -platform linux-g++-32
$ make
$ make install
```

2017 - [Oslo and Akershus University College](http://hioa.no)

[hioa-lnk]: <https://github.com/RahulHP/dillinger/blob/master/plugins/googleanalytics/README.md>
