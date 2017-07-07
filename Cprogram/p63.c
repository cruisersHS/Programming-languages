#include <stdio.h>
#include <stdlib.h>

void kakezan(int a[3][3], int b[3][3], int out[3][3]) {
	int i,j,k;
	for(i=0;i<3;i++) {
		printf("|\t");
		for(j=0;j<3;j++) {
			for(k=0;k<3;k++) {
				out[i][j]=a[i][k]*b[k][j];
			}
			printf("%d\t",out[i][j]);
		}
		printf("|\n");
	}
}
main() {
int a[3][3] = {{9, 8, 7},
		{6, 5, 4},
		{3, 2, 1}};
int b[3][3] = {{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}};
int c[3][3];
kakezan(a,b,c);
}
