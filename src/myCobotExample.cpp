#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>

#include <QCoreApplication>

#include "MyCobot.hpp"

#define ANGLES_OFFSET 5

using namespace mycobot;
using namespace std::chrono_literals;
template<typename T>
void PrintMsg(std::string str, T coords, uint8_t len);
Coords GetCoords();
bool IsAnglesInPosition(Angles goal_angles, uint8_t offset);

Coords get_coords{ 0 };

int main(int argc, char* argv[])
try {
	QCoreApplication a(argc, argv);
	if (!mycobot::MyCobot::I().IsControllerConnected()) {
		std::cerr << "Robot is not connected\n";
		exit(EXIT_FAILURE);
	}
	std::cout << "Robot is connected\n";
	mycobot::MyCobot::I().PowerOn();

	mycobot::MyCobot::I().SleepSecond(1);//需要等待1S，让前面的动作做完

	//设置io输出，2、5、26为m5输出引脚
	/*mycobot::MyCobot::I().SetBasicOut(2, 1);
	mycobot::MyCobot::I().SleepSecond(1);
	mycobot::MyCobot::I().SetBasicOut(5, 1);
	mycobot::MyCobot::I().SleepSecond(1);
	mycobot::MyCobot::I().SetBasicOut(26, 1);
	mycobot::MyCobot::I().SleepSecond(1);*/

	//m5输入引脚 35、36 第一次会出现延迟
	/*for (int i = 0; i < 2; i++) {
		std::cout << "35= " << mycobot::MyCobot::I().GetBasicIn(35) << std::endl;
		mycobot::MyCobot::I().SleepSecond(1);
		std::cout << "36= " << mycobot::MyCobot::I().GetBasicIn(36) << std::endl;
		mycobot::MyCobot::I().SleepSecond(1);
	}*/

	//atom输出引脚 23 33
	/*mycobot::MyCobot::I().SetDigitalOut(23, 1);
	mycobot::MyCobot::I().SleepSecond(1);
	mycobot::MyCobot::I().SetDigitalOut(33, 1);
	mycobot::MyCobot::I().SleepSecond(1);*/

	//atom输入引脚22 19 第一次会出现延迟
	/*for (int i = 0; i < 2; i++) {
		std::cout << "22= " << mycobot::MyCobot::I().GetDigitalIn(22) << std::endl;
		mycobot::MyCobot::I().SleepSecond(1);
		std::cout << "19= " << mycobot::MyCobot::I().GetDigitalIn(19) << std::endl;
		mycobot::MyCobot::I().SleepSecond(1);
	}*/

	//自适应夹爪 1--open 0--close 由于第一次有延迟，发送两次
	/*for (int i = 0; i < 2; i++) {
		mycobot::MyCobot::I().SetGriper(1);
		mycobot::MyCobot::I().SleepSecond(3);
		mycobot::MyCobot::I().SetGriper(0);
		mycobot::MyCobot::I().SleepSecond(3);
	}*/

	//电动夹爪 1-开 0-关  由于第一次有延迟，发送两次
	/*for (int i = 0; i < 2; i++) {
		mycobot::MyCobot::I().SetElectricGriper(1);
		mycobot::MyCobot::I().SleepSecond(1);
		mycobot::MyCobot::I().SetElectricGriper(0);
		mycobot::MyCobot::I().SleepSecond(1);
	}*/
	
	mycobot::MyCobot::I().StopRobot();
	std::this_thread::sleep_for(200ms);

	std::cout << "Robot is moving: " << mycobot::MyCobot::I().IsMoving() << "\n";
	std::this_thread::sleep_for(200ms);

	//读取运动前的角度
	mycobot::Angles angles = mycobot::MyCobot::I().GetAngles();
	PrintMsg("get_angles1 ", angles, Joints);

	//坐标运动前机械臂需要垂直90°，J3动至90°
	mycobot::Angles goal_angles = { 0, 0, 90, 0, 0, 0 };
	for (int i = 0; i < 14; ++i) {
		goal_angles[0] = 10 * i;
		mycobot::MyCobot::I().WriteAngles(goal_angles, 100);
		PrintMsg("goal_angles ", goal_angles, Joints);
		//std::this_thread::sleep_for(1000ms);
		//判断是否到达点位 
		while (!IsAnglesInPosition(goal_angles, ANGLES_OFFSET)) {
			angles = mycobot::MyCobot::I().GetAngles();
			PrintMsg("get_angles2 ", angles, Joints);
			std::this_thread::sleep_for(200ms);
		}
		angles = mycobot::MyCobot::I().GetAngles();
		std::this_thread::sleep_for(200ms);
		angles = mycobot::MyCobot::I().GetAngles();
		PrintMsg("end_angles2 ", angles, Joints);
		std::this_thread::sleep_for(200ms);
	}
	//mycobot::MyCobot::I().JogAngle(mycobot::Joint::J1, 1, 5);
	std::this_thread::sleep_for(5000ms);
	mycobot::MyCobot::I().StopRobot();
	std::this_thread::sleep_for(200ms);

	//读取当前坐标，z轴减20°
	Coords goal_coords = GetCoords();
	goal_coords[2] -= 20;
	std::this_thread::sleep_for(200ms);
	mycobot::MyCobot::I().WriteCoords(goal_coords, 100);
	std::this_thread::sleep_for(5000ms);
	//读取运动后的坐标
	goal_coords = GetCoords();

	std::cout << "\n";
	exit(EXIT_SUCCESS);
} catch (std::error_code&) {
	std::cerr << "System error. Exiting.\n";
	exit(EXIT_FAILURE);
} catch (...) {
	std::cerr << "Unknown exception thrown. Exiting.\n";
	exit(EXIT_FAILURE);
}

//打印相关信息，可以用于打印角度、坐标等
template<typename T>
void PrintMsg(std::string str, T data, uint8_t len)
{
	std::cout << str << " [";
	for (int i = 0; i < len; ++i) {
		if (i != 0)
			std::cout << ", ";
		std::cout << data[i];
	}
	std::cout << "]" << std::endl;
}

//读取并打印当前坐标 由于第一次有延迟，读取两次
Coords GetCoords()
{
	for (int i = 0; i < 3; ++i) {
		get_coords = mycobot::MyCobot::I().GetCoords();
		std::this_thread::sleep_for(200ms);
	}
	PrintMsg("get_coords", get_coords, Joints);
	return get_coords;
}

bool IsAnglesInPosition(Angles goal_angles, uint8_t offset)
{
	Angles get_angles{ 0 };
	for (int i = 0; i < 2; ++i) {
		get_angles = mycobot::MyCobot::I().GetAngles();
		std::this_thread::sleep_for(200ms);
	}
	for (int i = 0; i < Joints; ++i) {
		//std::cout << "equal " << goal_angles[i] << ", " << get_angles[i] << std::endl;
#if defined(__linux__)
		if (labs(goal_angles[i] - get_angles[i]) > offset)
#else
		if (fabs(goal_angles[i] - get_angles[i]) > offset)
#endif
			return false;
	}
	return true;
}
