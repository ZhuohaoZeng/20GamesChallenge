#include <iostream>
#include "include/raylib.h"
#include <string>
#include <memory>

struct Bounds
{
    int w, h;
};

struct Input
{
    bool up{};
    bool down{};
};
class Controller {
public:
    virtual Vector2 Move() = 0; 
    virtual ~Controller() = default;
};

class Ball{
public:
    Ball(float x, float y, float r, Color c, Vector2 bs): 
        centerX(x), initX(x), centerY(y), initY(y), radius(r), color(c), ballSpeed(bs){}
    
    Vector2 getPosition() const {return {centerX, centerY};}
    Rectangle getRect() const {return Rectangle{centerX - radius, centerY - radius, 2 * radius, 2 * radius};}
    float getRadius() const {return radius;}
    Color getColor() const {return color;}
    Vector2 getSpeed() const {return ballSpeed;}
    void reflectX() {ballSpeed.x *= -1;}
    void reflectY() {ballSpeed.y *= -1;}
    void moveBy(float ms, float my) {centerX += ms; centerY+= my;}
    void respond() {centerX = initX; centerY = initY;}

    // bool scoreCheck(const paddle& p);

    
private:
    float initX;
    float initY;
    float centerX;
    float centerY;
    float radius;
    Color color;
    Vector2 ballSpeed;
};

class paddle{
public:
    paddle(int posX, int poxY, int width, int height, Color color, Vector2 m, std::unique_ptr<Controller> ctrl = nullptr): 
          posX(posX), posY(poxY), width(width), height(height), color(color), ms(m), controller(std::move(ctrl)){}
    Color getColor() const {return color;}
    Vector2 getMovSpe() const{return ms;}
    Vector2 getPosition() const{return {(float) posX,(float) posY};}
    void setY(float posY){this->posY = posY;}
    void setController(std::unique_ptr<Controller> ctrl) {controller = std::move(ctrl);}
    void setPosition(Vector2 position)
    {
        posX = position.x;
        posY = position.y;
    }
    //Get Move direction from the inputted Controller comonent
    void move() {
        Vector2 m{controller->Move()};
        posX += m.x; posY+= m.y;
        clampY(0, 620);
    }

    void clampY(int minY, int maxY)
    {
        if (posY < minY) posY = minY;
        if (posY > maxY) posY = maxY;
    }
    Rectangle getRect() const{
        return Rectangle{(float) posX, (float) posY, (float) width, (float) height};
    }
private:
    int posX;
    int posY;
    int width;
    int height;
    Color color;
    Vector2 ms;
    std::unique_ptr<Controller> controller;
};

class PlayerController: public Controller {
public:
    PlayerController(paddle& p): pd(p){}
    Vector2 Move() override
    {
        Input in{IsKeyDown(KEY_UP), IsKeyDown(KEY_DOWN)};
        if (in.up) return Vector2{0, -pd.getMovSpe().y};
        else if (in.down) return Vector2{0, pd.getMovSpe().y};
        else return Vector2{0, 0};
    }
private:
    paddle& pd;
};

class EnemyController: public Controller {
public:
    EnemyController(paddle& p, Ball& b): pd(p), ball(b){}
    Vector2 Move() override
    {
        if (ball.getPosition().y > pd.getPosition().y)
        {
            return Vector2{0, pd.getMovSpe().y};
        }
        else if (ball.getPosition().y < pd.getPosition().y) 
        {
            return Vector2{0, -pd.getMovSpe().y};
        }
        else return Vector2{0, 0};
    }
private:
    paddle& pd; 
    Ball& ball; 
};

void checkCollision(Ball& ball, const paddle& p, const Bounds& bounds)
{
    Vector2 ballP = ball.getPosition();
    
    if(ballP.y < 0 || ballP.y > bounds.h){
        ball.reflectY();
    }
    if (CheckCollisionRecs(p.getRect(), ball.getRect()))
    {
        ball.reflectX();
    }
    else if (ballP.x < 0 || ballP.x> bounds.w){
        ball.reflectX();
        ball.respond();
    }
    ball.moveBy(ball.getSpeed().x, ball.getSpeed().y);
}
// balls non-member method
void draw(const Ball& b)
{
    auto [centerX, centerY] = b.getPosition();
    DrawCircle(centerX, centerY, b.getRadius(), b.getColor());
}


// paddles non-member method
void draw(const paddle& p)
{
    Rectangle r = p.getRect();
    DrawRectangleRec(r, p.getColor());
}

int main(void)
{
    int player_score;
    int enemy_score;
    Bounds bounds{1280, 720};
    Vector2 ballSpeed{ 3.0f, 2.0f };
    Ball ball{(float) bounds.w / 2, (float) bounds.h / 2, 30, WHITE, ballSpeed};
    paddle player{70, bounds.h/2, 30, 100, WHITE, {0, 4.0f}};
    player.setController(std::make_unique<PlayerController>(player));
    paddle enemy{1200, bounds.h/2, 30, 100, WHITE, {0, 4.0f}};
    enemy.setController(std::make_unique<EnemyController>(enemy, ball));
    InitWindow(bounds.w, bounds.h, "A new Winodw");
    SetTargetFPS(120); 
    //Main Game Loop
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        player.move();
        draw(player);
        checkCollision(ball, player, bounds);
        checkCollision(ball, enemy, bounds);
        draw(ball);
        enemy.move();
        draw(enemy);
        // if (ball.scoreCheck(player)) ++player_score;
        // if (ball.scoreCheck(enemy)) ++enemy_score;
        // DrawText(TextFormat("%d", player_score), bounds.w/2, bounds.h/2, 20, WHITE);
        DrawLine(bounds.w/2, 0,bounds.w/2, bounds.h, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}