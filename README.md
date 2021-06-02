# myCobotCpp

C++ Interface for myCobot.

Please, download appropriate binaries for your platform from Releases page and put them into `lib` folder.

## Example Code

Please check src/myCobotExample.cpp for example usage.

## How to build on Linux

1. Copy `*.so` to `lib` directory
2. Install Qt 5.12.10 and export QTDIR installation directory (eg: `export QTDIR=$HOME/Qt/5.12.10/gcc_64`)
3. mkdir build && cd build && cmake .. && cmake --build .
4. Run example: `./bin/myCobotCppExample`

## How to build on Ubuntu20.04
1. Copy all.so files to the lib directory (Note to extract after download, do not copy to Ubuntu after Windows extract, extract directly from Ubuntu, eg: 'tar-xvf and drag files directly to the terminal')
2. Install Qt 5.12.10 and export QTDIR installation directory (eg: `export QTDIR=$HOME/Qt/5.12.10/gcc_64`)
3. mkdir build && cd build && cmake .. && cmake --build .
4. Place libqt5serialport.so.5(in the Qt installation directory, eg: /home/ "user name"/qt5.12.10/5.12.10 /gcc_64/lib) soft link to mycobotcpp/build/bin (do not copy directly),the command is as follows (note to choose your path):'ln -s /home/“用户名”/Qt5.12.10/5.12.10/gcc_64/lib/libQt5SerialPort.so.5 /home/“用户名”/myCobotCpp/build/bin/libQt5SerialPort.so.5'
5. Modify the robot arm serial port permissions, can not directly chmod...Beause if do this, you should change the permissions every time you start up.
   eg:5-1.cd /etc/udev/rules.d; 5-1.cd /etc/udev/rules.d;5-2. Sudo gedit 20 - usb to serial. Rules;5-3.In the file add:KERNEL=="ttyUSB*" MODE="0777"
6. Run example: switch to bin directory and execute'./myCobotCppExample' (Note: switch to bin directory and run, otherwise the report will not open or cannot find libqt5serialport.so.5)
Note: 1. if an error is reported at compile time: Please check steps 1 and 2
      2. if an error is reported at run time
      eg: 2-1. eg: System Error, it may be that the mechanical arm serial port fails to open. Please check Step 5
          2-2. eg: Libqt5SerialPort.so.5 cannot be opened or found. Please check steps 4 and 6

## How to build on Windows VS 2019
1. install Qt5.12.10
  set qt system environment variables(eg: this computer-->right click-->properties --> advanced system Settings -->environment variables --> look at the system variables
  -->click on the new -- >variable name:QTDIR  variable value: the directory where msvc2017_64 is located (eg: D:\qt5.12.10\5.12.10\msvc2017_64(see the installation path of his computer specifically))

2. install VS 2019(try not to change the default installation path. Other paths are error-prone)
  set environment variables: steps like 1, variable name: VCINSTALLDIR variable value: Find the directory where Redist is located(eg: C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC)

3. install the qt plugin vsaddin(select the version corresponding to VS 2019)
  settings: VS2019 Menu Bar Extension -- >Qt VS Tools -->Qt Versions--> click Add new QtVersion, the path select the path where msvc2017_64 is located(eg: D:\qt5.12.10\5.12.10\msvc2017_64)

4. add.lib and.dll files to myCobotCpp/lib (the.lib and.dll files are in the mycobotcpp-0.0.3-Windows-MSVC-x86_64.zip package)

5. run MyCobotCpp on VS
  menu bar,file -- >Open --> Cmake-->select the path where MycobotCpp is located --> click cmakelist.txt
  select x64-Release Compile (next to the startup item, if not, click the 'Manage Configuration' drop-down box to add it), and also select Release from the configuration section of the CMAKE Settings
  click "Generate". Once successful, select the start item (next to the green play key, that is, next to the Run button), drop down and select MyCobotcppExample.exe (bin\ MyCobotcppExample.exe) and click "Run"

warnning: be sure to select x64-release for compilation;If the running message is missing...Please see the following

## How to build on Windows Command Line
1. if mycobotcpp.dll is missing, put the mycobotcpp.dll that was placed in the lib directory into the directory where mycobotcppexample.exe is

2. if QT5Core.cpp is missing, open Qt Command (search for Qt in the menu bar), select MSVC 2017 64-bit, and execute WinDeployQt --release mycobotcppexample.exe in the directory (eg: Windeployqt - release D:\vs2019\myCobotCpp\out\build\x64-release\bin)
   if the VS installation path cannot be found after executing the command here, please check the settings of the VS environment variable

3. if QT5SerialPort.dll is missing after the above steps, copy this file (eg: D: qt5.12.10\5.12.10\msvc2017_64\bin) from the Qt installation directory to the directory where mycobotcppexample.exe is located
