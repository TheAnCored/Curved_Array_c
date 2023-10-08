#include "header.h"


// // Тест, который проверяет правильное считывание длин массивов
// int ReadingTest(void){
//    	
//    	//FILE *pointer_test_write;
//    	FILE *pointer_test_read;
// 
//    	SmartArray test_array;
// 
//    	/*pointer_test_write = fopen("test_data.dat", "w");
// 
//    	for(int i=0; i<10; i++){
//    		for(int j=0; j<5; j++){
//    			if(i == 3 && j == 3){
//    				fprintf(pointer_test_write, "%d", 2);
//    				break;
//    			}
//    			else{
//    				fprintf(pointer_test_write, "%d", 1);
//    			}
//    			fprintf(pointer_test_write, "%c", ' ');
//    		}
//    		fprintf(pointer_test_write, "%c", '\n');
//    	}
// 
//    	fclose(pointer_test_write);*/
// 
//    	pointer_test_read = fopen("test_data.dat", "r");
// 
//    	test_array.rowLen = reading_rowLen(pointer_test_read);
// 
//    	// Определим размер массива с длинами внутренних массивов
//    	test_array.stringLen = (int*)malloc(sizeof(int)*test_array.rowLen);
// 
// 
//    	// Заполним длинами массив
//    	test_array.stringLen = string_len(pointer_test_read, test_array);
//     
//     printf("rowlen: %d\n", test_array.rowLen);
//     for(int i=0; i<test_array.rowLen;i++){
//         printf(" %d\n", test_array.stringLen[i]);
//     }
//     
//    	if(test_array.stringLen[3] != 4){
//    		free(test_array.stringLen);
//    		fclose(pointer_test_read);
//        
//    		return 1;
//    	}
// 
// 
// 
//    	free(test_array.stringLen);
//    	fclose(pointer_test_read);
// 
// 	return 0;
// }

// Тест, проверяющий правильное удаление столбца
int DeleteTest(void){

	int rowLen = 4;
	int lenght_of_array[]={1, 2, 3, 4};
    
    SmartArray test_array;
    

	test_array.array = (int**)malloc(sizeof(int*)*rowLen);
    test_array.rowLen = rowLen;
    test_array.stringLen = lenght_of_array;

	for(int i=0; i<4; i++){
		test_array.array[i] = (int*)malloc(sizeof(int)*(i+1));
	}

	for(int i=0; i<4; i++){
		for(int j=0; j<=i; j++){
			test_array.array[i][j] = 1;
		}
	}

	test_array.array[2][1] = 2;
	test_array.array[2][2] = 0;


	test_array.array = search(test_array);


	if(test_array.array[1][0] != 2){
		for(int i=0; i<2; i++){
			free(test_array.array[i]);
		}

		free(test_array.array);
        
		return 1;
	}


	for(int i=0; i<3; i++){
			free(test_array.array[i]);
		}

	free(test_array.array);


	return 0;
}

// Главный тест
int MainTest(void){

// 	if(ReadingTest() != 0){
// 
// 		return 1;
// 	}

	if(DeleteTest() != 0){
		return 1;
	}

	return 0;
}
