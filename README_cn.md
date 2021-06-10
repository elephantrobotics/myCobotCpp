# myCobotCpp

����src/myCobotExample.cpp���÷�

## ��α��� (Linux)
1. ��������.so�ļ���libĿ¼��
2. ��װQT 5.12.10��Ȼ��Install Qt 5.12.10 and ����QT�����������磺 export QTDIR=$HOME/Qt/5.12.10/gcc_64��
3. ִ�����mkdir build && cd build && cmake .. && cmake --build .
4. ����ʾ��: ./bin/myCobotCppExample

## ��α��루 Ubuntu20.04��
1. ��������.so�ļ���libĿ¼�£�ע�����غ��ѹ����Ҫ��Windows��ѹ���Ƶ�Ubuntu��ֱ����Ubuntu��ѹ���磺tar -xvf Ȼ��ֱ���϶��ļ����նˣ�
2. ��װQT 5.12.10��Ȼ��Install Qt 5.12.10 and ����QT�����������磺 export QTDIR=$HOME/Qt/5.12.10/gcc_64��
3. ִ�����mkdir build && cd build && cmake .. && cmake --build .
4. ��libQt5SerialPort.so.5(��QT��װĿ¼���磺/home/���û�����/Qt5.12.10/5.12.10/gcc_64/lib)�����ӵ�mycobotcpp/build/bin����Ҫֱ�Ӹ��ƣ����������£�ע��ѡ�����ǵ�·������ln -s /home/���û�����/Qt5.12.10/5.12.10/gcc_64/lib/libQt5SerialPort.so.5 /home/���û�����/myCobotCpp/build/bin/libQt5SerialPort.so.5
5. �޸Ļ�е�۴���Ȩ�ޣ�����ֱ��chmod...������ÿ��������Ҫ�ٴθ�Ȩ�ޣ��磺5-1.cd /etc/udev/rules.d��5-2.sudo gedit 20-usb-serial.rules��5-3.���ļ��ڼ��룺KERNEL=="ttyUSB*"  MODE="0777"
6. ����ʾ�����л���binĿ¼�£�ִ��./myCobotCppExample��ע���л���binĿ¼�£������У�����ᱨ�޷��򿪻����Ҳ���libQt5SerialPort.so.5��

## ��α��� (Windows VS 2019)
1. ��װQT5.12.10
  ����QTϵͳ�����������˵���--���Ҽ� ����--���߼�ϵͳ����--����������--����ϵͳ������������½�--����������QTDIR ����ֵ��msvc2017_64����Ŀ¼���磺D:\qt5.12.10\5.12.10\msvc2017_64�����忴�Լ����Եİ�װ·����
2. ��װVS2019���������øı�Ĭ�ϰ�װ·��������·�����׳���
  ���û�����������1�Ĳ��裬��������VCINSTALLDIR ����ֵ���ҵ�Redist����Ŀ¼(�磺C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC��
3. ��װqt���vsaddin(ѡ���Ӧvs 2019�İ汾)
  ���ã�vs2019�˵��� ��չ--��QT VS ToolS--��QT Versions--��add new qtversion Pathѡ��msvc2017_64����·�����磺D:\qt5.12.10\5.12.10\msvc2017_64��
4. ��.lib��.dll�ļ���ӵ�myCobotCpp/lib��.lib��.dll�������ļ���myCobotCpp-0.0.3-windows-msvc-x86_64.zipѹ�����ڣ�
5. vs������MyCobotCpp
    �˵��� �ļ�--����--��Cmake--��ѡ��MycobotCpp����·��--�����cmakelist.txt
    ѡ��x64-Release���루�������Աߣ����û�У����������--���������ý�����ӣ���ͬʱcmake���õ����ô�ҲҪѡ��release
    ������ɣ����ɳɹ���ѡ���������ɫ���ż��ԣ�Ҳ�������а�ť�ԣ�������ѡ��myCobotCppEXample.exe(bin\myCobotCppExample.exe)���������
ע�⣺һ��ѡ��x64-Release���б��룻������б�ȱ��...�뿴����

## ���ȥ���� (Windows������)
1. ���myCobotCpp.dllȱʧ����֮ǰ�ŵ�libĿ¼�µ�myCobotCpp.dll�ŵ�mycobotcppexample.exe����Ŀ¼��
2. �����ȱ��QT5Core.dll����qt command���˵�������QT����ѡ��msvc 2017 64-bit��ִ��windeployqt --release myCobotCppExample.exe����Ŀ¼���磺windeployqt --release D:\vs2019\myCobotCpp\out\build\x64-Release\bin��
  �˴�ִ�������������Ҳ���vs��װ·��������vs��������������
3. ���ϲ���ִ�к������ȱ��qt5serialport.dll�ļ�����qt��װĿ¼���Ĵ��ļ�(·���磺D:\qt5.12.10\5.12.10\msvc2017_64\bin)��������myCobotCppExample.exe����Ŀ¼

#���ڿ⺯�����ʹ��˵��
1. �ٶ����ã�����ʹ��SetSpeed��������WriteAngles/WriteCoords����
   ���ù�ʽ���ٶ������и���ʽ�������ٶ�*100/����ٶȣ��ؽ��ٶ������18000�������ٶ������30000�������ٶ�ԽС���ƶ��ٶ�Խ�죩
   ע�⣺�����ܻ����������ɻ�Ϊʲô���ٶ���Ϊ1����18���ƶ��ٶ�һ������������1��18�����빫ʽ������Ƿ���ȫ���Ƕȣ�
         ����0.005%��0.1%����Ϊ�������Կ���ȥ�ƶ��ٶ�һ��������������ø�180�ٶȾͲ�һ����

2. �����ʹ��cmake���룬��ֱ����MFC��ʹ�ã�����ͼ��ʾ�������ã�
   ![����ͼ1](https://github.com/elephantrobotics/myCobotCpp/image/����ͼ1.png)
   ![����ͼ2](https://github.com/elephantrobotics/myCobotCpp/image/����ͼ2.png)