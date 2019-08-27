#ifndef SNAKE_H_
#define SNAKE_H_
//#include <SFML/Graphics.hpp>

class Food { //class for the food block
public:
    int x;
    int y;
    void newlocation();
    void show(sf::RenderWindow &window);
};

class Head { //class for the head of the snake
public:
    int x;
    int y;
    int dirx;
    int diry;
    int length;
    void update();
    bool overfood(Food food);
    void direction();
    void show(sf::RenderWindow &window);
};

class Body{ //structure for a body block of the snake
public:
int x;
int y;
Body *next;
void show(sf::RenderWindow &window);
};

Body *addtobody(Body *list);
bool hittingwall(Head snake);
bool foodoversnake(Body *body, Food food);
bool headhittingbody(Head head, Body *body,int x, int y);

#endif

