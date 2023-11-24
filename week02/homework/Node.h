#ifndef Node_H
#define Node_H
class Node{
public:
		std::string name;
		int x;
		int y;
public:
		Node();
		Node(std::string, int, int);
		Node(Node&& item);                                 //移动构造函数
		Node(const Node& item);                         //拷贝构造函数
		Node& operator=(Node&& item);             //移动赋值运算符;
		Node& operator=(const Node& item);     //拷贝赋值运算符;
        void show();
		~Node();
friend std::ostream& operator<<(std::ostream&, const Node&); // 使用友元函数重载<<运算符 方便后面的迭代器 cout << *it
};
#endif