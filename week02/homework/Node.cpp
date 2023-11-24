#include <iostream>
#include "Node.h"

Node::Node()
{
    name = "------";
    x = 0;
    y = 0;
    std::cout << "default constructor\n";
}

Node::Node(std::string name, int x, int y)
{
    this->name = name;
    this->x = x;
    this->y = y;
}


Node::Node(Node&& item)
{
    name = std::move(item.name);
    x = item.x;
    y = item.y;
    item.name = "";
    std::cout << "move constructor\n";
}


Node::Node(const Node& item)
{
    name = item.name;
    x = item.x;
    y = item.y;
    std::cout << "copy constructor\n";
}


Node::~Node()
{
}


Node& Node::operator=(Node&& item) {
    if (this != &item) {
        name = std::move(item.name);
        x = item.x;
        y = item.y;
        item.name = "";
        std::cout << "move assignment\n";
    }
    return *this;
}


Node& Node::operator=(const Node& item) {
    name = item.name;
    x = item.x;
    y = item.y;
    std::cout << "copy assignment\n";
    return *this;
}

void Node::show()
{
    std::cout << "--------------" << std::endl;
    std::cout << "Node name: " << name << std::endl;
    std::cout << "Node x: " << x << std::endl;
    std::cout << "Node y: " << y << std::endl;
    std::cout << "--------------" << std::endl;
}


//全局重载<<运算符
std::ostream& operator<<(std::ostream& out, const Node& node)
{
    out << "{name: "  << node.name << ", x: " << node.x << ", y: " << node.y << "}";
    return out;
}