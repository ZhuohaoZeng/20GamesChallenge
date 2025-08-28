#include <iostream>
#include "include/raylib.h"

class Ball{
public:
    Ball(float x, float y, float r, Color c, Vector2 ballSpeed): 
        centerX(x), centerY(y), radius(r), color(c), bs(ballSpeed){}
    void Move(){
        bounceCheck();
        centerX += bs.x;
        centerY += bs.y;
        DrawCircle(centerX, centerY, radius, WHITE);
    }
private:
    float centerX;
    float centerY;
    float radius;
    Color color;
    Vector2 bs;

    void bounceCheck()
    {
        if (centerX < 0 ||centerX > 1280){
            bs.x *= -1;
        }
        if(centerY < 0 || centerY > 720){
            bs.y *= -1;
        }
    }
};

class paddle{
public:
    paddle(int posX, int poxY, int width, int height, Color color, Vector2 ms): 
          posX(posX), posY(poxY), width(width), height(height), color(color), ms(ms){}
    void isMove(){
        if (IsKeyDown(KEY_UP)){
            posY -= ms.y;
            if (posY > 670){
                posY = 670;
            }
        }
        if (IsKeyDown(KEY_DOWN)){
            posY += ms.y;
            if (posY < 50){
                posY = 50;
            }
        }
    }
    void Draw(){
        isMove();
        DrawRectangle(posX, posY, width, height, color);
    }
private:
    int posX;
    int posY;
    int width;
    int height;
    Color color;
    Vector2 ms;
};


int main(void)
{
    int width = 1280;
    int height = 720;
    Vector2 ballSpeed{ 5.0f, 4.0f };
    Ball ball{(float) width / 2, (float) height / 2, 30, WHITE, ballSpeed};
    paddle player{70, height/2, 30, 100, WHITE, {0, 4.0f}};
    InitWindow(width, height, "A new Winodw");
    SetTargetFPS(120); 
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        player.Draw();
        ball.Move();
        
        DrawRectangle(1200, height/2, 30, 100, WHITE);
        DrawLine(width/2, 0,width/2, height, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}