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
    void reverseX(){
        bs.x *= -1;
    }
    void reverseY(){
        bs.y *= -1;
    }
    Rectangle getRect()
    {
        return Rectangle{centerX - radius, centerY - radius, centerX + radius, centerY + radius};
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
        // std::cout << posY << std::endl;
        if (IsKeyDown(KEY_UP)){
            posY -= ms.y;
            if (posY < 0){
                posY = 0;
            }
            
        }
        if (IsKeyDown(KEY_DOWN)){
            posY += ms.y;
            if (posY > 620){
                posY = 620;
            }
        }
    }

    Rectangle getRect(){
        return Rectangle{(float) posX, (float) posY, (float) width, (float) height};
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

class enemy : paddle{

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
        if (CheckCollisionRecs(player.getRect(), ball.getRect()))
        {
            ball.reverseX();
        }
        DrawRectangle(1200, height/2, 30, 100, WHITE);
        DrawLine(width/2, 0,width/2, height, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}