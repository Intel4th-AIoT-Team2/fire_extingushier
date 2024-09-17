#ifndef __ITOA_H__
#define __ITOA_H__

#ifdef __cplusplus
extern "C" {
#endif

int waitCtl(float time);
void reverse(char str[], int length);
char* itoa(int num, char* str, int base);

#ifdef __cplusplus
}
#endif          // __cplusplus

#endif 		// __ITOA_H__
