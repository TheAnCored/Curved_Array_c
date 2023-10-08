#include "header.h"


int main(void){

	int render=0;


	const char *filename_in = "data.dat";
	const char *filename_out = "data.res";


	if(MainTest()!=0){
		printf(" Test is failed! \n");
        return 0;
	}
	else{
		printf(" Test complete!\n");
	}


	render = dance_with_array(filename_in, filename_out);

	if(render != 0){
		return -1;
	}

	return 0;
}
