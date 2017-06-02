#include<stdio.h>
#include<math.h>

main() {
	int i=0;
	double r;
	FILE *f;
	f=fopen("radius.dat","w");
	printf("Running....../n");
	for(;i<=40;i+=2) {
		r=i;
		fprintf(f,"r=%lf\t\tV=%lf\n",r,4/3*M_PI*r*r*r);
	}
	printf("successfull.");
	fclose(f);
}