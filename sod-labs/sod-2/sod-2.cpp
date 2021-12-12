#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

int main() {
	SetConsoleCP(1251); // Використовуємо кодування для коректного відображення українських символів
	SetConsoleOutputCP(1251);

	const int length = 101;

	char key[length];
	char line[length];

	cout << "\tTASK 1\n";
	cout << "Enter search key: "; // Вводимо частину назви міста
	cin >> key;

	ifstream sourceFile1("text_city_UA.txt"); // Вказуємо шлях до файлу
	if (!sourceFile1) { // Якщо файл неможливо відкрити - завершуємо роботу застосунку
		cout << "File can not be opened!\n";
		return true;
	}
	while (sourceFile1.getline(line, length)) // Перебираємо файл по одному рядку
		if (strstr(line, key)) // Перевіряємо рядок на схожість з введеним раніше ключем
			cout << "Match! " << line << " city was found by key: " << key << endl; // Демонструємо що рядки однакові	
	cout << "No more matches found!\n";

	//////////////////////////////////////////
	cout << "\n\tTASK 2\n";

	cout << "Enter search key: "; // Вводимо слово, яке будемо підраховувати
	cin >> key;

	ifstream sourceFile2("Shakespeare_Hamlet.txt"); // Вказуємо шлях до файлу
	if (!sourceFile2) // Якщо файл неможливо відкрити - завершуємо роботу застосунку
	{
		cout << "File can not be opened!\n";
		return true;
	}

	int count = 0; // Оголошуємо лічильник
	char temp[length]; // Оголошуємо змінну для копії рядка
	while (sourceFile2.getline(line, length)) // Перебираємо файл по одному рядку
	{
		strcpy(temp, line); // Створюємо копію поточного рядка у temp
		bool isFound = false; // Оголошуємо змінну, що сигналізує про потрібний рядок
		char* separatedLine = strtok(temp, " .,!?-;"); // Використовуємо функцію strtok для створення лексем
		while (separatedLine != NULL) // Перебираємо лексеми по одному
		{
			if (strcmp(separatedLine, key) == 0) isFound = true; // Порівнюємо лексему зі словом, яке було задано раніше
			separatedLine = strtok(NULL, " .,!?-;");
		}
		if (isFound) // Якщо слово знайдено
		{
			cout << "Line: " << line << endl; // Виводимо результат
			++count; // Застосовуємо інкремент до лічильника
		}
	}
	cout << "Number of occurrences of word " << key << ": " << count << endl;

	//////////////////////////////////////////
	cout << "\n\tTASK 3\n";



	ifstream sourceFile3("Shakespeare_Winter'sTale_UA.txt"); // Вказуємо шлях до файлу
	if (!sourceFile3) // Якщо файл неможливо відкрити - завершуємо роботу застосунку
	{
		cout << "File can not be opened!\n";
		return true;
	}
	while (sourceFile3.getline(line, length)) // Перебираємо файл по одному рядку
	{
		strcpy(temp, line); // Створюємо копію поточного рядка у temp
		char* separatedLine = strtok(temp, " -"); // Використовуємо функцію strtok для створення лексем
		char* tempWord;
		while (separatedLine != NULL) // Перебираємо лексеми по одному
		{
			tempWord = separatedLine; // Створюємо копію першого слова
			separatedLine = strtok(NULL, " -"); // Переходимо до наступного лексему
			if (separatedLine != NULL) // Перевіряємо, чи не дійшли до кінця рядка
				cout << separatedLine << " " << tempWord << " "; // Виводимо друге, потім перше слово
			else
			{
				cout << tempWord << " "; // Виводимо останнє слово, для непарних рядків
				continue; // Якщо, дійшли до кінця рядка, пропускаємо наступний рядок
			}
			separatedLine = strtok(NULL, " -"); // Переходимо до наступного лексему
		}
		cout << endl; // Переходимо до нового рядка	
	}
}