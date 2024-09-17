#ifndef __PWM_H__
#define __PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

int exportPwm(int);
int setPwm(int, int, int);
int enablePwm(int);
int disablePwm(int);
int unexportPwm(int);

#ifdef __cplusplus
}
#endif          // __cplusplus

#endif		// __PWM_H__
