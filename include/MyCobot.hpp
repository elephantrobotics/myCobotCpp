/**
 * @file MyCobot.hpp
 * @brief C++ API for myCobot.
 *
 * @copyright Elephant Robotics
 */

#ifndef MYCOBOTCPP_MYCOBOT_MYCOBOT_HPP
#define MYCOBOTCPP_MYCOBOT_MYCOBOT_HPP

#include <array>
#include <iostream>
#include <memory>
#if defined WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "MyCobotExport.hpp"

/**
 * @namespace mycobot
 * @brief Namespace where all myCobot related classes and types are defined.
 */
namespace mycobot {

enum Axis : int { X = 1, Y, Z, RX, RY, RZ };
enum Joint : int { J1 = 1, J2, J3, J4, J5, J6 };
constexpr const int Axes = 6;
constexpr const int Joints = 6;
using Coords = std::array<double, Axes>;
using Angles = std::array<double, Joints>;

constexpr const int DefaultSpeed = 30;

/**
 * @class MyCobot
 * @brief Main class that defines API for myCobot.
 */
class MYCOBOTCPP_API MyCobot {
public:
	/**
	 * @brief Get singleton instance of MyCobot.
	 * 'I' stands for 'Instance'.
	 * @throws std::error_code if serial port cannot be opened
	 * @returns singleton instance of MyCobot object
	 */
	static MyCobot I();
	/** Copy constructor */
	MyCobot(const MyCobot&) = default;
	/** Copy assignment operator */
	MyCobot& operator=(const MyCobot&) = default;
	/** Destructor */
	virtual ~MyCobot() = default;
	/** Move constructor */
	MyCobot(MyCobot&&) = delete;
	/** Move assignment operator */
	MyCobot& operator=(MyCobot&&) = delete;

	void PowerOn();
	void PowerOff();
	bool IsControllerConnected() const;
	void StopRobot();
	/**
	 * @brief Checks if robot is in given position.
	 *
	 * This function can be used to check if robot is at the
	 * given point at the moment or if robot has reached target
	 * point with this pseudo code:
	 * 
	 *     WriteCoords(coords)
	 *     while (IsMoving() && !IsInPosition(coords))
	 *         sleep(1)
	 *
	 * @param[in] coords The meaning depends on is_linear parameter:
	 *                   if is_linear is true, coords are cartesian coordinates
	 *                   of target point,
	 *                   if is_linear is false, coords are joint angles
	 *                   of target robot position.
	 * @param[in] is_linear defines meaning of coords parameter, if true --
	 *                      coords are cartesian coordinates, if false --
	 *                      coords are angles of robot joints.
	 * @returns true if robot is at coords point at the moment, false otherwise.
	 */
	bool IsInPosition(const Coords& coords, bool is_linear = true) const;
	bool IsMoving() const;
	int GetSpeed() const;
	void SetSpeed(int percentage);
	double GetJointMin(Joint joint) const;
	double GetJointMax(Joint joint) const;

	void SetFreeMoveMode(bool free_move = true);
	bool IsFreeMoveMode() const;

	Angles GetAngles() const;
	void WriteAngles(const Angles& angles, int speed = DefaultSpeed);
	void WriteAngle(Joint joint, double value, int speed = DefaultSpeed);
	Coords GetCoords() const;
	void WriteCoords(const Coords& coords, int speed = DefaultSpeed);
	void WriteCoord(Axis axis, double value, int speed = DefaultSpeed);

	void JogCoord(Axis axis, int direction, int speed = DefaultSpeed);
	void JogAngle(Joint joint, int direction, int speed = DefaultSpeed);
	void JogCoordAbsolute(Axis axis, double value, int speed = DefaultSpeed);
	void JogAngleAbsolute(Joint joint, double value, int speed = DefaultSpeed);
	void JogCoordIncrement(Axis axis, double increment, int speed = DefaultSpeed);
	void JogAngleIncrement(Joint joint, double increment, int speed = DefaultSpeed);

	//io
	int GetBasicIn(int pin_number) const;
	void SetBasicOut(int pin_number, int pin_signal);
	int GetDigitalIn(int pin_number) const;
	void SetDigitalOut(int pin_number, int pin_signal);

	//gripper
	void SetGriper(int open);//自适应夹爪
	void SetElectricGriper(int open);//电动夹爪
	void SleepSecond(unsigned time);

protected:
	MyCobot() = default;
private:
	/**
	 * Private implementation detail.
	 *
	 * It allows for cheap copies of enclosing class and hides implementation details.
	 */
	std::shared_ptr<class MyCobotImpl> impl{};
};

}
#endif
