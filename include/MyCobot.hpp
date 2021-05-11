/**
 * @file MyCobot.hpp
 * @brief C++ API for myCobot.
 */

#ifndef MYCOBOTCPP_MYCOBOT_MYCOBOT_HPP
#define MYCOBOTCPP_MYCOBOT_MYCOBOT_HPP

#include <array>
#include <iostream>
#include <memory>

namespace mycobot {

enum Axis : int { X = 0, Y, Z, RX, RY, RZ };
enum Joint : int { J1 = 0, J2, J3, J4, J5, J6 };
constexpr const int Axes = 6;
constexpr const int Joints = 6;
using Coords = std::array<double, Axes>;
using Angles = std::array<double, Joints>;

constexpr const int DefaultSpeed = 30;

/**
 * @brief 
 */
class MyCobot {
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

protected:
	MyCobot() = default;
private:
	std::shared_ptr<class MyCobotImpl> impl{};
};

}
#endif
