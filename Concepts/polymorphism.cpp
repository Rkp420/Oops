#include <iostream>
using namespace std;

// Polymorphism : Two types
/*
--> CompileTime Poly
        --> Function and Operator Overloading

--> Runtime Poly
        --> Function and Operator Overriding
*/

// Example of Function OverLoading
class SomeThing{
    public:
    int age;

    public:

    void show(){
        cout << "I am the Show without Parameter"<< endl;
    }

    void showAge(SomeThing &s){
        cout << "I am the show with Object of Something" << endl;
    }
};

// Example of Operator Overloading 
class Complex{
    
    double real, imag;

    public:
        // Initialisation list
        Complex(double r, double i) : real(r), imag(i) {};

        // Complex(double r, double i){
        //     cout << "Constructor Call hua hai" << endl;
        //     this->real = r;
        //     this->imag = i;
        // }

        // Operator overloading
        Complex operator +(const Complex &c){
            return Complex(real + c.real, imag + c.imag);
        }

        void display(){
            cout << real << " + " << imag << "i" << endl;
        }
};

int main()
{
    Complex c1(4, 5), c2(6, 7);
    c1.display();
    c2.display();
    Complex c3 = c1 + c2;
    
    c3.display();
    return 0;
}   