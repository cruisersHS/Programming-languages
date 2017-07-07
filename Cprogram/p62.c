//p62.c
#include<stdio.h>

void invA(int a[2][2],double out[2][2]) {
	double detA=a[0][0]*a[1][1]-a[0][1]*a[1][0];
	out[0][0]=(1/detA)*a[1][1];
	out[0][1]=(1/detA)*(-a[0][1]);
	out[1][0]=(1/detA)*(-a[1][0]);
	out[1][1]=(1/detA)*a[0][0];
}

main() {
	int as[2][2]={{1,2},{3,4}},i,j;
	double ou[2][2];
	invA(as,ou);
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			printf("%lf\n",ou[i][j]);
		}
	}
}
