# myCobotCpp

请检查src/myCobotExample.cpp的用法

## 如何编译 (Linux)
1. 复制所有.so文件到lib目录下
2. 安装QT 5.12.10，然后Install Qt 5.12.10 and 设置QT环境变量（如： export QTDIR=$HOME/Qt/5.12.10/gcc_64）
3. 执行命令：mkdir build && cd build && cmake .. && cmake --build .
4. 运行示例: ./bin/myCobotCppExample

## 如何编译（ Ubuntu20.04）
1. 复制所有.so文件到lib目录下（注意下载后解压，不要在Windows解压后复制到Ubuntu，直接在Ubuntu解压，如：tar -xvf 然后直接拖动文件到终端）
2. 安装QT 5.12.10，然后Install Qt 5.12.10 and 设置QT环境变量（如： export QTDIR=$HOME/Qt/5.12.10/gcc_64）
3. 执行命令：mkdir build && cd build && cmake .. && cmake --build .
4. 将libQt5SerialPort.so.5(在QT安装目录，如：/home/“用户名”/Qt5.12.10/5.12.10/gcc_64/lib)软链接到mycobotcpp/build/bin（不要直接复制），命令如下（注意选择你们的路径）：ln -s /home/“用户名”/Qt5.12.10/5.12.10/gcc_64/lib/libQt5SerialPort.so.5 /home/“用户名”/myCobotCpp/build/bin/libQt5SerialPort.so.5
5. 修改机械臂串口权限，不能直接chmod...，这样每次重启都要再次该权限，如：5-1.cd /etc/udev/rules.d；5-2.sudo gedit 20-usb-serial.rules；5-3.在文件在加入：KERNEL=="ttyUSB*"  MODE="0777"
6. 运行示例：切换到bin目录下，执行./myCobotCppExample（注意切换到bin目录下，再运行，否则会报无法打开或者找不到libQt5SerialPort.so.5）

## 如何编译 (Windows VS 2019)
1. 安装QT5.12.10
  设置QT系统环境变量：此电脑--》右键 属性--》高级系统设置--》环境变量--》看系统变量处，点击新建--》变量名：QTDIR 变量值：msvc2017_64所在目录（如：D:\qt5.12.10\5.12.10\msvc2017_64，具体看自己电脑的安装路径）
2. 安装VS2019（尽量不用改变默认安装路径，其它路径容易出错）
  设置环境变量：如1的步骤，变量名：VCINSTALLDIR 变量值：找到Redist所在目录(如：C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC）
3. 安装qt插件vsaddin(选择对应vs 2019的版本)
  设置：vs2019菜单栏 扩展--》QT VS ToolS--》QT Versions--》add new qtversion Path选择msvc2017_64所在路径（如：D:\qt5.12.10\5.12.10\msvc2017_64）
4. 将.lib和.dll文件添加到myCobotCpp/lib（.lib和.dll这两个文件在myCobotCpp-0.0.3-windows-msvc-x86_64.zip压缩包内）
5. vs上运行MyCobotCpp
    菜单栏 文件--》打开--》Cmake--》选择MycobotCpp所在路径--》点击cmakelist.txt
    选择x64-Release编译（启动项旁边，如果没有，点击下拉框--》管理配置进行添加），同时cmake设置的配置处也要选择release
    点击生成，生成成功后，选择启动项（绿色播放键旁，也就是运行按钮旁），下拉选择myCobotCppEXample.exe(bin\myCobotCppExample.exe)，点击运行
注意：一定选择x64-Release进行编译；如果运行报缺少...请看下面

## 如何去编译 (Windows命令行)
1. 如果myCobotCpp.dll缺失，将之前放到lib目录下的myCobotCpp.dll放到mycobotcppexample.exe所在目录下
2. 如果报缺少QT5Core.dll，打开qt command（菜单栏搜索QT），选择msvc 2017 64-bit，执行windeployqt --release myCobotCppExample.exe所在目录（如：windeployqt --release D:\vs2019\myCobotCpp\out\build\x64-Release\bin）
  此处执行命令后如果报找不到vs安装路径，请检查vs环境变量的设置
3. 以上步骤执行后，如果报缺少qt5serialport.dll文件，将qt安装目录处的此文件(路径如：D:\qt5.12.10\5.12.10\msvc2017_64\bin)，拷贝到myCobotCppExample.exe所在目录

#关于库函数相关使用说明
1. 速度设置，可以使用SetSpeed函数或者WriteAngles/WriteCoords函数
   设置公式：速度设置有个公式：设置速度*100/最大速度，关节速度最大是18000，坐标速度最大是30000（设置速度越小，移动速度越快）
   注意：您可能会有这样的疑惑，为什么我速度设为1或者18，移动速度一样，比如设置1和18，代入公式后，如果是发送全部角度，
         就是0.005%和0.1%，因为相差不大，所以看上去移动速度一样，但是如果设置个180速度就不一样了

2. 如果不使用cmake编译，如直接在MFC中使用，按下图所示进行配置：
   ![配置图1](https://github.com/elephantrobotics/myCobotCpp/image/配置图1.png)
   ![配置图2](https://github.com/elephantrobotics/myCobotCpp/image/配置图2.png)