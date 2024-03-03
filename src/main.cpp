#include <raylib.h>
#include <iostream>
#include "game.cpp"
#define offset 75
Color green = {173, 204, 96, 255};


int main()
{
    std::cout<<"starting the game ..."<< "\n";
    InitWindow(2*offset + cellSize*cellCount, 2*offset +cellSize*cellCount, "Retro Snake");
    SetTargetFPS(60);
    Game game;

    //game loop
    while(!WindowShouldClose()){

        BeginDrawing();
        //update the snake position after every 20ms
        if (game.eventTriggered(0.12))
        {
            game.Update();
        }

        game.snakeMovement();

        ClearBackground(green);
        Rectangle rec{(float) offset-5,(float)offset-5, (float)cellSize*cellCount+10, (float)cellSize*cellCount+10};
        DrawRectangleLinesEx(rec, 5, DARKGREEN);
        DrawText("Retro Snake Game ",offset-5, 20, 40, DARKGREEN );
        DrawText("Score: ", offset-5, offset+cellSize*cellCount+10, 40, DARKGREEN);
        DrawText(TextFormat("%i", game.score), offset+150, offset+cellSize*cellCount+10, 40, DARKGREEN);

        //highest score
        DrawText("Highest Score: ", offset+400, offset+cellSize*cellCount+10, 40, DARKGREEN);
        DrawText(TextFormat("%i", game.highest_score), offset+720, offset+cellSize*cellCount+10, 40, DARKGREEN);
        game.Draw();
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}