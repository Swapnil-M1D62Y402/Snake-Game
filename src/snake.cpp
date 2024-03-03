#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <raylib.h>
#include "raymath.h"
#define cellSize 30
#define cellCount 25

class Snake{
public:
    int offset  = 75;

    std::deque<Vector2> body = {Vector2{12,11}, Vector2{13,11}, Vector2{14,11} };
    Vector2 direction = {1,0};
    bool AddSegment = false;

    void Draw()
    {
        for(unsigned i = 0; i < body.size(); i++){
            float x = body[i].x;
            float y = body[i].y;
            Rectangle Rec_segment = Rectangle{offset + x*cellSize, offset + y*cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(Rec_segment, 0.5, 6 ,DARKGREEN);
        }
    }
    void Update()
    {      
        //a block will be added everytime but also popped if Addsegment==false
        body.push_front(Vector2Add(body[0], direction));
        if(AddSegment == true)
        {
            AddSegment = false;
        }
        else{
            body.pop_back();
        }
    }

    void Reset()
    {
        body = {Vector2{12,11}, Vector2{13,11}, Vector2{14,11}};
    }

};
#endif //SNAKE_H