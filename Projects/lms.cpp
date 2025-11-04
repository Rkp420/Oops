#include <iostream>
#include <vector>
#include <string>
#include <ctime>   // For date handling
#include <sstream> // For string manipulation
using namespace std;

// Date Utility Function (to get current date)
string getCurrentDate()
{
    time_t t = time(0);
    tm *now = localtime(&t);
    return to_string(now->tm_year + 1900) + "-" + to_string(now->tm_mon + 1) + "-" + to_string(now->tm_mday);
}

// Helper function to add days to a given date (in string format)
string addDaysToDate(const string &date, int daysToAdd)
{
    int year, month, day;
    stringstream ss(date);
    char delimiter;

    // Parse the current date
    ss >> year >> delimiter >> month >> delimiter >> day;

    // Add the days to the current day
    day += daysToAdd;

    // Handle month overflow
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Handle leap year for February (28 or 29 days)
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        daysInMonth[1] = 29;
    }

    while (day > daysInMonth[month - 1])
    {
        day -= daysInMonth[month - 1];
        month++;

        if (month > 12)
        {
            month = 1;
            year++;
        }
    }

    // Return the new date as a string
    stringstream newDate;
    newDate << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day;
    return newDate.str();
}

// Helper function to calculate the number of days between two dates
int daysBetween(const string &startDate, const string &endDate)
{
    int startYear, startMonth, startDay;
    int endYear, endMonth, endDay;
    stringstream ssStart(startDate), ssEnd(endDate);
    char delimiter;

    // Parse start date
    ssStart >> startYear >> delimiter >> startMonth >> delimiter >> startDay;
    // Parse end date
    ssEnd >> endYear >> delimiter >> endMonth >> delimiter >> endDay;

    // Convert both dates to days since epoch (1970-01-01)
    tm start_tm = {0};
    start_tm.tm_year = startYear - 1900;
    start_tm.tm_mon = startMonth - 1;
    start_tm.tm_mday = startDay;
    time_t startTime = mktime(&start_tm);

    tm end_tm = {0};
    end_tm.tm_year = endYear - 1900;
    end_tm.tm_mon = endMonth - 1;
    end_tm.tm_mday = endDay;
    time_t endTime = mktime(&end_tm);

    // Return the difference in days
    return difftime(endTime, startTime) / (60 * 60 * 24);
}

// Enum for Book Categories
enum BookCategory
{
    Fiction,
    NonFiction,
    Technical,
    Other
};

// Convert Category Enum to String for Display
string categoryToString(BookCategory category)
{
    switch (category)
    {
    case Fiction:
        return "Fiction";
    case NonFiction:
        return "Non-Fiction";
    case Technical:
        return "Technical";
    default:
        return "Other";
    }
}

// Book Class (Updated with Category)
class Book
{
private:
    string title;
    string author;
    int availableCopies;
    BookCategory category;

public:
    Book(string t, string a, int copies, BookCategory cat)
        : title(t), author(a), availableCopies(copies), category(cat) {}

    bool borrow()
    {
        if (availableCopies > 0)
        {
            availableCopies--;
            return true;
        }
        return false;
    }

    void returnBook()
    {
        availableCopies++;
    }

    string getTitle() const { return title; }
    BookCategory getCategory() const { return category; }

    void displayDetails() const
    {
        cout << "Title: " << title << ", Author: " << author
             << ", Available Copies: " << availableCopies
             << ", Category: " << categoryToString(category) << endl;
    }
};

// Borrowed Book Details Structure (Updated to include category)
struct BorrowedBook
{
    string title;
    string borrowDate;
    string dueDate;
    BookCategory category;
    bool returned; // Track if the book is returned
    int fine;      // Fine for overdue books
};

// Base User Class (Updated to account for book category-specific borrow rules)
class User
{
protected:
    string name;
    int userId;
    vector<BorrowedBook> borrowedBooks;

public:
    User(string n, int id) : name(n), userId(id) {}

