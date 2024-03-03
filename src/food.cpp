#ifndef FOOD_H
#define FOOD_H

#include <raylib.h>
#include <raymath.h>
#include <deque>
#define cellSize 30
#define cellCount 25


class Food{
public:
    int offset = 75;
    Vector2 position;
    Texture2D texture;

    Food(std::deque<Vector2> snakeBody)
    {
        Image image = LoadImage("Graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image); //free memory
        position = GenerateRandomPos(snakeBody);
    }
    ~Food()
    { 
        UnloadTexture(texture);  //free the texture 
    }
    void Draw(){
        DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize , WHITE);

    }

    Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, cellCount-1);
        float y = GetRandomValue(0, cellCount-1);
        return Vector2{x,y};
    }

    Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody){
    
        Vector2 position = GenerateRandomCell();

        while(ElementInDeque(position, snakeBody))
        {
            position = GenerateRandomCell();
        }
        return position;
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
#endif  //FOOD_H