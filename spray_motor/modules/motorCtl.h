#ifndef __MOTORCTL_H__
#define __MOTORCTL_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PERIOD 20000000
#define DUTY 1000000

int controlMotorAngle(int, int);
int enPwm();
int disPwm();

#ifdef __cplusplus
}
#endif          // __cplusplus

#endif	// __MOTORCTL_H__
