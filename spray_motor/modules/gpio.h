#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

int exportGpio(int num);
int setDirectionGpio(int num, const char *direction);
int setGpio(int num, int value);
int disableGpio(int num);

#ifdef __cplusplus
}
#endif          // __cplusplus

#endif		// __GPIO_H__
