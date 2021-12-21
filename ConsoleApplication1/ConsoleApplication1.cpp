#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <Windows.h>
#include <vector>
#include <string>
#include <conio.h>
#include <cstdlib>

using namespace std;

//Довжина поля ПІБ
const int l_name = 35;
//Структура для зберігання відомостей для одного працівника
struct Student {
	char name[l_name + 1];
	int group;
	int marks[5];

	Student()
	{

	}

	Student(char* name, int group, int marks[]) : group(group) {
		strncpy(this->name, name, l_name);
		int sum = 0;
		for (int i = 0; i < 5; i++) {
			this->marks[i] = marks[i];
		}
	}
};

int compare(const void* str1, const void* str2);
int compare2(const void* y1, const void* y2);
int compare3(const void* s1, const void* s2);
int average(Student* s);
int checkMarks(Student* s);




int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	const char* file_name = "new_students.bin";


	while (true)
	{
		FILE* file;
		file = fopen("new_students.bin", "rb");
		if (file == NULL)
		{
			puts(" Error of opening file!");
			return 1;
		}

		fseek(file, 0, SEEK_END);
		// Підраховуємо кількість записів про студентів в файлі
		int count = ftell(file) / sizeof(Student);

		cout << " Count of Students = " << count << endl;
		// Виділяємо пам'ять під всих студентів
		Student* students = new Student[count];
		// Встановлюємо поточну позицію початку файлу
		fseek(file, 0, SEEK_SET);
		// Зчитування інформації з файлу в масив
		fread(students, sizeof(Student), count, file);
		fclose(file);
		// Сортування масиву структур
		bool ent = true;
		cout << " Please! Press any key to continue or press \"Esc\" to stop program: \n";
		char ch = _getch();
		if (ch == VK_ESCAPE) {
			cout << " Program has been stoped!!" << endl;
			break;
		}
		else
		{

			cout << " Choose what to do:\n 1 - Add new student;\n 2 - Sorting;\n 3 - Show students with marks 4 and 5;\n 4 - Show students;\n";
			int choose1 = 0;
			cin >> choose1;
			if (choose1 == 1)
			{
				FILE* file1;
				file1 = fopen("new_students.bin", "a+b");
				if (file1 == NULL)
				{
					puts(" Error of opening file!");
					return 1;
				}
				cout << " Enter name: ";
				char name[l_name + 1];

				cin.ignore();

				cin.getline(name, sizeof(name));
				//Його групу
				cout << " Enter group of student: ";
				int group;
				cin >> group;
				//Та оцінки
				cout << " Enter marks of student: \n";
				int time_mark[5];
				for (int i = 0; i < 5; i++) {
					int p;
					cout << "\t Enter mark №" << i + 1 << " = ";
					cin >> p;
					time_mark[i] = p;
				}
				//Створюємо обьект структури відповідно до введених даних
				Student newStudent = Student(name, group, time_mark);
				cout << "Новый студент: \n";
				cout << " Name: " << newStudent.name << "\t Group: " << newStudent.group << "\t";
				for (int i = 0; i < 5; i++)
				{
					if (i != 4)
					{
						cout << newStudent.marks[i] << "\t";
					}
					else
					{
						cout << newStudent.marks[i] << endl;
					}
				}
				//Записуємо нового студента в кінець файлу
				fwrite(&newStudent, sizeof(newStudent), 1, file1);
				cout << "\n New Student was added!\n";
				fclose(file1);

			}
			else if (choose1 == 2)
			{
				cout << " Choose sort:\n 1 - by name;\n 2 - by group;\n 3 - by average of marks;\n ";
				int choose2 = 0;
				cin >> choose2;
				if (choose2 == 1)
				{
					qsort(students, count, sizeof(Student), compare);
				}
				else if (choose2 == 2)
				{
					qsort(students, count, sizeof(Student), compare2);
				}
				else if (choose2 == 3)
				{
					qsort(students, count, sizeof(Student), compare3);
				}
				else
				{
					cout << " You enter not correct number!\n";
				}
				for (int i = 0; i < count; i++)
				{
					// Вивід
					printf("%s\t%i\t", students[i].name, students[i].group);
					for (int j = 0; j < 5; j++)
					{
						if (j < 4)
						{
							printf("%i\t", students[i].marks[j]);
						}
						else
						{
							printf("%i\n", students[i].marks[j]);
						}

					}
				}
			}
			else if (choose1 == 3)		// Перевірка на оцінки 4 і 5
			{
				int countGoodMarks = 0;
				for (int i = 0; i < count; i++)
				{
					if (checkMarks(&students[i]) != 5)
					{
						continue;
					}
					else
					{
						printf("%s\t%i\t", students[i].name, students[i].group);
						for (int j = 0; j < 5; j++)
						{
							printf("%i\t", students[i].marks[j]);
						}
						cout << " Average = " << average(&students[i]) << endl;
					}
				}
			}
			else if (choose1 == 4)
			{
				for (int i = 0; i < count; i++)
				{
					printf("%s\t%i\t", students[i].name, students[i].group);
					for (int j = 0; j < 5; j++)
					{
						printf("%i\t", students[i].marks[j]);
					}
					cout << " Average = " << average(&students[i]) << endl;
				}
			}
			else
			{
				cout << " You enter not correct number!!\n\a";
			}
		}
		// Звільнення памяті
		delete[]students;
	}

	system("pause");
	return 0;
}
// Сортування за іменем
int compare(const void* str1, const void* str2)
{
	//Лексиграфічне порівняння двох рядків
	return strcmp(((Student*)str1)->name, ((Student*)str2)->name);
}
// Сортування за групою
int compare2(const void* y1, const void* y2)
{
	int f = 0;
	if ((((Student*)y1)->group < ((Student*)y2)->group))
	{
		f = -1;
	}
	else if ((((Student*)y1)->group == ((Student*)y2)->group))
	{
		f = 0;
	}
	else
	{
		f = 1;
	}

	return f;
}
// Сортування за середнім балом
int compare3(const void* s1, const void* s2)
{
	int f = 0;
	int average1 = 0, average2 = 0;
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < 5; i++)
	{
		sum1 += ((Student*)s1)->marks[i];
		sum2 += ((Student*)s2)->marks[i];
	}
	average1 = sum1 / 5;
	average2 = sum2 / 5;
	if (average1 < average2)
	{
		f = -1;
	}
	else if (average1 == average2)
	{
		f = 0;
	}
	else
	{
		f = 1;
	}

	return f;
}
// Підрахунок середнього бала
int average(Student* s)
{
	int average = 0;
	int sum = 0;
	for (int i = 0; i < 5; i++)
	{
		sum += s->marks[i];
	}
	average = sum / 5;

	return average;
}
// Перевірка на те чи всі оцінки 4 і 5
int checkMarks(Student* s)
{
	int check = 0;
	for (int i = 0; i < 5; i++)
	{
		if (s->marks[i] == 4 || s->marks[i] == 5)
		{
			check++;
		}
	}

	return check;
}
