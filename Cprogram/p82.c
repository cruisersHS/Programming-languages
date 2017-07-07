#include<stdio.h>
#include<math.h>

main() {
	double r;
	printf("Input R:\n");
	scanf("%lf",&r);
	printf("V = %lf\n",4/3*M_PI*r*r*r);
}