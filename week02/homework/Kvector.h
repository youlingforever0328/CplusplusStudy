#pragma once
#ifndef KVECTOR_H
#define KVECTOR_H

//����ģ����
template <class T>
class kvector {
	T* elem = nullptr;
	int cur_size;
	int cur_length;
public:
	kvector();                                                                   //Ĭ�Ϲ��캯���������Kvector;
	kvector(int size);                                                       //����ʼ��ֵ�Ĺ��캯���������ʼ��С��Kvector;
	kvector(int size, T& item);                                         //����ʼ��ֵ�Ĺ��캯���������ʼ��С��Kvector;
	~kvector();                                                                
	T& operator[] (int index);                                          //����[]�����;
	T& at(int index);                                                        //����at����;
	int Length();														      //��ȡ����
	bool JudgeNull();													  //�ж��Ƿ�Ϊ��
	void push_back(const T& item);                              //ʹ��copy��ʽ׷��
	void push_back(T&& item);                                      //ʹ��move��ʽ׷��
	void insert_item(const T& item, int index);             //ʹ��copy��ʽ����
	void insert_item(T&& item, int index);                    //ʹ��move��ʽ����
	void delete_item(int index);                                    //ɾ��ָ��Ԫ��
	void Clear();															 //���Ԫ�ز����ͷ�ȫ���ռ�
	void Show();															 //չʾvector
	kvector<T>& auto_reduce();									 //�Զ���������;


	//���������
	class iterator
	{
		int pos;
		T* data;
	public:
		iterator(T* ptr, int idx)
		{
			pos = idx;
			data = ptr;
		}
		iterator()
		{
			pos = 0;
			data = nullptr;
		}
		void operator++() {
			pos++;
		}
		void operator++(int i) {
			pos++;
		}
		void operator--() {
			pos--;
		}
		void operator--(int i) {
			pos--;
		}
		T& operator*()const {
			return data[pos];
		}
		bool operator!=(const iterator& it) {
			return it.pos != pos;
		}
		bool operator==(const iterator& it) {
			return it.pos == pos;
		}
	};

	//��ȡ������;
	iterator begin()
	{
		return iterator(elem, 0);
	}

	iterator begin(int index)
	{
		return iterator(elem, index);
	}

	iterator end()
	{
		return iterator(elem, cur_length);
	}

	iterator end(int index)
	{
		return iterator(elem, index);
	}
};


//����ʵ��

template<class T>
kvector<T>::kvector() {
	cur_size = 0;
	cur_length = 0;
	elem = nullptr;
}

template<class T>
kvector<T>::kvector(int size) {
	cur_size = size;
	try {
		elem = new T[size];
	}
	catch (std::bad_alloc & e) {
		std::cout << e.what() << std::endl;
		exit(-1);
	}
	cur_length = 0;
}

template<class T>
kvector<T>::kvector(int size, T& item) {
	cur_size = size;
	try {
		elem = new T[size];
	}
	catch (std::bad_alloc & e) {
		std::cout << e.what() << std::endl;
		exit(-1);
	}
	for (int i = 0; i < size; i++) {
		elem[i] = item;
	}
	cur_length = size;
}

template<class T>
kvector<T>::~kvector() {
	delete[] elem;
	elem = nullptr;
	cur_size = 0;
	cur_length = 0;
}

template<class T>
T& kvector<T>::operator[] (int index) {
	if (index < 0 || index > cur_length) {
		std::cout << "index error!\n";
		exit(-1);
	}
	return elem[index];
}

template<class T>
T& kvector<T>::at(int index) {
	if (index < 0 || index > cur_length) {
		std::cout << "index error!\n";
		exit(-1);
	}
	return elem[index];
}

template<class T>
int kvector<T>::Length() {
	return cur_length;
}

template<class T>
bool kvector<T>::JudgeNull() {
	return cur_length == 0;
}

template<class T>
void kvector<T>::Clear() {
	if (JudgeNull() == false) {
		for (int i = 0; i < cur_length; i++) {
			elem[i].~T();
		}
		delete[] elem;
		elem = nullptr;

		//���֮��
		cur_size = 0;
		cur_length = 0;
	}
}

template<class T>
void kvector<T>::push_back(const T& item) {
	// �ռ䲻��
	if (cur_length >= cur_size) {
		cur_size = (cur_size == 0 ? 1 : (int)cur_size * 2);
		T* temp = nullptr;
		try {
			temp = new T[cur_size]; 
		}
		catch (std::bad_alloc & e) {
			std::cout << e.what() << std::endl;
			exit(-1);
		}

		for (int i = 0; i < cur_length; i++) {
			temp[i] = elem[i];
		}
		delete[] elem;
		elem = temp;
		std::cout << "[ append ] memory not enough\n";
	}
	elem[cur_length] = item;  //����T�Ŀ�����ֵ����
	cur_length++;
}

