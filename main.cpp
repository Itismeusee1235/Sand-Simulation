#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

using namespace std;
using namespace sf;

void Brush(Grid& grid, Vector2i pos, int type)
{
    Vector2i radius(1, 1);
    for (int i = -radius.x; i <= radius.x ; i++)
    {
        for (int j = -radius.y ; j <= radius.y; j++)
        {
            Vector2i newPos(pos.x + i, pos.y + j);
            grid.AddParticle(newPos, type);
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

    RenderWindow win(VideoMode(resolution.x, resolution.y), "Falling Sand Sim");
    win.setFramerateLimit(60);
    Particle Cursor(particleSize, Vector2i(0,0), Color::Blue);
    Clock clock;
    Grid grid(particleSize, resolution.x/particleSize, resolution.y/particleSize);

    while (win.isOpen())
    {
        float frame_time = clock.restart().asSeconds();
        float fps = 1/frame_time;
       // cout << fps << endl;

        Event ev;

        Vector2i pos = Mouse::getPosition(win);
        pos.x /= particleSize;
        pos.y /= particleSize;
        Cursor.pos = pos;

        grid.DebugType(pos);

        while (win.pollEvent(ev))
        {
            if(ev.type == Event::Closed)
            {
                win.close();
            }

            if(Keyboard::isKeyPressed(Keyboard::S))
            {
                Brush(grid, pos, 1);
            }
            else if (Keyboard::isKeyPressed(Keyboard::W))
            {
                Brush(grid, pos, 2);
            }
            else if (Keyboard::isKeyPressed(Keyboard::I))
            {
                Brush(grid, pos, 3);
            }
            else if (Keyboard::isKeyPressed(Keyboard::G))
            {
                Brush(grid, pos, 4);
            }
            
            else if (Keyboard::isKeyPressed(Keyboard::C))
            {
                ClearBrush(grid, pos);
            }
            
        }

        
        win.clear();
        grid.Update();
        //grid.DebugPrint();

        grid.Draw(win);
        Cursor.Draw(win);
        win.display();
        
    }
    

    return 0;
}

