#include "../../header/Item.hpp"
using namespace std;

Item::Item()
{
    id = 0;
    code = "";
    name = "";
    type = "";
    price = 0;
}

Item::Item(int id, string code, string name, string type, int price)
    : id(id), code(code), name(name), type(type), price(price) {}

Item::~Item() {}

Item::Item(const Item &other)
    : id(other.id), code(other.code), name(other.name), type(other.type), price(other.price) {}

bool Item::isEmpty()
{
    return id == 0 && code.empty() && name.empty() && type.empty() && price == 0;
}

ostream &operator<<(ostream &os, const Item &item)
{
    os << item.code;
    return os;
}
bool operator==(const Item &a, const Item &b)
{
    return a.id == b.id && a.code == b.code && a.name == b.name &&
           a.type == b.type && a.price == b.price;
}

int Item::getID()
{
    return id;
}

string Item::getCode()
{
    return code;
}

string Item::getName()
{
    return name;
}

string Item::getType()
{
    return type;
}

int Item::getPrice()
{
    return price;
}

void Item::setID(int id)
{
    this->id = id;
}

void Item::setCode(string code)
{
    this->code = code;
}

void Item::setName(string name)
{
    this->name = name;
}

void Item::setType(string type)
{
    this->type = type;
}

void Item::setPrice(int price)
{
    this->price = price;
}
