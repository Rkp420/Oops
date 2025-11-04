#include <iostream>
using namespace std;

// Single level Inheritance
class Parent
{
private:
    int ex;

protected:
    int jamin;

public:
    int age;

    void showAge()
    {
        cout << "The Age is :" << this->age << endl;
    }
};

class Child : protected Parent
{
public:
    int friends;

    void showFriends()
    {
        cout << "The Friend are : " << this->friends << endl;
    }
};

// MultiLevel Inheritance
class ChildOfChild : private Child{
    public:
    int something;
};

// Multiple Inheritance
class SomeOne : public Parent , protected Child{

};

// Heirarchichal inheritance : One Parant but Child are more than One
class Child1 : public Parent{

};
class Child2 : protected Parent{

};

// Hybrid Inheritance : There is Two or More types of Inheritance
// If we consider two or more inheritance at a time it becomes hybrid

int main()
{
    Child rahul;
    rahul.friends = 4;
    // rahul.showAge();  --> Inaccessible because it becomes Protected after Inheritance
    rahul.showFriends();
    return 0;
}