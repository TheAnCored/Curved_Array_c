#include <stdlib.h>
#include <stdio.h>


// Логика выполнения задачи такая: 
// 1. Найдём длину всего массива
// 2. Найдём длину всех строк и запишем в массив длин
// 3. Запишем все значения в массив
// 4. Преобразуем по условию
// 5. Выведем в файл преобразованный массив


// Структура с двумерным массивом
typedef struct SmartArray{
	
	int **array;
	int *stringLen;
	int rowLen;

}SmartArray;


// Главная функция
int dance_with_array(const char *filename_input, const char *filename_output);


// Функция считывания длины всего массива
int reading_rowLen(FILE *pointer);


// Функция считывания длин строк
int *string_len(FILE *pointer, SmartArray s_array);


// Функция, читающая все значения массива
int **filling_array(FILE *pointer, SmartArray s_array);


// Функция поиска столбца, удовлетворяюшие условию
int **search(SmartArray s_array);


// Функция, которая считает сренее арифметическое в столбце и сравнивает с элементом
int check_average_in_column(int **array, int lenght_of_array, int *strings_lenght, int column);


// Функция, удаляющая столбец массива
int **delete_column(int **array, int lenght_of_array, int *strings_lenght, int column);


// Функция, записывающая в файл
void writing_to_file(FILE *pointer, SmartArray s_array);



//----------------------------------------
// Функции с тестами
int MainTest(void);

// Проверка считывания массива
int ReadingArray(void);

int DeleteTest(void);
int ReadingTest(void);
