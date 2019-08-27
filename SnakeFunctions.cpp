#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "Snake.h"
#include <windows.h>

void Food::newlocation(){
    x=(rand()%19)*20; //assign the food to have a new random location, but on a desired 20 by 20 grid so the snake and the food align
    y=(rand()%19)*20;
    }
void Food::show(sf::RenderWindow &window){ //show the food on the window
    //setcolor(WHITE);
    //setfillstyle(SOLID_FILL,WHITE);
    sf::RectangleShape foodbody(sf::Vector2f(20,20));
    foodbody.setPosition(x,y);
    foodbody.setOutlineColor(sf::Color::Green);
    foodbody.setFillColor(sf::Color::Green);
    window.draw(foodbody);
    //rectangle(x,y,x+20,y+20); //draw a rectangle on the screen and fill it with white
    //floodfill(x+1,y+1,WHITE);
    }
void Head::update(){
    x=x+dirx*20; //move the head of the snake up, down, left or right by 20 units based on the keys the user presses
    y=y+diry*20;
    }
bool Head::overfood(Food food){
        if(x==food.x&&y==food.y){ //if the head of the snake has the same coordinates as the food, increase the length as a new body part is added and return that it is above food
            length++;
            return true;
        }
        else{
            return false; //if its not above the food, return that
        }
    }
void Head::direction(){
    if(GetAsyncKeyState(0x57)||GetAsyncKeyState(0x26)){ //if they are pressing w or up arrow
        dirx=0;
        diry=-1; //make the snake direction up
    }
    else if(GetAsyncKeyState(0x41)||GetAsyncKeyState(0x25)){ //if they are pressing a or left arrow
        dirx=-1;
        diry=0;//make the snake direction left
    }
    else if(GetAsyncKeyState(0x53)||GetAsyncKeyState(0x28)){ //if they are pressing s or down arrow
        dirx=0;
        diry=1; //make the snake direction down
    }
    else if(GetAsyncKeyState(0x44)||GetAsyncKeyState(0x27)){ //if they are pressing d or right arrow
        dirx=1; //make the snake direction right
        diry=0;
    }
    }
void Head::show(sf::RenderWindow &window){
    /*setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    rectangle(x,y,x+20,y+20); //draw the head and fill it with white
    floodfill(x+1,y+1,WHITE);*/
    sf::RectangleShape headimage(sf::Vector2f(20,20));
    headimage.setPosition(x,y);
    headimage.setOutlineColor(sf::Color::White);
    headimage.setFillColor(sf::Color::White);
    window.draw(headimage);
    }
void Body::show(sf::RenderWindow &window){
    /*setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    rectangle(this->x,this->y,(this->x)+20,(this->y)+20); //draw a rectangle based on the coordinates of the current body block
    floodfill(x+1,y+1,WHITE); //fill it with white*/
    sf::RectangleShape bodypart(sf::Vector2f(20,20));
    bodypart.setPosition(this->x,this->y);
    bodypart.setOutlineColor(sf::Color::White);
    bodypart.setFillColor(sf::Color::White);
    window.draw(bodypart);
}
Body *addtobody(Body *list){
    Body *last;
    last=new Body;
    last->next=list; //add a new body block to the end of the snake
    return last;
}

bool hittingwall(Head snake){
if(snake.x<0||snake.x>=400||snake.y<0||snake.y>=400){//if the snake is outside the window, return that its hitting the wall
    return true;
}
else{ //if its not hitting the wall, return it
    return false;
}
return 0;
}

bool foodoversnake(Body *body, Food food){
Body *too;
too=new Body;
for (too=body; too!=NULL; too=too->next){ //go through all the body blocks in the snake
    if(too->x==food.x||too->y==food.y){ //if the food block has the same position as a body block, return it
        return true;
    }
}
    return false; //if the food is not sharing a position with the body, return it

}
bool headhittingbody(Head head, Body *body,int x, int y){ //test if the head is touching the body
Body *yee;
yee= new Body;

if(head.length==2){ //if theres only the head and one body block
    if(head.x==x&&head.y==y){ //if the head and the body share the same position
    return true; //return it
    }
}

for (yee=body; yee!=NULL; yee=yee->next){//go through all the body blocks
    if(head.x==yee->x&&head.y==yee->y){ //if the head's position has the same position as one of the body blocks, return it
        return true;
    }
}
return false; //if the head isnt touching its body, return it
}

