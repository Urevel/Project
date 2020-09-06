
#include "Heap.h"
#include <iostream>
#include <iomanip>
using namespace std;

void AAA::Print() //вывод
{
	std::cout << x;
}
int AAA::GetPriority()
{
	return x;
}

namespace heap
{
	Heap Create(int maxsize, CMP(*f)(void*, void*))   // функция создания кучи с заданным максимальным размером и функцией сравнения двух элементов
	{
		return *(new Heap(maxsize, f));	             // создаём новую кучу и возвращаем её (по указытелю на выделенную память получаем кучу и возвращаем её)
	}

	int Heap::Left(int ix)	// функция получения номера левого потомка элемента ix
	{
		return (2 * ix + 1 >= Size) ? -1 : (2 * ix + 1);	// если номер левого потомка выходит за пределы текущего количества элементов в куче, то возвращаем -1, иначе возвращаем номер левого элемента
	}

	int Heap::Right(int ix)	// функция получения номера правого потомка элемента ix
	{
		return (2 * ix + 2 >= Size) ? -1 : (2 * ix + 2);	// если номер правого потомка выходит за пределы текущего количества элементов в куче, то возвращаем -1, иначе возвращаем номер правого элемента
	}

	int Heap::Parent(int ix)	// функция получения номера родительского элемента ix
	{
		return (ix + 1) / 2 - 1;	// возврат номера родительского элемента
	}

	void Heap::Swap(int i, int j)	// функция перестановки двух элементов
	{
		void* buf = Storage[i];      // запоминаем i-тый элемент массивы в буфере buf (Storage - массив элементов произвольного типа)
		Storage[i] = Storage[j];	// на место i-того элемента записываем j-тый
		Storage[j] = buf;           // на место j-того элемента записываем то, что созранили в buf (i-тый элемент)  
	}

	void Heap::Heapify(int ix)	// функция формирования кучи в массиве (ix - номер текущего элемента)
	{
		int l = Left(ix), r = Right(ix), irl = ix;     // irl = ix - переменная для хранения номера нибольшего из трёх элементов (теущего, левого и парвого)
		if (l > 0)
		{
			if (isGreat(Storage[l], Storage[ix]))
				irl = l;

			if (r > 0 && isGreat(Storage[r], Storage[irl]))

				irl = r;

			if (irl != ix)
			{
				Swap(ix, irl);
				Heapify(irl);
			}
		}
	}

	void Heap::Insert(void* x)	// функция вставки элемента в кучу
	{
		int i;
		if (!isFull())
		{
			i = Size;
			Storage[i] = x; //хранение
			Size++;
			while (i > 0 && isLess(Storage[Parent(i)], Storage[i]))       // пока не дойдём до вершины и пока родительский элемент меньше вставленного
			{
				Swap(Parent(i), i);
				i = Parent(i);	// новой позицией вставленного элемента становится позиция родительского элемента
			}
		}
	}

	void* Heap::ExtractMax() //извлечение максимального
	{
		void* rc = NULL;
		if (!isEmpty())
		{
			rc = Storage[0];	// возвращаемый элемент равен нулевому элементу массива
			Storage[0] = Storage[Size - 1];   // на место нулевого элемента массива записываем последний элемент
			Size--;
			Heapify(0);	// перестраиваем кучу начиная с кучи
		}
		Heapify(0);
		return rc;
	}

	void Heap::Scan(int i)	// функция вывода кучи
	{
		int probel = 20;
		std::cout << '\n';
		if (Size == 0)
			std::cout << "Куча пуста";
		for (int u = 0, y = 0, level = 1; u < Size; u++)

		{
			cout << setw(probel + 10) << setfill(' ');

			((AAA*)Storage[u])->Print(); //вывод кучи
			if (u == y)      // если мы дошли до конца текущего уровня (y-номер последнего элемента в текущем уровне)
			{
				level++;
				cout << '\n';
				if (y == 0)	// если текущий уровень нулевой
					y = 2;	// то номер последнего элемента в следующем первом уровне = 2
				else y = pow(2, level) - 2; // иначе расчитываем номер последнего элемента для следующего уровня (level- номер текущего уровня)
			}
			probel /= 2;
		}
		cout << '\n';
	}

	void Heap::DeleteHeap()
	{
		if (!isEmpty()) //если куча непустая, то удаляем все
		{
			Size = 0;
			this->~Heap();
		}
	}

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	void* Heap::ExtractMin() //извлекаем минимальный
	{
		void* rc = nullptr;
		int ind;
		int* print = (int*)Storage[0]; //хранилище
		for (int i = 0; i < Size; i++)
			if (*print > * ((int*)Storage[i]))
			{
				print = (int*)Storage[i];
				ind = i;
			}
		Storage[ind] = Storage[Size - 1];
		Size--;

		Heapify(ind);
		return rc;
	}

	// функция удаление i-ого элемента 
	void* Heap::ExtractI(int i)
	{
		void* rc = NULL;
		if (Size > 0 && i >= 0 && i < Size)
		{
			rc = Storage[i];
			Swap(i, Size - 1);	// переставляем местами удаляемый элемент и последний
			Size--;
		}
		Heapify(0);
		return rc;
	}

	// функция объединения двух куч в одну
	void Heap::Union(Heap& h2)
	{
		while (!h2.isEmpty())		// пока не опустеет вторая куча
			Insert(h2.ExtractMax());
		// извлекаем элемент из второй кучи и вставляем в первую	
	}
}
