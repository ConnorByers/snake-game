#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "Snake.h"
#include <chrono>
#include <thread>
using namespace std;

int main(){

srand ((unsigned int)time(NULL)); //getting a new seed to get random integers

int height=400,width=400; //the height and width of the screen is 400 by 400
sf::RenderWindow window(sf::VideoMode(height, width), "Snake Game");

Head snake; //create the Head of the snake
snake.x=100; //set the location of the snake
snake.y=100;
snake.length=1; //the length of the snake is 1 for now
snake.dirx=0; //no direction for the snake yet
snake.diry=0;
Food food; //create a variable of class food
food.newlocation(); //choose a new random location for the food block
Body *body=NULL; //there is no body yet as its only the head
Body *cur;
int x=0,y=0;

while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(!(!hittingwall(snake)&&snake.length!=51&&!headhittingbody(snake,body,x,y))){ //while the snake isnt hitting the wall, the snake doesnt have the winning length and the snake's head isnt touching its body
            window.close();
        }
        window.clear(); //clear the screen

        if(snake.overfood(food)){ //if the snake is over food
            body=addtobody(body); //add a block to the body
            while((food.x==snake.x&&food.y==snake.y)||foodoversnake(body,food)){ //find a new location for the food that the snake isn't already on
                food.newlocation();
            }
        }
        for (cur=body; cur!=NULL; cur=cur->next){ //update the snake's body's position
            if(cur->next==NULL){ //if its the body block before the head
                x=cur->x; //make the body's coordinates equal to the head'd position
                y=cur->y;
                cur->x=snake.x;
                cur->y=snake.y;
            }
            else{ //if its just another body part, make it equal to the body part that is in front of him's position
                cur->x=(cur->next)->x;
                cur->y=(cur->next)->y;
                }
        }

        for (cur=body; cur!=NULL; cur=cur->next){ //display the body on the window
            cur->show(window);
        }
        food.show(window); //show the food on the window
        snake.direction(); //get the new direction of the snake based on what key user is pressing
        snake.update(); //update the heads position with the new direction
        snake.show(window); //show the head on the window
        window.display();
        int delay;
        if(snake.length>=40){
            delay=75;
        }
        else if(snake.length>=10){
            delay=100;
        }
        else{
            delay=125;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

return 0;
}




