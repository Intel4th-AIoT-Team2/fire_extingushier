#ifndef __AI_H__
#define __AI_H__

#ifdef __cplusplus
extern "C" {
#endif

int onAI(int *);
int offAI(int *);
int workAI(int *);
void rmText();

bool findPos(char *angle_x, char *angle_y);

void handler(int signo);
int takePic(char *filename);


#ifdef __cplusplus
}
#endif		// __cplusplus

#endif 		// __AI_H_