template<class T>
void kvector<T>::push_back(T&& item) {
	// ����ռ䲻��
	if (cur_length >= cur_size) {
		cur_size = (cur_size == 0 ? 1 : (int)cur_size * 2);
		T* temp = nullptr;
		try {
			temp = new T[cur_size];
		}
		catch (std::bad_alloc & e) {
			std::cout << e.what() << std::endl;
			exit(-1);
		}

		for (int i = 0; i < cur_length; i++) {
			temp[i] = elem[i];
		}
		delete[] elem;
		elem = temp;
		std::cout << "[ append ] memory not enough\n";
	}
	elem[cur_length] = std::move(item);  //����T���ƶ���ֵ���� ������Tδ�����ƶ���ֵ�����ᱨ��
	cur_length++;
}

template<class T>
void kvector<T>::insert_item(const T& item, int index) {
	if (index < 0 || index > cur_length) {
		std::cout << "insert index error!\n";
		exit(-1);
	}
	// ����ռ䲻��
	if (cur_length >= cur_size) {
		cur_size = (cur_size == 0 ? 1 : cur_size + (int)cur_size * 2);
		T* temp = nullptr;
		try {
			temp = new T[cur_size];
		}
		catch (std::bad_alloc & e) {
			std::cout << e.what() << std::endl;
			exit(-1);
		}

		for (int i = cur_length-1; i >= index; i--) {
			temp[i + 1] = elem[i];
		}
		temp[index] = item;
		delete[] elem;
		elem = temp;
		cur_length++;
		std::cout << "[ insert ] memory not enough\n";
	}
	else {
		for (int i = cur_length - 1; i >= index;i--) {
			elem[i + 1] = elem[i];
		}
		elem[index] = item;
		cur_length++;
	}
}

template<class T>
void kvector<T>::insert_item(T&& item, int index) {
	if (index < 0 || index > cur_length) {
		std::cout << "insert index error!\n";
		exit(-1);
	}
	// ����ռ䲻��
	if (cur_length >= cur_size) {
		cur_size = (cur_size == 0 ? 1 : cur_size + (int)cur_size * 2);
		T* temp = nullptr;
		try {
			temp = new T[cur_size];
		}
		catch (std::bad_alloc & e) {
			std::cout << e.what() << std::endl;
			exit(-1);
		}

		for (int i = cur_length - 1; i >= index; i--) {
			temp[i + 1] = elem[i];
		}
		temp[index] = std::move(item);  //�����ƶ���ֵ����
		delete[] elem;
		elem = temp;
		cur_length++;
		std::cout << "[ insert ] memory not enough\n";
	}
	else {
		for (int i = cur_length - 1; i >= index; i--) {
			elem[i + 1] = elem[i];
		}
		elem[index] = std::move(item);  //�����ƶ���ֵ����
		cur_length++;
	}
}

template<class T>
void kvector<T>::delete_item(int index) {
	if (index < 0 || index > cur_length - 1) {
		std::cout << "delete index error!\n";
		exit(-1);
	}
	elem[index].~T();
	for (int i = index; i < cur_length - 1; i++) {
		elem[i] = elem[i + 1];
	}
	if (cur_size > cur_length) {
		elem[cur_length-1] = elem[cur_length];
	}
	else {
		elem[cur_length - 1].~T();
		cur_size--;
	}
	cur_length--;
}

template<class T>
kvector<T>& kvector<T>::auto_reduce() {
	//���ܿռ������Ԫ�ظ�����5��������ʱ���Զ���������
	if ((int)(cur_size / cur_length) > 5) {
		int reduced_size = (int)cur_length * 2;
		T* temp = nullptr;
		try {
			temp = new T[reduced_size];
		}
		catch (std::bad_alloc & e) {
			std::cout << e.what() << std::endl;
			exit(-1);
		}

		for (int i = 0; i < cur_length; i++) {
			temp[i] = std::move(elem[i]);  //ʹ���ƶ���ֵ
		}
		delete[] elem;
		elem = temp;
		temp = nullptr;
		cur_size = reduced_size;
	}
	return *this;
}

template<class T>
void kvector<T>::Show() {
	std::cout << "---------------Kvector info start------------------\n";
	std::cout << "cur_size: " << cur_size << std::endl;
	std::cout << "cur_length: " << cur_length << std::endl;
	std::cout << "data:\n[\n";
	//����չʾȫ���ڴ��Ԫ�� ����鿴��������
	//һ��ֻչʾcur_length���ڵ�Ԫ�� �����Ԫ����Ĭ�Ϲ��캯������Ķ���
	for (int i = 0; i < cur_size; i++) {
		std::cout << elem[i] << ", \n"; //���ֶ����� ����T �� << �����
	}
	std::cout << "]\n";
	std::cout << "---------------Kvector info end-------------------\n";
}

#endif // !1



