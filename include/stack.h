// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#pragma once

template <class T>
class Stack {
	T* data;
	int size_data;
	int top;
public:
	Stack() {
		size_data = 1;
		top = -1;
		data = new T[size_data];
	}

	Stack(int _size_data) {
		if (_size_data <= 0)
			throw "cannot_create_with_negative_size";
		size_data = _size_data;
		top = -1;
		data = new T[size_data];
	}

	Stack(const Stack<T>& s) {
		T* tmp = new T[s.size_data];
		size_data = s.size_data;
		top = s.top;
		data = tmp;
		for (int i = 0; i <= top; i++)
			data[i] = s.data[i];
	}

	~Stack() {
		delete[] data;
	}

	void push(const T& _data) {
		if (top + 1 == size_data) {
			T* tmp = new T[size_data * 2];
			for (int i = 0; i <= top; i++)
				tmp[i] = data[i];
			delete[] data;
			size_data *= 2;
			data = tmp;
		}
		data[++top] = _data;
	}

	void pop() {
		if (!IsEmpty())
			top--;
		else
			throw "pop_of_empty_stack";
	}

	bool IsEmpty() {
		if (top == -1)
			return true;
		return false;
	}

	void Clear() {
		delete[] data;
		top = -1;
		size_data = 1;
		data = new T[size_data];
	}

	T Top() {
		T tmp;
		if (IsEmpty())
			throw "top_of_empty_stack";
		tmp = data[top];
		return tmp;
	}

	int SizeData() {
		return size_data;
	}
};