#ifndef _HELPER_
#define _HELPER_
#include <string.h>
using namespace std;

#define MAX_USER 100
using namespace std;
template <class T>
class arrayList {
public:
	T* list;
	size_t size;
	size_t arrayCapacity;
public:
	arrayList() {
		arrayCapacity = MAX_USER;
		this->list = new T[MAX_USER];
		size = 0;
	}
	arrayList(int capacity) {
		arrayCapacity = capacity;
		this->list = new T[capacity];
		size = 0;
	}
	~arrayList() {
	}
	void removeFromList(int index);
	void removeFromList_(T data);
	void addToList(T newData);
	void modifyListSize();
	bool isEmpty() {
		if (size == 0) {
			return true;
		}
		else return false;
	}
	bool isExist(T data, int&index) {
		for (size_t i = 0; i < size; i++) {
			if (list[i] == data) {
				index = i;
				return true;
			}
		}
		index = -1;
		return false;
	}
	bool isExist(T data) {
		for (size_t i = 0; i < size; i++) {
			if (list[i] == data) {
				return true;
			}
		}
		return false;
	}
	arrayList<T>& operator=(arrayList<T> &r) {
		if (this == &r)return *this;
		this->arrayCapacity = r.arrayCapacity;
		this->size = r.size;
		memcpy(this->list, r.list, size * sizeof(string));
		return *this;
	}
};

template <class T>
void arrayList<T>::modifyListSize() {
	this->arrayCapacity = this->size + 100;
	T* newList = new T[arrayCapacity];
	memmove(newList, this->list, sizeof(T)*size);
	this->list = newList;
}

/// This function addd data at the end of array
template <class T>
void arrayList<T>::addToList(T newData) {
	if (size < arrayCapacity) {
		this->list[size] = newData;
		this->size++;
	}
	if (arrayCapacity - size > 150 || arrayCapacity - size < 10) {
		modifyListSize();
	}
}

template <class T>
void arrayList<T>::removeFromList(int index) {
	memmove(this->list + index, this->list + index + 1, sizeof(T)*size);
	size--;
	if (arrayCapacity - size > 100) {
		modifyListSize();
	}
}
template <class T>
void arrayList<T>::removeFromList_(T data) {
	int index;
	this->isExist(data, index);
	if (index == this->size - 1) {
		size--;
	}
	else if (index != -1) {
		memmove(this->list + index, this->list + index + 1, sizeof(T)*size);
		size--;
	}
	if (arrayCapacity - size > 100) {
		modifyListSize();
	}
}
#endif // _HELPER_