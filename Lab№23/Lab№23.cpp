#include <iostream>
#include <ctime>
#include <vector>
#include <stdexcept>

class Vector
{ // Класс Veector
private:
	int* array; 
	int size;

public:
	Vector(int size = 2 + rand() % 9)
	{//  Констркутор, который определяет и инициализирует динамический массив
		array = new int[size];
		this->size = size;

		for(int i = 0; i < size; i++)
			array[i] = rand() % 10;
	}

	~Vector()
	{// Деструктор 
		delete[] array;
	}

	const int Get_size()
	{// Функция возвращающая размер массива
		return size;
	}

	const int& operator [] (int &index)
	{//  Перегрузка оператора []
		return array[index];
	}

	const void print_array()
	{// Функция для вывода массива на экран
		for (int i = 0; i < size; i++)
			std::cout << array[i] << ' ';
	}

};

class RightIterator 
{// Класс Итератор
private:
	std::vector<int>::iterator current;
	std::vector<int>::iterator end;
	size_t index;

public:
	RightIterator(std::vector<int>::iterator begin, std::vector<int>::iterator end, size_t n)
		: current(begin), end(end), index(n) 
	{//  Конструктор с параметрами, который инициализирует поля класса и производит итерацию на указанный индекс
		if (index >= static_cast<size_t>(std::distance(begin, end))) // Проверка на диапозон 
			throw std::out_of_range("Index out of range");

		std::advance(current, n); // Изменяет положение итератора на указаный индекс
	}

	int next() 
	{// Функция, которая возвращает значение индекса итератора, иначе обрабатывает исключение(71 стр)
		if (current != end) 
		{
			int value = *current;
			++current;
			return value;
		}
		else
			throw std::out_of_range("Iterator reached the end");
	}
};

int main()
{
	srand(time(NULL));

	Vector vector(5);
	std::cout << "Full array: ";
	vector.print_array();

	int first_index = rand() % (vector.Get_size());
	int second_index = rand() % (vector.Get_size());
	std::cout << "\nfirst_index: " << first_index << ' ' << "second_index: " << second_index << std::endl;
	std::cout << std::endl << "a[first_index] * b[second_index] = " << vector[first_index] * vector[second_index] << std::endl;

	std::cout << std::endl;

	std::vector<int> test(vector.Get_size());
	for (int i = 0; i < vector.Get_size(); i++)
	{
		test[i] = vector[i];
	}

	int n;
	std::cout << std::endl << "Enter +n: ";
	std::cin >> n;

	try 
	{
		RightIterator it(test.begin(), test.end(), n);

		std::cout << "Current element: " << test[0] << ' ' << "Values to the right of element at index " << n << ": " << it.next() << std::endl;
	}
	catch (const std::out_of_range& e) 
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}