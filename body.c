#include "header.h"

int dance_with_array(const char *filename_input, const char *filename_output){

	FILE *pointer_out;
	FILE *pointer_in;
    
    int amount=0;

	// Заполним структуру
	SmartArray s_array;
	s_array.stringLen = NULL;
	s_array.rowLen = 0;


	// Открываем файл на чтение
	pointer_in	= fopen(filename_input, "r");
	if(pointer_in == NULL){
		return -1;
	}

	// Счёт основной длины
	s_array.rowLen = reading_rowLen(pointer_in);
	if(s_array.rowLen <= 0){
		printf(" The file 'data.txt' is null!\n");
		fclose(pointer_in);

		return -1;
	}
	rewind(pointer_in);

	// Выделяем память для основного массива и массива длин
	s_array.array = (int**)malloc(sizeof(int*)*s_array.rowLen);
	if(s_array.array == NULL){
		printf(" Memory is full!\n");
		fclose(pointer_in);

		return -1;
	}

	s_array.stringLen = (int*)malloc(sizeof(int)*s_array.rowLen);
	if(s_array.stringLen == NULL){
		printf(" Memory is full!\n");

		free(s_array.array);
		fclose(pointer_in);

		return -1;
	}
	
	// Заполнение всего массива нулями, чтобы потом дополнить длины внутренних массивов
	for(int i=0; i<s_array.rowLen; i++){
		s_array.stringLen[i] = 0;
	}

	// Счёт длин строчек массива
	s_array.stringLen = string_len(pointer_in, s_array);

	
	// Задание длин массивам
	for(int i=0; i<s_array.rowLen; i++){
		s_array.array[i] = (int*)malloc(s_array.stringLen[i]*sizeof(int));

		if(s_array.array[i] == NULL){
			free(s_array.array);
			fclose(pointer_in);

			return -1;
		}
	}

	// Заполнение массива числами
	s_array.array = filling_array(pointer_in, s_array);
	// Чтобы не занимать оперативку, закроем файл чтения
	fclose(pointer_in);


	// Функция поиска столбца
	s_array.array = search(s_array);


	for(int i=0; i<s_array.rowLen; i++){
		if(s_array.stringLen[i] != 0){
			amount++;
		}
	}	
	s_array.rowLen = amount;

	// Вывод функции в файл
	pointer_out = fopen(filename_output, "w");

	writing_to_file(pointer_out, s_array);


	for(int i =0; i<s_array.rowLen; i++){
		free(s_array.array[i]);
	}
	free(s_array.array);
	free(s_array.stringLen);

	fclose(pointer_out);

	return 0;
}

// Чтение длины всего массива
int reading_rowLen(FILE *pointer){

	int rowLen = 0;

	char symb;
	int digit;

	int amount = 0;
	int iter_2 = 0;

	int position_first=0;
	int position_sec=0;

	// Если массив пустой, то вернём 0. Если не пуст - есть хотя бы одна строка
	if(fscanf(pointer, "%d", &digit) != 1){
		return 0;
	}
	else{
		rowLen++;
	}
	rewind(pointer);

	// Посчитаем все числа
	while(fscanf(pointer, "%d", &digit)== 1){
		amount++;
	}
	rewind(pointer);
	
	// Определим начальную позицию в файле
	fscanf(pointer, "%d", &digit);
	position_first = ftell(pointer);


	// Далее будет такой цикл: возьмём положение первого числа в файле,  затем будем между каждыми
	// двумя числами смотреть символ '\n', если такие имеются, то значит мы переходим на новую строчку.
	// Однако, если же таких символов больше одного, то значит пропускаются строчки, поэтому мы прибавим к длине только единицу
	for(int i=0; i<amount-1; i++){

		// Перейдём к следующему числу в файле
		fscanf(pointer, "%d", &digit);
		position_sec = ftell(pointer);


		// Переводим ползунок в файле к первому элементу, чтобы проверить все символы между ними
		fseek(pointer, -1*(position_sec - position_first), 1);

		// Найдём между двумя числами символ перехода на новую строку.
		// Если такого символа нет, то числа в одной строке
		for(int j=position_first; j<position_sec; j++){

			fscanf(pointer, "%c", &symb);

			// Считаем количество переходов на новую строку
			if(symb == '\n'){
				iter_2++;
			}
		}

		// Если между числами есть хоть один переход, то строк больше на единицу
		if(iter_2 > 0){
			rowLen++;
		}
		iter_2 = 0;

		position_first = position_sec;
		position_sec = 0;
	}
	rewind(pointer);


	return rowLen;
}

// Чтение длины каждого внутреннего массива
int *string_len(FILE *pointer, SmartArray s_array){

	char symb;

	int digit;

	int position_first = 0;
	int position_sec = 0;

	int amount=0;

	int iter = 0;
	int check = 0;

	char enter='\n';

	// Введём счётчик, чтобы потом распределить все числа
	while(fscanf(pointer, "%d", &digit)==1){
		amount++;
	}
	rewind(pointer);

	// Перейдём сразу к первому числу в файле так, чтобы ползунок был перед ним
	fscanf(pointer, "%d", &digit);

	// Если в массиве одна строчка
	if(s_array.rowLen == 1){
		while(fscanf(pointer, "%d", &digit)==1){
			s_array.stringLen[0] += 1;
		}
		rewind(pointer);

		return s_array.stringLen;
	}
	else{

		for(int i=0; i<s_array.rowLen; i++){
			s_array.stringLen[i]++;
		}

		position_first = ftell(pointer);

		for(int i=0; i<amount-1; i++){

			fscanf(pointer, "%d", &digit);

			position_sec = ftell(pointer);

			fseek(pointer, -1*(position_sec - position_first), 1);

			for(int j = position_first; j<position_sec; j++){
				fscanf(pointer, "%c", &symb);

				if(symb == enter){
					check=1;
				}
			}

			if(check == 0){
				s_array.stringLen[iter]++;
			}
			else{
				iter++;

				check = 0;
			}

			position_first = position_sec;
		}
	}
	rewind(pointer);

	return s_array.stringLen;
}


