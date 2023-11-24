#pragma once
#ifndef KVECTOR_H
#define KVECTOR_H

//定义模板类
template <class T>
class kvector {
	T* elem = nullptr;
	int cur_size;
	int cur_length;
public:
	kvector();                                                                   //默认构造函数，构造空Kvector;
	kvector(int size);                                                       //带初始化值的构造函数，构造初始大小的Kvector;
	kvector(int size, T& item);                                         //带初始化值的构造函数，构造初始大小的Kvector;
	~kvector();                                                                
	T& operator[] (int index);                                          //重载[]运算符;
	T& at(int index);                                                        //重载at函数;
	int Length();														      //获取长度
	bool JudgeNull();													  //判断是否为空
	void push_back(const T& item);                              //使用copy方式追加
	void push_back(T&& item);                                      //使用move方式追加
	void insert_item(const T& item, int index);             //使用copy方式插入
	void insert_item(T&& item, int index);                    //使用move方式插入
	void delete_item(int index);                                    //删除指定元素
	void Clear();															 //清空元素并且释放全部空间
	void Show();															 //展示vector
	kvector<T>& auto_reduce();									 //自动缩减容量;


	//定义迭代器
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

	//获取迭代器;
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


//函数实现

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

		//清空之后
		cur_size = 0;
		cur_length = 0;
	}
}

template<class T>
void kvector<T>::push_back(const T& item) {
	// 空间不足
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
	elem[cur_length] = item;  //调用T的拷贝赋值函数
	cur_length++;
}

template<class T>
void kvector<T>::push_back(T&& item) {
	// 数组空间不足
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
	elem[cur_length] = std::move(item);  //调用T的移动赋值函数 若类型T未定义移动赋值函数会报错
	cur_length++;
}

template<class T>
void kvector<T>::insert_item(const T& item, int index) {
	if (index < 0 || index > cur_length) {
		std::cout << "insert index error!\n";
		exit(-1);
	}
	// 数组空间不足
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
	// 数组空间不足
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
		temp[index] = std::move(item);  //调用移动赋值函数
		delete[] elem;
		elem = temp;
		cur_length++;
		std::cout << "[ insert ] memory not enough\n";
	}
	else {
		for (int i = cur_length - 1; i >= index; i--) {
			elem[i + 1] = elem[i];
		}
		elem[index] = std::move(item);  //调用移动赋值函数
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
	//当总空间个数是元素个数的5倍及以上时，自动缩减容量
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
			temp[i] = std::move(elem[i]);  //使用移动赋值
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
	//这里展示全部内存的元素 方便查看完整内容
	//一般只展示cur_length以内的元素 后面的元素是默认构造函数构造的对象
	for (int i = 0; i < cur_size; i++) {
		std::cout << elem[i] << ", \n"; //需手动重载 类型T 的 << 运算符
	}
	std::cout << "]\n";
	std::cout << "---------------Kvector info end-------------------\n";
}

#endif // !1



