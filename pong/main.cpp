#include <iostream>
#include "include/raylib.h"
#include <string>
//----Below should be in the header files, but I didn't because I am lazy --------
class Ball;
class paddle; 
//----End of the header --------
class Ball{
public:
    Ball(float x, float y, float r, Color c, Vector2 ballSpeed): 
        centerX(x), initX(x), centerY(y), initY(y), radius(r), color(c), bs(ballSpeed){}
    void Move(){
        bounceCheck();
        centerX += bs.x;
        centerY += bs.y;
        DrawCircle(centerX, centerY, radius, WHITE);
    }
    void respond() {
        centerX = initX;
        centerY = initY;
    }
    Vector2 getPosition(){return {centerX, centerY};}
    void reverseX(){
        bs.x *= -1;
    }
    void reverseY(){
        bs.y *= -1;
    }
    bool scoreCheck(const paddle& p);

    Rectangle getRect()
    {
        return Rectangle{centerX - radius, centerY - radius, 2 * radius, 2 * radius};
    }
private:
    float initX;
    float initY;
    float centerX;
    float centerY;
    float radius;
    Color color;
    Vector2 bs;
    void bounceCheck()
    {
        if(centerY < 0 || centerY > 720){
            bs.y *= -1;
        }
        if (centerX < 0 || centerX > 1280){
            bs.x *= -1;
            respond();
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
    Vector2 getMovSpe() const{return ms;}
    Vector2 getPosition() const{return {(float) posX,(float) posY};}
    void setY(float posY){this->posY = posY;}
    void setPosition(Vector2 position)
    {
        posX = position.x;
        posY = position.y;
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

class enemy : public paddle{
public:
    enemy(int posX, int poxY, int width, int height, Color color, Vector2 ms):
    paddle(posX, poxY, width, height, color, ms){}
    void Move(Ball& ball){
        if (ball.getPosition().y > getPosition().y)
        {
            setY(getPosition().y + getMovSpe().y);
        }
        else if (ball.getPosition().y < getPosition().y) 
        {
            setY(getPosition().y - getMovSpe().y);
        }
        Draw();
    }
private:
    
    
};

int main(void)
{
    int player_score;
    int enemy_score;
    int width = 1280;
    int height = 720;
    Vector2 ballSpeed{ 6.0f, 5.0f };
    Ball ball{(float) width / 2, (float) height / 2, 30, WHITE, ballSpeed};
    paddle player{70, height/2, 30, 100, WHITE, {0, 4.0f}};
    enemy enemy{1200, height/2, 30, 100, WHITE, {0, 4.0f}};
    InitWindow(width, height, "A new Winodw");
    SetTargetFPS(120); 
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        player.Draw();
        ball.Move();
        enemy.Move(ball);
        if (CheckCollisionRecs(player.getRect(), ball.getRect()))
        {
            ball.reverseX();
        }
        if (CheckCollisionRecs(enemy.getRect(), ball.getRect()))
        {
            ball.reverseX();
        }
        // if (ball.scoreCheck(player)) ++player_score;
        // if (ball.scoreCheck(enemy)) ++enemy_score;
        DrawText(TextFormat("%d", player_score), width/2, height/2, 20, WHITE);
        DrawLine(width/2, 0,width/2, height, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}