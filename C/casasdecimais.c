#include <stdio.h> 
int main (void){
	double x;
	double t = 0.000000001;
	int i = 1;
	printf("Digite um valor com casas decimais: ");
	scanf("%lf", &x); 
	while (( x - (int) x ) > t) {
		x *= 10;
		i *= 10;
	}
	while (( (int) x % 2 == 0 ) && ( i % 2 == 0 ) || ( (int) x % 5 == 0 ) && ( i % 5 == 0 )){
		if ((int) x % 2 == 0 ){
			x/=2;
			i/=2;
		}
		else if ((int) x % 5 == 0){
			x/=5;
			i/=5;		
		}
	}
	printf("%.0lf/%d", x, i);
	return 0;
}