#include <iostream>
#include "ArrayInt.h"
#include <string>

using std::cout;
using std::endl;

int main()
{
	try
	{
		//ArrayInt array1(-1);											// Проверка инициализации контейнера отрицательным значением
		ArrayInt<int> array1(10);
		for (int i(0); i < array1.getLength(); i++)
			array1[i] = i * 2;

		cout << "Array1(int): " << array1 << endl;
		cout << "Array1(int) size: " << array1.getLength() << endl;
		//cout << "Array:\n" << array1[11] << endl;						    // Проверка контейнера на выход за пределы диапазона

		ArrayInt<int> array2(array1);										// Инициализация одного контейнера другим
		cout << "Array2(int): " << array1 << endl;
		cout << "Array2(int) size: " << array2.getLength() << endl;

		// array1.resize(-1);												// Проверка некорректного изменения размера контейнера
		array1.resize(7);													// Изменение размера контейнера
		cout << "Array1(int) after resize: " << array1 << endl;
		cout << "Array1(int) size: " << array1.getLength() << endl;

		array1.resize(10);
		cout << "\nArray1(int) after resize: " << array1 << endl;
		cout << "\nArray1(int) size: " << array1.getLength() << endl;

		array2.copyContainerTo(array1);										// Копирование контейнера при одинаковых размерах
		cout << "\nArray1(int) after copy from Array2: ";
		for (int i(0); i < array1.getLength(); i++)
			cout << array1[i] << " ";
		cout << "\nArray1(int) size: " << array1.getLength() << endl;

		// array1.findElement(145);											// Проверка поиска элемента по некорректному индексу
		array1.findElement(5);

		//array1.insertBefore(100, 100);									// Проверка вставки элемента в контейнер перед некорректным индексом
		array1.insertBefore(100, 5);
		cout << "\nArray1(int) after insert: ";
		for (int i(0); i < array1.getLength(); i++)
			cout << array1[i] << " ";
		cout << "\nArray1(int) size: " << array1.getLength() << endl;

		//array1.remove(100);												// Проверка удаления элемента с некорректным индексом
		array1.remove(7);
		cout << "\nArray1(int) after remove: ";
		for (int i(0); i < array1.getLength(); i++)
			cout << array1[i] << " ";
		cout << "\nArray1(int) size: " << array1.getLength() << endl;

		array1.insertAtBeginning(73);
		cout << "\nArray1(int) after insert: ";
		for (int i(0); i < array1.getLength(); i++)
			cout << array1[i] << " ";
		cout << "\nArray1(int) size: " << array1.getLength() << endl;

		array1.insertAtEnd(37);
		cout << "\nArray1(int) after insert: ";
		for (int i(0); i < array1.getLength(); i++)
			cout << array1[i] << " ";
		cout << "\nArray1(int) size: " << array1.getLength() << endl;

		array1.erase();
		cout << "\nArray1(int) after erase: ";
		for (int i(0); i < array1.getLength(); i++)
			cout << array1[i] << " ";
		cout << "\nArray1(int) size: " << array1.getLength() << endl;

		array2.erase();
		cout << "\nArray2(int) after erase: ";
		for (int i(0); i < array2.getLength(); i++)
			cout << array2[i] << " ";
		cout << "\nArray2(int) size: " << array2.getLength() << endl;

		ArrayInt<std::string> array3(3);
		array3[0] = "First";
		array3[1] = "Second";
		array3[2] = "Third";
		cout << "Array3(string): " << array3 << endl;
		array3.remove(2);
		cout << "Array3(string): " << array3 << endl;
		array3.erase();

		ArrayInt<double> array4(5);
		ArrayInt<double> array5;
		for (int i(0); i < 5; i++)
			array4[i] = 2.5 * (i + 1.0);
		cout << "Array4(double): " << array4 << endl;
		array4.insertAtBeginning(6.4);
		cout << "Array4(double) after insert: " << array4 << endl;
		cout << "Array5(double): " << array5 << endl;
		array5 = array4;
		cout << "Array5(double) after array5 = array4: " << array5 << endl;
		array4.erase();
		array5.erase();
		cout << "\nArray4 after erase: " << array4 << endl;
		cout << "\nArray5 after erase: " << array5;
	}
	catch (bad_length& bl)
	{
		cout << "\nbad_length caught!" << endl;
		cout << bl.what() << endl;
	}
	catch (bad_range& br)
	{
		cout << "\nbad_range caught!" << endl;
		cout << br.what() << endl;
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}
}
