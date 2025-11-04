/*
 Problem Statement: 
 create a class 'book' with name, price  and number of pages as it's attributes. The class should contain following member functions : 
  * countBooks(int price) : This function will return count of all the books that have a price less than the given price.

  * isBookPresent(string title) : This will return a boolean value indicating whether any boo with the given title 

 */

#include <iostream>
using namespace std;

class Book{

private:
    // Data members
    string name;
    int price;
    int numberOfPages;

public:
    // Constructor to initialize book details
    Book(string name, int price, int numberOfPages)
    {
        this->name = name;
        this->price = price;
        this->numberOfPages = numberOfPages;
    }

    // Avail the allBooks By Making it Static 
    static vector<Book> allBooks;

    // Static function to work with static variables
    static void addBook(const Book &book){
        allBooks.push_back(book);
    }

    // Member function
    static int countBooks(int p){
        int count = 0;
        for(Book b : allBooks){
            if(b.price < p) count++;
        }

        return count;
    }

    static bool isBookPresent(string title){
        for(Book b : allBooks){
            if(b.name == title) return true;
        }

        return false;
    }
};

// Initialize static member
vector<Book> Book::allBooks;

int main()
{
    // Adding books to the collection
    Book::addBook(Book("Book A", 300, 150));
    Book::addBook(Book("Book B", 500, 200));
    Book::addBook(Book("Book C", 250, 100));

    // Test the functions
    cout << "Count of books with price less than 400: " << Book::countBooks(400) << endl;
    cout << "Is 'Book A' present? " << (Book::isBookPresent("Book A") ? "Yes" : "No") << endl;
    cout << "Is 'Book D' present? " << (Book::isBookPresent("Book D") ? "Yes" : "No") << endl;

    return 0;
}