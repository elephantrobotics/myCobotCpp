#ifndef MYCOBOTCPP_MYCOBOT_MYCOBOTEXPORT_HPP
#define MYCOBOTCPP_MYCOBOT_MYCOBOTEXPORT_HPP

#if defined _WIN32 || defined __CYGWIN__
  #define MYCOBOTCPP_HELPER_DSO_IMPORT __declspec(dllimport)
  #define MYCOBOTCPP_HELPER_DSO_EXPORT __declspec(dllexport)
  #define MYCOBOTCPP_HELPER_DSO_LOCAL
#else
  #if __GNUC__ >= 4
    #define MYCOBOTCPP_HELPER_DSO_IMPORT __attribute__ ((visibility ("default")))
    #define MYCOBOTCPP_HELPER_DSO_EXPORT __attribute__ ((visibility ("default")))
    #define MYCOBOTCPP_HELPER_DSO_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define MYCOBOTCPP_HELPER_DSO_IMPORT
    #define MYCOBOTCPP_HELPER_DSO_EXPORT
    #define MYCOBOTCPP_HELPER_DSO_LOCAL
  #endif
#endif

#ifdef MYCOBOTCPP_DSO
  #ifdef MYCOBOTCPP_DSO_EXPORTS
    #define MYCOBOTCPP_API MYCOBOTCPP_HELPER_DSO_EXPORT
  #else
    #define MYCOBOTCPP_API MYCOBOTCPP_HELPER_DSO_IMPORT
  #endif
  #define MYCOBOTCPP_LOCAL MYCOBOTCPP_HELPER_DSO_LOCAL
#else
  #define MYCOBOTCPP_API
  #define MYCOBOTCPP_LOCAL
#endif

#endif
