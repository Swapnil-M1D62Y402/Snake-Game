#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include "food.cpp"
#include "snake.cpp"
#include "raymath.h"
#include <iostream>
using namespace std;

class Game{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    double lastUpdateTime = 0;
    bool running = true;
    int score = 0;
    int highest_score = 0;

    Sound eatfx;
    Sound wallfx;
    Sound bgm;
    Sound menu;

    Game()
    {
        InitAudioDevice();
        eatfx = LoadSound("Sounds/eat.mp3");
        wallfx = LoadSound("Sounds/wall.mp3");
        bgm = LoadSound("Sounds/bgm.mp3");
        menu = LoadSound("Sounds/menu.mp3");
    }
    ~Game()
    {
        UnloadSound(eatfx);
        UnloadSound(wallfx);
        UnloadSound(bgm);
        UnloadSound(menu);
        CloseAudioDevice();
    }
    void Draw()
    {
        food.Draw();
        snake.Draw();
    }

    void Update()
    {
       
        if(running){
            snake.Update();
            CheckCollisionWith_Food();
            CheckCollisionWith_Edges();
            CheckCollisionWith_Tail();
            PlaySound(bgm);   //plays the menu sound but not during the gameplay
        }
    }
    
    //setup a timer to repeat an action after a specified interval
    bool eventTriggered(double interval)
    {
        double currentTime = GetTime();
        if(currentTime - lastUpdateTime >= interval)
        {
            lastUpdateTime = currentTime;
            return true;
        }
        return false;
    }

    void snakeMovement()
    {
        if(IsKeyPressed(KEY_W) && snake.direction.y != 1) //snake moving only up and not down
        {
            snake.direction = {0,-1};
            running = true;
        }
        if(IsKeyPressed(KEY_S) && snake.direction.y != -1) //snake moving only down and not up
        {
            snake.direction = {0,1};
            running = true;
        }
        if(IsKeyPressed(KEY_A) && snake.direction.x != 1) //snake moving only left and not right
        {
            snake.direction = {-1,0};
            running = true;
        }
        if(IsKeyPressed(KEY_D) && snake.direction.x != -1) //snake moving only right and not left
        {
            snake.direction = {1,0};
            running = true;
        }
    }

    //if the snake's head position is equal to food position
    void CheckCollisionWith_Food()
    {
        if(Vector2Equals(snake.body[0], food.position))
        {
            food.position = food.GenerateRandomPos(snake.body);
            snake.AddSegment = true;
            score ++;
            PlaySound(eatfx);
            //PlaySound(bgm);  //plays bgm after player scores but after every score music resets 
        }
    }

    void CheckCollisionWith_Edges()
    {
        //if snake's head gone past right edge or left edge
        if(snake.body[0].x == cellCount || snake.body[0].x == -1)
        {
            GameOver();
        }
        //if snake's head gone past top edge or left bottom
        if(snake.body[0].y == cellCount || snake.body[0].y == -1)
        {
            GameOver();
        }
    }

    //if the snake's head equal to any of its element
    void CheckCollisionWith_Tail()
    {
        deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();
        if(ElementInDeque(snake.body[0], headlessBody))
        {
            GameOver();
        }
    }
    void GameOver()
    {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        running = false;
        if(score > highest_score)highest_score = score;
        score = 0;
        PlaySound(wallfx);
    }

    bool ElementInDeque(Vector2 element, std::deque<Vector2> deque)
    {
        for(unsigned int i = 0; i<deque.size(); i++)
        {
            if(Vector2Equals(deque[i], element))
            {
                return true;
            }
        }
        return false;
    }
};

#endif //GAME_H