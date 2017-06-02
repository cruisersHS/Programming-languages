#include<stdio.h>
#include<math.h>

main() {
	int i;
	for(i=0;i<=10;i++) {
		printf("sin((%d/10)*pi) = %lf\tcos((%d/10)*pi) = %lf\n",i,sin(M_PI*i/10),i,cos(M_PI*i/10));
	}
}