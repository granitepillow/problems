#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>


#define radi 15
#define rowheight 1.86
int main() {
	for(int i=0; i < (radi+1)*2; i++) {
		double y = (radi-i)*rowheight;
		double x = (radi*radi) - (y*y);
		int stars = (int)(sqrt(x) + 0.5);
		
		int spaces = (radi - stars);
		stars = stars*2;
		for(int j=0; j < spaces; j++) {
			printf(" ");
		}
		for(int j=0; j < stars; j++) {
			printf("*");
		}
		printf("\n");
	}

}
