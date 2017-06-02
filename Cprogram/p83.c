#include<stdio.h>
#include<math.h>

main() {
	double a,b,c,x1,x2,AC;
	printf("ax^2+bx+c=0\nInput a b c:");
	scanf("%lf %lf %lf",&a,&b,&c);
	AC=sqrt(b*b-4*a*c);
	if(b*b-4*a*c<0) {
		printf("I cant solve this!!");
	} else {
		x1=(-b+AC)/(2*a);
		x2=(-b-AC)/(2*a);
		printf("\nx1=%lf\nx2=%lf\n",x1,x2);
	}
}