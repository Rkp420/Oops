#include <iostream>
using namespace std;

// User Defined data Types
class Player
{
private:
    string name;
    int score;
    int health;

public:
    // Setters
    void setName(string playerName)
    {
        name = playerName;
    }

    void setScore(int s)
    {
        score = s;
    }

    void setHealth(int h)
    {
        health = h;
    }

    // Getters
    string getName()
    {
        return name;
    }

    int getScore()
    {
        return score;
    }

    int getHealth()
    {
        return health;
    }
};

int main()
{

    Player rahul;
    rahul.setName("Rahul Kumar");
    rahul.setScore(100);
    rahul.setHealth(200);

    cout << "Player's Name : " << rahul.getName() << endl;
    cout << "Health is : " << rahul.getHealth() << endl;
    cout << "Score is : " << rahul.getScore() << endl;
    return 0;
}