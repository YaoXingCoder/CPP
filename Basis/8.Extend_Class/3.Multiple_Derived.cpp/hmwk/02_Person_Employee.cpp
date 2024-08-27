/*************************************************************************
    > File Name: 02_Person_Employee.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月26日 星期一 21时38分46秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 基类 派生类
    > Content:
    >   1.定义类Person，包含姓名（char*）、年龄，提供成员函数 display输出信息。
    >   2.类Employee由Person派生，包含部门（char*）、工资, 成员函数display用来输出职工姓名、年龄、部门、工资。
    >   3.要求Employee对象能够进行正确的复制、赋值操作，同时提供计算平均工资的功能。
 ************************************************************************/

#include <string.h>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Person {
public:
    Person(const char* name, const int age) 
    : _name(new char[strlen(name) + 1]())
    , _age(age) 
    {
        strcpy(_name, name);
        cout << "Person(const char*, const int) 有参" << endl;
    }

    /* 拷贝 */
    Person(const Person& rhs) 
    : _name(new char[strlen(rhs._name) + 1]())
    , _age(rhs._age)
    {
        strcpy(_name, rhs._name);
        cout << "Person(const Person&) 拷贝" << endl; 
    }

    /* 赋值 */
    Person& operator=(const Person& rhs) {
        if ( this != &rhs ) {
            delete[] _name;
            _name = nullptr;
            _name = new char[strlen(rhs._name) + 1]();
            strcpy(_name, rhs._name);
            _age = rhs._age;
        }
        return *this;
    }

    /* 析构 */
    ~Person() { 
        if ( _name ) {
            delete[] _name;
            _name = nullptr;
        }
        cout << "~Person 析构" << endl; 
    }
    
    /* 显示信息 */
    void display() const {
        cout << "Person's name is " << _name << ", age is " << _age << endl;
    }
private:

private:
    char* _name;
    int _age;
};

class Employee : public Person {
public:
    /* 构造 */
    Employee( const char* name, const int age, const char* department, const float salary )
    : Person(name, age)
    , _department(new char[strlen(department) + 1]())
    , _salary(salary)
    {
        strcpy(_department, department);
        _totalSalary += salary;
        ++_employeeCount;
        cout << "Employee(name, age, department, salary) 有参" << endl;
    }

    Employee(const Person& person, const char* department, const float salary) 
    : Person(person)
    , _department(new char[strlen(department) + 1]())
    , _salary(salary)
    {
        strcpy(_department, department);
        _totalSalary += salary;
        ++_employeeCount;
        cout << "Employee(person, department, salary) 有参" << endl;
    }

    /* 拷贝 */
    Employee(const Employee& rhs) 
    : Person(rhs)
    , _department(new char[strlen(rhs._department) + 1]())
    , _salary(rhs._salary)
    {
        strcpy(_department, rhs._department);
        _totalSalary += rhs._salary;
        ++_employeeCount;
        cout << "Employee(const Employee&) 拷贝" << endl;
    }

    /* 赋值 
     * 自复制
     * 会自动调基类的析构函数
     * */
    Employee& operator=(const Employee& rhs) {
        if ( this != &rhs ) {
            Person::operator=(rhs);
            delete[] _department;
            _department = nullptr;
            _department = new char[strlen(rhs._department) + 1]();
            strcpy(_department, rhs._department);
            _totalSalary += (rhs._salary - _salary);
            _salary = rhs._salary;
        }
        return *this;
    }

    /* 析构 */
    ~Employee() {
        /* destroy(); */
        if ( _department ) {
            delete[] _department;
            _department = nullptr;
        }
        cout << "~Employee() 析构" << endl;
    }

    static float averageSalary() {
        return ( _employeeCount > 0 ) ? (_totalSalary / _employeeCount) : 0.0;
    }

    void display() const {
        Person::display();
        cout << _department << ", " << _salary << endl;
    }
private:
    char* _department;
    float _salary;
    static int _employeeCount;
    static float _totalSalary;
};
float Employee::_totalSalary = 0.0;
int Employee::_employeeCount = 0;

/* =============== test =============== */
void test0() {
    cout << endl << "====== test0 ======" << endl;

    Person p1("timi", 12);

    Employee em1(Person("tom", 12), "longhu", 8000.00);
    Employee em2(p1, "longhu", 9000.00);

    em2 = em1;

    cout << endl << "====== start ======" << endl;
    em1.display();
    em2.display();

    cout << Employee::averageSalary() << endl;
    cout << endl << "====== end ======" << endl;
}
/* =============== main =============== */
int main (int argc, char* argv[]) {
    test0();
    return 0;
}