// Функция заполнения массива
int **filling_array(FILE *pointer, SmartArray s_array){
	
	int digit;

	// Стандартное заполенение массива целыми числами
	for(int i=0; i<s_array.rowLen; i++){
		for(int j=0; j<s_array.stringLen[i]; j++){
			fscanf(pointer, "%d", &digit);
			s_array.array[i][j] = digit;
		}
	}	
	rewind(pointer);

	return s_array.array;
}


// Функция поиска нужного столбца
int **search(SmartArray s_array){

	int sum=0;

	int average_ml = 0;
	int max_lenght=0;
	int index=0;

	int delete=0;

	// Найдём максимальную длину строки, чтобы узнать:
	// имеет ли смысл нам искать столбец в массиве. Если среднее арифметическое
	// самой длинной строки - нецелое число, то просто вернём массив

	for(int i=0; i<s_array.rowLen; i++){
		if(s_array.stringLen[i] >= max_lenght){
			max_lenght = s_array.stringLen[i];
			index = i;
		}
	}


	for(int i=0; i<s_array.stringLen[index]; i++){
		sum += s_array.array[index][i];
	}

	if(sum % max_lenght != 0){
		return s_array.array;
	}
	

	average_ml = sum / max_lenght;

	sum = 0;

	for(int j = 0, iter=0; j<max_lenght; j++){

		if(s_array.array[index][j-iter] == average_ml){	


			delete = check_average_in_column(s_array.array, s_array.rowLen, s_array.stringLen, j-iter);

			if(delete == 0){
		 		s_array.array = delete_column(s_array.array, s_array.rowLen, s_array.stringLen, j-iter);
		 		iter++;
			}
			for(int i=0, len=0; i < s_array.rowLen; i++){
				if(s_array.stringLen[i] != 0){
					len++;
				}
				if(i == s_array.rowLen-1){
					s_array.rowLen = len;
				}
			}
		}
		delete = 0;
	}

	return s_array.array;
}


// Проверка столбца на условие
int check_average_in_column(int **array, int rowLen, int *stringLen, int column){

	int sum = 0;

	// Пробежимся по всему столбцу
	for(int i=0; i < rowLen; i++){

		// Если номер столбца больше, чем номер строчки, то скипнем эту строку
		if(stringLen[i]-1 < column){
			continue;
		}

		// Посчитаем сумму элементов строки
		for(int j=0; j < stringLen[i]; j++){
			sum += array[i][j];
		}

		// Если сумма - нецелое число, то завершаем проверку столбца
		if(sum % stringLen[i] != 0){
			return 1;
		}
		
		// Если элемент в столбце не совпадает со средним арифметическим, то завершаем проверку
		if(sum/stringLen[i] != array[i][column]){
			return 1;
		}

		sum = 0;
	}

	return 0;
}


// Функция удаления столбца из массива
int **delete_column(int **array, int rowLen, int *stringLen, int column){

	// Пробежимся по всему столбцу
	for(int i=0; i<rowLen; i++){

		// Если необходимо удалить столбец, индекс которого больше индекса последнего элемента строки,
		// то пропускаем удаление в этой строке
		if(column > stringLen[i]-1){
			continue;
		}

		// Если удаляем столбец в строке, длина которой равна единице, то просто 
		// передвинем все элементы на единицу
		if(stringLen[i] > 1){
		
			for(int j=column; j<stringLen[i]-1; j++){
				array[i][j] = array[i][j+1];
			}

			stringLen[i]--;

			array[i] = (int*)realloc(array[i], stringLen[i]*sizeof(int));
		}
		// Если удаляем столбец в строке, длина которой единица, то необходимо удалить всю строчку целиком, т.к.
		// после удаления её длина будет равняться нулю. А это равносильно пустой строке
		else{
			// Поэтому все строчки сдвигаем наверх на единицу(не забываем про длины этих строк)
			free(array[i]);
			for(int k=i; k<rowLen-1; k++){
				array[k] = array[k+1];
				stringLen[k] = stringLen[k+1];
			}

			stringLen[rowLen-1] = 0;

			rowLen--;
			array = (int**)realloc(array, sizeof(int*)*rowLen);

			// Обязательно вернёмся к индексу следующей строки, у которой индекс уменьшился на единицу
			i--;
		}
	}

	return array;
}


// Функция запсис в файл
void writing_to_file(FILE *pointer, SmartArray s_array){

	for(int i=0; i<s_array.rowLen; i++){
		for(int j=0; j<s_array.stringLen[i]; j++){
			fprintf(pointer, "%d ", s_array.array[i][j]);
		}
		fprintf(pointer, "%c", '\n');
	}
}

