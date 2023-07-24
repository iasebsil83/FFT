//standard
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//graphics
#include "../lib/S2DE.h"

//sound file info
#include "data.c"






// =================== DECLARATIONS =====================

// ---- S2DE variables ----
extern unsigned int S2DE_width;
extern unsigned int S2DE_height;

// ---- FFT constants ----
#define FREQ_MIN 2600
#define FREQ_MAX 3000
#define SAMPLE_NBR 524288
#define SAMPLE_RATE 44100
#define GRAPH_DIV 1000
#define OFFSET 200
#define PRECISION_DIV 1

// ---- FFT variables ----
float freq_amp[FREQ_MAX-FREQ_MIN];
int graph_freq = 0;
int graph_cnt = 0;






// ====================== EVENTS ========================

// ---- unused events ----
void S2DE_event(int event){
	switch(event){
		case S2DE_DISPLAY:
			//white background
			S2DE_setColor(255,255,255);
			S2DE_rectangle(0,0, S2DE_width,S2DE_height, 1);

			//black lines
			S2DE_setColor(  0,  0,  0);

			//fourrier spectrum
			printf("Starting Fourrier spectrum...\n");
			graph_freq = 0;
			for(int x=0; x < S2DE_width; x++){
				//draw
				S2DE_rectangle(
					2*x, 0,
					2*x+1, pow( abs(freq_amp[graph_freq])/GRAPH_DIV ,2)/500, 1
				);

				//evolution
				graph_freq++;
				graph_cnt++;

				printf("%i\n", (int)( abs(freq_amp[graph_freq])/GRAPH_DIV ));

				//limit
				if(graph_freq > FREQ_MAX-FREQ_MIN)
					break;
			}
			printf("%i values displayed starting from %i to %i\n", graph_cnt, FREQ_MIN, FREQ_MIN+graph_freq);
			printf("Ending Fourrier spectrum !\n");
		break;

		case S2DE_KEYBOARD:
		break;
		case S2DE_MOUSE_CLICK:
		break;
		case S2DE_MOUSE_MOVE:
		break;
		case S2DE_RESIZE:
		break;
		case S2DE_TIMER:
		break;
	}
}






// ====================== EXECUTION ======================

// ---- launch game ----
int main(int argc, char **argv){

	//fourier transform
	printf("Starting Fourrier transform...\n");
	for(int f=0; f < FREQ_MAX-FREQ_MIN; f++){
		freq_amp[f] = 0;

		//integral
		for(int t=0; t < SAMPLE_NBR/PRECISION_DIV; t++)
			freq_amp[f] += temp_amp[PRECISION_DIV*t] * cos( 2*M_PI*(f+FREQ_MIN)*PRECISION_DIV*t /SAMPLE_NBR );

		if(f != 0)
			freq_amp[f] = (freq_amp[f] + freq_amp[f-1])/2;
	}
	printf("Ending Fourrier transform !\n");

	//init window
	S2DE_init(argc,argv, "FFT - ShortBlackLizard.wav", 1800,700);

	//start window
	S2DE_start();
	return EXIT_SUCCESS;
}
