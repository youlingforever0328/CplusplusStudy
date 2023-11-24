#include <iostream>
#include <string>
#include "Kvector.h"  //自定义的Kvector
#include "Node.h"      //自定义的类
using std::string;


//测试装入 类类型(Node类) 数据 的Vector
void test_class() {
    std::cout << "==================测试KVector构造函数==================================\n";
    kvector<Node> arr(30);

    std::cout << "==================测试push_back[以move方式]===========================\n";
    for (int i = 0; i < 5; i++) {
        arr.push_back(Node("node_" + std::to_string(i), i, i));  //以move方式添加元素
    }
    arr.Show(); //这里展示全部内存的元素 方便查看完整内容
    //一般只展示cur_length以内的元素 后面的元素是默认构造函数构造的对象

    std::cout << "==================测试 ”获取长度“ 及 ”判断是否为空“ 两个函数=============\n";
    std::cout << "Length: " << arr.Length() << std::endl;
    std::cout << "is Null: " << arr.JudgeNull() << std::endl;

    std::cout << "==================测试自动缩减容量函数==================================\n";
    arr.auto_reduce();  //自动缩减容量
    arr.Show();

    std::cout << "==================测试迭代器=============================================\n";
    for (kvector<Node>::iterator it = arr.begin(); it != arr.end(); ++it)
    {
        std::cout << *it << ", \n"; //需手动重载 类型T 的 << 运算符
    }

    std::cout << "==================测试插入元素[copy方式]=================================\n";
    Node n5 = Node("node_5", 5, 5);
    arr.insert_item(n5, 0);  //以copy方式插入
    arr.Show();

    std::cout << "==================测试插入元素[move方式]=================================\n";
    arr.insert_item(Node("node_6", 6, 6), 2);  //以move方式插入
    arr.Show();

    std::cout << "==================测试删除元素============================================\n";
    arr.delete_item(3);
    arr.Show();

    std::cout << "==================测试重载[ ]运算符和at()函数==============================\n";
    arr[1].show();       //重载[ ]运算符 调用第二个元素(Node)的show方法  这里是元素Node的show()方法，不是vector的Show()
    arr.at(2).show();  //重载at()函数 调用第三个元素(Node)的show方法   这里是元素Node的show()方法，不是vector的Show()

    std::cout << "==================测试清空函数============================================\n";
    arr.Clear();          //清空Kvector并释放所有内存空间
    arr.Show();
}


//测试装入 基本数据类型(int) 数据 的Vector
void test_base() {
    std::cout << "==================测试KVector构造函数==================================\n";
    kvector<int> arr(30);

    std::cout << "==================测试push_back[以copy方式]===========================\n";
    for (int i = 0; i < 5; i++) {
        arr.push_back(i);  //以copy方式添加元素
    }
    arr.Show();//这里展示全部内存的元素 方便查看完整内容
    //一般只展示cur_length以内的元素 后面的元素是默认构造函数构造的对象

    std::cout << "==================测试 ”获取长度“ 及 ”判断是否为空“ 两个函数=============\n";
    std::cout << "Length: " << arr.Length() << std::endl;
    std::cout << "is Null: " << arr.JudgeNull() << std::endl;

    std::cout << "==================测试自动缩减容量函数==================================\n";
    arr.auto_reduce();  //自动缩减容量
    arr.Show();

    std::cout << "==================测试迭代器=============================================\n";
    for (kvector<int>::iterator it = arr.begin(); it != arr.end(); ++it)
    {
        std::cout << *it << ", \n";
    }

    std::cout << "==================测试插入元素[copy方式]=================================\n";
    int n5(5);
    arr.insert_item(n5, 0);  //以copy方式插入
    arr.Show();

    std::cout << "==================测试插入元素[move方式]=================================\n";
    arr.insert_item(int(6), 2);  //以move方式插入
    arr.Show();

    std::cout << "==================测试删除元素============================================\n";
    arr.delete_item(3);
    arr.Show();

    std::cout << "==================测试重载[ ]运算符和at()函数==============================\n";
    std::cout << arr[1] << std::endl;       //重载[ ]运算符
    std::cout << arr.at(2) << std::endl;  //重载at()函数

    std::cout << "==================测试清空函数============================================\n";
    arr.Clear();          //清空Kvector并释放所有内存空间
    arr.Show();
}


int main()
{
    std::cout << "--测试类类型--\n";
    test_class();
    std::cout << "\n\n\n\n--测试基本类型--\n";
    test_base();
}
