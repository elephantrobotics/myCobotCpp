#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>

#include <QCoreApplication>

#include "MyCobot.hpp"

int main(int argc, char* argv[])
try {
	QCoreApplication a(argc, argv);
	using namespace std::chrono_literals;
	if (!mycobot::MyCobot::I().IsControllerConnected()) {
		std::cerr << "Robot is not connected\n";
		exit(EXIT_FAILURE);
	}
	std::cout << "Robot is connected\n";
	mycobot::MyCobot::I().PowerOn();
	mycobot::MyCobot::I().StopRobot();
	std::cout << "Robot is moving: " << mycobot::MyCobot::I().IsMoving() << "\n";
	mycobot::Angles angles = mycobot::MyCobot::I().GetAngles();
	std::this_thread::sleep_for(200ms);
	mycobot::Coords coords = mycobot::MyCobot::I().GetCoords();
	angles = mycobot::MyCobot::I().GetAngles();
	std::cout << "[" << angles[mycobot::J1] << ", " << angles[mycobot::J2] << ", " << angles[mycobot::J3] << ", "
		<< angles[mycobot::J4] << ", " << angles[mycobot::J5] << ", " << angles[mycobot::J6] << "]";
	mycobot::Angles goal_angles = { 5, 5, 5, 5, 5, 5 };
	mycobot::MyCobot::I().WriteAngles(goal_angles);
	while (!mycobot::MyCobot::I().IsInPosition(goal_angles, false)) {
		angles = mycobot::MyCobot::I().GetAngles();
		std::cout << "[" << angles[mycobot::J1] << ", " << angles[mycobot::J2] << ", "
			<< angles[mycobot::J3] << ", " << angles[mycobot::J4] << ", "
			<< angles[mycobot::J5] << ", " << angles[mycobot::J6] << "]" << std::flush;
		std::this_thread::sleep_for(200ms);
	}

	mycobot::MyCobot::I().JogAngle(mycobot::Joint::J1, 1, 5);
	std::this_thread::sleep_for(5000ms);
	mycobot::MyCobot::I().StopRobot();

	std::cout << "\n";
	exit(EXIT_SUCCESS);
} catch (std::error_code&) {
	std::cerr << "System error. Exiting.\n";
	exit(EXIT_FAILURE);
} catch (...) {
	std::cerr << "Unknown exception thrown. Exiting.\n";
	exit(EXIT_FAILURE);
}
