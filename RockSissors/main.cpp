#include <iostream>

using namespace std;

class Tool
{
protected:
    int strength;
    char type;
public:
    void setStrength(int set_strength) {strength = set_strength;};
};

class Rock: public Tool
{
public:
    Rock(int strength) : setStrength(strength), type('r') {};
    bool fight(Tool);
};

class Scissors: public Tool
{
    Scissors(int strength) : setStrength(strength), type('s') {};
};

class Paper: public Tool
{
    Paper(int strength) : setStrength(strength), type('p') {};
};

bool Rock::fight(Tool tool)
{
    if (tool.type == 's')
    {
     strength *= 2;
     return true;
    }
    else if (tool.type == 'p')
    {
        strength /= 2;
        return false;
    }
};

bool Scissors::figth(Tool tool)
{
    if (tool.type == 'p')
    {
        strength *= 2;
        return true;
    }
    else if (tool.type == 'r')
    {
        strength /= 2;
        return false;
    }
};

bool Paper::fight(Tool tool)
{
    if (tool.type == 'r')
    {
        strength *= 2;
        return true;
    }
    else if (tool.type == 's')
    {
        strength /= 2;
        return false;
    }
}

int main() {
	// Example main function
	// You may add your own testing code if you like

	Scissors s1(5);
	Paper p1(7);
	Rock r1(15);
	cout << s1.fight(p1) << p1.fight(s1) << endl;
	cout << p1.fight(r1) << r1.fight(p1) << endl;
	cout << r1.fight(s1) << s1.fight(r1) << endl;

	return 0;
}
