#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

using namespace std;
using namespace sf;

float distance(Vector2i a, Vector2i b)
{
    return sqrtf(pow((a.x-b.x), 2) + pow((a.y-b.y), 2));
}

void CircleBrush(Grid& grid, Vector2i pos, int type, bool random=true)
{
    int radius = 4;
    for (int i = -radius; i <= radius ; i++)
    {
        for (int j = -radius ; j <= radius; j++)
        {
            Vector2i newPos(pos.x + i, pos.y + j);
            if(distance(newPos, pos) > radius)
            {
                continue;
            }
            if(type == -1)
            {
                grid.DeleteParticle(newPos);
            }
            else
            {
                if(rand()%4 < 3 && random)
                {
                    continue;
                }
                grid.AddParticle(newPos, type);
            }
        }
        
    }
    
}
void SquareBrush(Grid& grid, Vector2i pos, int type, bool random=true)
{
    int radius = 2;
    for (int i = -radius; i <= radius ; i++)
    {
        for (int j = -radius ; j <= radius; j++)
        {
            Vector2i newPos(pos.x + i, pos.y + j);
            if(type == -1)
            {
                grid.DeleteParticle(newPos);
            }
            else
            {
                if(rand()%4 < 3 && random)
                {
                    continue;
                }
                grid.AddParticle(newPos, type);
            }
        }
        
    }
    
}
void ClearBrush(Grid& grid, Vector2i pos)
{
    Vector2i radius(2, 2);
    for (int i = -radius.x; i <= radius.x ; i++)
    {
        for (int j = -radius.y ; j <= radius.y; j++)
        {
            Vector2i newPos(pos.x + i, pos.y + j);
            grid.DeleteParticle(newPos);
        }
        
    }
    
}

int main()
{
    int particleSize = 5;
    Vector2i resolution(1000, 1000);
    int brushMode = 1;
    int brushType = 1;

    RenderWindow win(VideoMode(resolution.x, resolution.y), "Falling Sand Sim");
    win.setFramerateLimit(60);
    Particle Cursor(particleSize, Vector2i(0,0), Color::Blue);
    Clock clock;
    Grid grid(particleSize, resolution.x/particleSize, resolution.y/particleSize);
    RectangleShape brushColorSquare(Vector2f(25,25));
    CircleShape brushColorCircle(12.5);
    brushColorSquare.setPosition(Vector2f(975, 0));
    brushColorSquare.setFillColor(Color::Yellow);
    brushColorCircle.setPosition(Vector2f(975, 0));
    brushColorCircle.setFillColor(Color::Yellow);

    while (win.isOpen())
    {
        float frame_time = clock.restart().asSeconds();
        float fps = 1/frame_time;
        //cout << fps << endl;

        Event ev;

        Vector2i pos = Mouse::getPosition(win);
        pos.x /= particleSize;
        pos.y /= particleSize;
        Cursor.pos = pos;


        while (win.pollEvent(ev))
        {
            if(ev.type == Event::Closed)
            {
                win.close();
            }
            else if (ev.type == Event::KeyPressed)
            {
                if(ev.key.code == Keyboard::Q)
                {
                    win.close();
                }
                else if (ev.key.code == Keyboard::BackSpace)
                {
                    grid.Empty();
                }
                else if (ev.key.code == Keyboard::Tab)
                {
                    brushType = brushType*2 % 3;
                }
                
                else if (ev.key.code == Keyboard::S)
                {
                    brushMode = 1;
                    brushColorSquare.setFillColor(Color::Yellow);
                    brushColorCircle.setFillColor(Color::Yellow);
                }
                else if (ev.key.code == Keyboard::W)
                {
                    brushMode = 2;
                    brushColorSquare.setFillColor(Color::Cyan);
                    brushColorCircle.setFillColor(Color::Cyan);
    
                }
                else if (ev.key.code == Keyboard::I)
                {
                    brushMode = 3;
                    brushColorSquare.setFillColor(Color::Red);
                    brushColorCircle.setFillColor(Color::Red);
                }
                else if (ev.key.code == Keyboard::G)
                {
                    brushMode = 4;
                    brushColorSquare.setFillColor(Color::White);
                    brushColorCircle.setFillColor(Color::White);
                }
                
                else if (ev.key.code == Keyboard::C)
                {
                    brushMode = -1;
                    brushColorSquare.setFillColor(Color(125, 125, 125));
                    brushColorCircle.setFillColor(Color(125, 125, 125));
                }
                
                
            }
            
            if(Mouse::isButtonPressed(Mouse::Left))
            {
               
                bool b = brushMode == 3 ? false : true;
                if(brushType == 1)
                {
                    SquareBrush(grid, pos, brushMode, b);
                }
                else if (brushType == 2)
                {
                    CircleBrush(grid, pos, brushMode, b);
                }
                    
            }
            
        }

        
        win.clear();
        grid.Update();
        grid.Draw(win);
        Cursor.Draw(win);
        if(brushType == 1)
        {
            win.draw(brushColorSquare);
        }
        else if (brushType == 2)
        {
            win.draw(brushColorCircle);
        }
        
        win.display();
        
    }
    

    return 0;
}

