#include "main.h"

//Функция интерполяционного поиска
//Предусловие: на вход поступает указатель на ненулевой массив, количество элементов массива, ключ искомого элемента
//Постусловие: функция возвращает индекс элемента в массиве
int interpolation_search(Patient* patients, int n, int key)
{
	int x = 0;
	int a = 0;
	int b = n;
	comparisons += 5;
	while (patients[a].patient_id < key && patients[b].patient_id > key)
	{
		comparisons += 5;
		movements++;
		x = a + ((key - patients[a].patient_id) * (b - a)) / (patients[b].patient_id - patients[a].patient_id);
		comparisons++;
		if (patients[x].patient_id < key)
		{
			movements++;
			a = x + 1;
		}
		else if (patients[x].patient_id > key)
		{
			comparisons++;
			movements++;
			b = x - 1;
		}
		else
		{
			return x;
		}
	}
	comparisons++;
	if (patients[a].patient_id == key)
	{
		return a;
	}
	else if (patients[b].patient_id == key)
	{
		comparisons++;
		return b;
	}
	else
	{
		return -1;
	}
}

//Функция линейного поиска
//Предусловие: на вход поступает указатель на ненулевой массив, количество элементов массива, ключ искомого элемента
//Постусловие: функция возвращает индекс элемента в массиве
int line_search(Patient* patients, long n, long key) {
	comparisons++;
	movements++;
	for (int i = 0; i < n; i++)
	{
		comparisons += 2;
		if (patients[i].patient_id == key)
		{
			movements++;
			return i;
		}
	}
	movements++;
	return -1;
}

//Функция линейного поиска c барьером
//Предусловие: на вход поступает указатель на ненулевой массив, количество элементов массива, ключ искомого элемента
//Постусловие: функция возвращает индекс элемента в массиве
int barrier_search(Patient* patients, long n, long key)
{
	movements += 2;
	patients[n].patient_id = key;
	long i = 0;
	comparisons++;
	while (patients[i].patient_id != key)
	{
		comparisons++;
		movements++;
		i++;
	}
	comparisons++;
	return i < n ? i : -1;
}

//Функция заполнения таблицы случайными данными
void filling_array(Patient* patients, long N)
{
	patients[0].patient_id = rand() % 10;
	patients[0].chronic_disease_id = rand() % 2;
	patients[0].attending_doctor = "text";
	for (long i = 1;i < N;i++)
	{
		patients[i].patient_id = patients[i - 1].patient_id + rand() % 10;
		patients[i].chronic_disease_id = rand() % 10;
		patients[i].attending_doctor = "text";
	}
}

void print_array(Patient* patients, long N)
{
	for (long i = 0;i < N;i++)
	{
		cout << "Пациент поликлиники: " << setw(10) << patients[i].patient_id << setw(10) << patients[i].chronic_disease_id << setw(10) << patients[i].attending_doctor << endl;
	}
}

//Функция тестирования линейного поиска
void test_line_search(long N, Patient*& patients) {
	patients = new Patient[N];

	cout << "Тестирование линейного поиска для массива из " << N << " случайно заполненых структур: " << endl;
	filling_array(patients, N);

	//cout << "Обрабатываемая таблица: " << endl;
	//print_array(patients, N);

	movements = 0;
	comparisons = 0;
	int key = rand() % 100;
	cout << "Искомый пациент с номером карточки: " << key << endl;
	auto begin = std::chrono::steady_clock::now();
	int var = line_search(patients, N, key);
	auto end = chrono::steady_clock::now();
	if (var != -1)
	{
		cout << "Пациент поликлиники: " << setw(10) << patients[var].patient_id << setw(10) << patients[var].chronic_disease_id << setw(10) << patients[var].attending_doctor << endl;
	}
	else
	{
		cout << "Пациент не найден" << endl;
	}
	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;
}

//Функция тестирования линейного поиска c барьером
void test_barrier_search(long N, Patient*& patients) {
	patients = new Patient[N + 1];

	cout << "Тестирование линейного поиска для массива из " << N << " случайно заполненых структур: " << endl;
	filling_array(patients, N);

	//cout << "Обрабатываемая таблица: " << endl;
	//print_array(patients, N);

	movements = 0;
	comparisons = 0;
	int key = rand() % 100;
	cout << "Искомый пациент с номером карточки: " << key << endl;
	auto begin = std::chrono::steady_clock::now();
	int var = barrier_search(patients, N, key);
	auto end = chrono::steady_clock::now();
	if (var != -1)
	{
		cout << "Пациент поликлиники: " << setw(10) << patients[var].patient_id << setw(10) << patients[var].chronic_disease_id << setw(10) << patients[var].attending_doctor << endl;
	}
	else
	{
		cout << "Пациент не найден" << endl;
	}
	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;
}

