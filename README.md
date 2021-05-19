# myCobotCpp

C++ Interface for myCobot.

Please, download appropriate binaries for your platform from Releases page and put them into `lib` folder.

## Example Code

Please check src/myCobotExample.cpp for example usage.

## How to build on Linux

1. Copy `*.so` to `lib` directory
2. Install Qt 5.12.10 and export QTDIR installation directory (eg: `export QTDIR=$HOME/Qt/5.12.10/gcc_64`)
3. mkdir build && cd build && cmake .. && cmake --build 
4. Run example: `./bin/myCobotCppExample`

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
1. open VS Command (Windows menu bar directly search for VS), switch to the directory where myCobotCpp is located, and execute "cmake -G "Visual Studio 16 2019" -A x64"

2. open Qt Command (search for Qt in the menu bar), select MSVC 2017 64-bit, and execute WinDeployQt --release mycobotcppexample.exe in the directory (eg: Windeployqt - release D:\vs2019\myCobotCpp\out\build\x64-release\bin)
   if the VS installation path cannot be found after executing the command here, please check the settings of the VS environment variable
3. if QT5SerialPort.dll is missing after the above steps, copy this file (eg: D: qt5.12.10\5.12.10\msvc2017_64\bin) from the Qt installation directory to the directory where mycobotcppexample.exe is located