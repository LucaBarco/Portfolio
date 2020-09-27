
extern int average(int *, int);

int main(void){

	int v[5]={1,2,3,4,5},n=5;
	volatile int r=0;
	
	r = average(v,n);
	
	while(1);
}