//Функция тестирования интерполяционного поиска для среднего случая
void test_interpolation_search(long N, Patient*& patients) {
	patients = new Patient[N];

	cout << "Тестирование интерполяционного поиска для массива из " << N << " случайно заполненых структур: " << endl;
	filling_array(patients, N);

	//cout << "Обрабатываемая таблица: " << endl;
	//print_array(patients, N);

	movements = 0;
	comparisons = 0;
	int key = rand() % 100;
	cout << "Искомый пациент с номером карточки: " << key << endl;
	auto begin = std::chrono::steady_clock::now();
	int var = interpolation_search(patients, N, key);
	auto end = chrono::steady_clock::now();
	if (var != -1)
	{
		cout << "Пациент поликлиники: " << setw(10) << patients[var].patient_id << setw(10) << patients[var].chronic_disease_id << setw(10) << patients[var].attending_doctor << endl;
	}
	else
	{
		cout << "Пациент не найден" << endl;
	}
	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;
}

//Функция тестирования интерполяционного поиска для лучшего случая
void test_interpolation_search_asc(long N, Patient*& patients) {
	patients = new Patient[N];

	cout << "Тестирование интерполяционного поиска для массива из " << N << " структур для лучшего случая: " << endl;
	filling_array(patients, N);
	patients[0].patient_id = 1;

	//cout << "Обрабатываемая таблица: " << endl;
	//print_array(patients, N);

	movements = 0;
	comparisons = 0;
	int key = 1;
	cout << "Искомый пациент с номером карточки: " << key << endl;
	auto begin = std::chrono::steady_clock::now();
	int var = interpolation_search(patients, N, key);
	auto end = chrono::steady_clock::now();
	if (var != -1)
	{
		cout << "Пациент поликлиники: " << setw(10) << patients[var].patient_id << setw(10) << patients[var].chronic_disease_id << setw(10) << patients[var].attending_doctor << endl;
	}
	else
	{
		cout << "Пациент не найден" << endl;
	}
	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;
}

//Функция тестирования интерполяционного поиска для худшего случая
void test_interpolation_search_desc(long N, Patient*& patients) {
	patients = new Patient[N];

	cout << "Тестирование интерполяционного поиска для массива из " << N << " структур для худшего случая: " << endl;
	filling_array(patients, N);

	//cout << "Обрабатываемая таблица: " << endl;
	//print_array(patients, N);

	movements = 0;
	comparisons = 0;
	long key = -1;
	cout << "Искомый пациент с номером карточки: " << key << endl;
	auto begin = std::chrono::steady_clock::now();
	int var = interpolation_search(patients, N, key);
	auto end = chrono::steady_clock::now();
	if (var != -1)
	{
		cout << "Пациент поликлиники: " << setw(10) << patients[var].patient_id << setw(10) << patients[var].chronic_disease_id << setw(10) << patients[var].attending_doctor << endl;
	}
	else
	{
		cout << "Пациент не найден" << endl;
	}
	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << "Затраченнное время: " << elapsed_ms.count() << " ms" << endl;
	cout << "C + M = " << movements + comparisons << endl;
}

int main()
{
	setlocale(LC_ALL, "Rus");

	Patient* patients;
	long n;


	//n = 100;
	//test_line_search(n, patients);
	//n = 1000;
	//test_line_search(n, patients);
	//n = 10000;
	//test_line_search(n, patients);
	//n = 100000;
	//test_line_search(n, patients);
	//n = 1000000;
	//test_line_search(n, patients);


	//n = 100;
	//test_barrier_search(n, patients);
	//n = 1000;
	//test_barrier_search(n, patients);
	//n = 10000;
	//test_barrier_search(n, patients);
	//n = 100000;
	//test_barrier_search(n, patients);
	//n = 1000000;
	//test_barrier_search(n, patients);


	n = 100;
	test_interpolation_search(n, patients);
	n = 1000;
	test_interpolation_search(n, patients);
	n = 10000;
	test_interpolation_search(n, patients);
	n = 100000;
	test_interpolation_search(n, patients);
	n = 1000000;
	test_interpolation_search(n, patients);


	n = 100;
	test_interpolation_search_asc(n, patients);
	n = 1000;
	test_interpolation_search_asc(n, patients);
	n = 10000;
	test_interpolation_search_asc(n, patients);
	n = 100000;
	test_interpolation_search_asc(n, patients);
	n = 1000000;
	test_interpolation_search_asc(n, patients);


	n = 100;
	test_interpolation_search_desc(n, patients);
	n = 1000;
	test_interpolation_search_desc(n, patients);
	n = 10000;
	test_interpolation_search_desc(n, patients);
	n = 100000;
	test_interpolation_search_desc(n, patients);
	n = 1000000;
	test_interpolation_search_desc(n, patients);
}