    virtual void borrowBook(Book &b)
    {
        if (b.borrow())
        {
            BorrowedBook borrowed;
            borrowed.title = b.getTitle();
            borrowed.category = b.getCategory();
            borrowed.borrowDate = getCurrentDate();
            borrowed.returned = false;
            borrowed.fine = 0;

            // Determine borrow duration based on category
            int borrowDuration = 7; // Default borrow duration

            if (borrowed.category == Fiction)
            {
                borrowDuration = 5; // 5 days for Fiction
            }
            else if (borrowed.category == Technical)
            {
                borrowDuration = 10; // 10 days for Technical books
            }

            // Calculate the due date by adding borrow duration to the current date
            borrowed.dueDate = addDaysToDate(borrowed.borrowDate, borrowDuration);
            borrowedBooks.push_back(borrowed);

            cout << name << " borrowed \"" << b.getTitle() << "\" on " << borrowed.borrowDate << " (Category: " << categoryToString(borrowed.category) << "). Due date: " << borrowed.dueDate << endl;
        }
        else
        {
            cout << "No copies available to borrow!" << endl;
        }
    }

    virtual void returnBook(Book &b)
    {
        auto it = find_if(borrowedBooks.begin(), borrowedBooks.end(), [&](const BorrowedBook &book)
                          {
                              return book.title == b.getTitle() && !book.returned; // Only return not yet returned books
                          });

        if (it != borrowedBooks.end())
        {
            // Calculate the fine if the book is overdue
            int overdueDays = daysBetween(it->dueDate, getCurrentDate());
            if (overdueDays > 0)
            {
                it->fine = overdueDays * 5; // Assume 5 units per day fine
                cout << "The book \"" << b.getTitle() << "\" is overdue by " << overdueDays << " days. Fine: " << it->fine << " units." << endl;
            }

            it->returned = true;
            b.returnBook();
            cout << name << " returned \"" << b.getTitle() << "\"." << endl;
        }
        else
        {
            cout << "Book not found in borrowed list!" << endl;
        }
    }

    virtual void displayDetails() const
    {
        cout << "User: " << name << ", ID: " << userId << endl;
        cout << "Borrowed Books: ";
        if (borrowedBooks.empty())
        {
            cout << "None";
        }
        else
        {
            for (const auto &book : borrowedBooks)
            {
                cout << book.title << " (Category: " << categoryToString(book.category) << ", Due: " << book.dueDate;
                if (book.returned)
                {
                    cout << ", Returned";
                }
                else if (book.fine > 0)
                {
                    cout << ", Fine: " << book.fine;
                }
                cout << "), ";
            }
        }
        cout << endl;
    }
};

// Derived Student Class
class Student : public User
{
private:
    static const int maxBorrowLimit = 3;

public:
    Student(string n, int id) : User(n, id) {}

    void borrowBook(Book &b)
    {
        if (borrowedBooks.size() < maxBorrowLimit)
        {
            User::borrowBook(b);
        }
        else
        {
            cout << "Student can borrow up to " << maxBorrowLimit << " books only!" << endl;
        }
    }
};

// Derived Teacher Class
class Teacher : public User
{
public:
    Teacher(string n, int id) : User(n, id) {}

    void borrowBook(Book &b)
    {
        User::borrowBook(b); // Teachers can borrow unlimited books
    }
};

int main()
{
    Book b1("C++ Programming", "Bjarne Stroustrup", 5, Technical);
    Book b2("Harry Potter", "J.K. Rowling", 3, Fiction);
    Book b3("Sapiens", "Yuval Noah Harari", 4, NonFiction);

    Student student1("Alice", 101);
    Teacher teacher1("Bob", 102);

    cout << "Initial Book Details:" << endl;
    b1.displayDetails();
    b2.displayDetails();
    b3.displayDetails();

    cout << "\nBorrowing Books for Student:" << endl;
    student1.borrowBook(b1); // Alice borrows C++ Programming (Technical)
    student1.borrowBook(b2); // Alice borrows Harry Potter (Fiction)

    student1.displayDetails(); // Show student’s borrowed books

    cout << "\nBorrowing Books for Teacher:" << endl;
    teacher1.borrowBook(b1); // Bob borrows C++ Programming (Technical)

    teacher1.displayDetails(); // Show teacher’s borrowed books

    return 0;
}