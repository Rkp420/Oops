#include <iostream>
using namespace std;

class Student
{
private:
    int age;
    char sec;

public:
    // Constructor's name must be same as Class Name
    // Constructor can be overloaded(E.g of compile Time Polymorphism)
    // Default Constructor
    Student() : age(0), sec('A')
    {
        cout << "Default Constructor called!" << endl;
    }

    // Parameterized Constructor
    Student(int age, char sec = 'A') : age(age), sec(sec)
    {
        cout << "Parameterized Constructor called!" << endl;
    }

    // Copy Constructor (using const reference)
    Student(const Student &s1) : age(s1.age), sec(s1.sec)
    {
        cout << "Copy Constructor called!" << endl;
    }

    // Getters
    int getAge() const
    {
        return age;
    }

    char getSec() const
    {
        return sec;
    }

    // Setters
    void setAge(int age)
    {
        this->age = age;
    }

    void setSec(char sec)
    {
        this->sec = sec;
    }

    // Destructor
    // Called whenever there is an object get out of scope
    // Means there is a function containing an object getting destructed when function scope ends
    ~Student()
    {
        cout << "Destructor called!" << endl;
    }
};

int main()
{
    // Default constructor
    Student s1;

    // Parameterized constructor
    Student s2(20, 'B');
    cout << "Student s2 - Age: " << s2.getAge() << ", Section: " << s2.getSec() << endl;

    // Copy constructor
    Student s3(s2);
    cout << "Student s3 (copied from s2) - Age: " << s3.getAge() << ", Section: " << s3.getSec() << endl;

    // Updating values using setters
    s3.setAge(22);
    s3.setSec('C');
    cout << "Updated Student s3 - Age: " << s3.getAge() << ", Section: " << s3.getSec() << endl;

    return 0;
}