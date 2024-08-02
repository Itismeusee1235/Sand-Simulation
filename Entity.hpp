#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace sf;
using namespace std;

class Grid;

class Particle
{
  public:
  int type;
  int size;
  Vector2i pos;
  RectangleShape shape;

  public:
  Particle(int size, Vector2i pos, Color color = Color::Black)
  {
    type = 0;
    this->size = size;
    this->pos = pos;
    this->shape.setFillColor(color);
    this->shape.setSize(Vector2f(size, size));
  }
  virtual void Update(Particle*** grid, int xLimit, int yLimit)
  {

  }
  void Swap(Particle *** grid, int a, int b, int c, int d)
  {
    Particle* temp = grid[b][a];
    grid[b][a] = grid[d][c];
    grid[d][c] = temp;
    grid[b][a]->pos.x = a;
    grid[b][a]->pos.y = b;
    grid[d][c]->pos.x = c;
    grid[d][c]->pos.y = d;

  }
  void Draw(RenderWindow& window)
  {
    Vector2f screenPosition(size*pos.x, size*pos.y);

    this->shape.setPosition(screenPosition);
    window.draw(this->shape);
  }
};

class Sand : public Particle
{
  public:
  Sand(int size, Vector2i pos) : Particle(size, pos, Color::Yellow)
  {
    this->type = 1;
  }
  void Update(Particle*** grid, int xLimit, int yLimit)
  {
    int x = this->pos.x;
    int y = this->pos.y;

    if(y < (yLimit-1))
    {
      if(grid[y+1][x]->type != 1 && grid[y+1][x]->type != 3)
      {
        Swap(grid, x, y, x, y+1);
      }
      else if (x < (xLimit-1) && grid[y+1][x+1]->type != 1  && grid[y+1][x+1]->type != 3)
      {
        Swap(grid, x, y, x+1, y+1);
      }
      else if (x > 0 && grid[y+1][x-1]->type != 1 && grid[y+1][x-1]->type != 3)
      {
        Swap(grid, x, y, x-1, y+1);
      }
      
    }       
  }
};

class Water : public Particle
{
  public:
  Water(int pSize, Vector2i pos) : Particle(pSize, pos, Color::Cyan)
  {
    this->type = 2;
  }

  void Update(Particle*** grid, int xLimit, int yLimit)
  {
    int x = this->pos.x;
    int y = this->pos.y;

    if(y >= yLimit - 1)
    {
      if (x < (xLimit-1) && grid[y][x+1]->type != 1 && grid[y][x+1]->type != 2 && grid[y][x+1]->type != 3 && x > 0 && grid[y][x-1]->type != 1 && grid[y][x-1]->type != 2 && grid[y][x-1]->type != 3)
      {
        int dif = rand()%2 == 1? 1 : -1;
        Swap(grid, x, y, x+ dif, y);
      }
      
      else if (x < (xLimit-1) && grid[y][x+1]->type != 1 && grid[y][x+1]->type != 2 && grid[y][x+1]->type != 3)
      {
        Swap(grid, x, y, x+1, y);
      }

      else if (x > 0 && grid[y][x-1]->type != 1 && grid[y][x-1]->type != 2 && grid[y][x-1]->type != 3)
      {
        Swap(grid, x, y, x-1, y);
      }
    }
    else
    {
      if(grid[y+1][x]->type != 2 && grid[y+1][x]->type != 1 && grid[y+1][x]->type != 3)
      {
        Swap(grid, x, y, x, y+1);
      }
      else if (x < (xLimit-1) && grid[y+1][x+1]->type != 1 && grid[y+1][x+1]->type != 2 && grid[y+1][x+1]->type != 3) 
      {
        Swap(grid, x, y, x+1, y+1);
      }
      else if (x > 0 && grid[y+1][x-1]->type != 1 && grid[y+1][x-1]->type != 2 && grid[y+1][x-1]->type != 3)
      {
        Swap(grid, x, y, x-1, y+1);
      }
      else if (x < (xLimit-1) && grid[y][x+1]->type != 1 && grid[y][x+1]->type != 2 && grid[y][x+1]->type != 3 && x > 0 && grid[y][x-1]->type != 1 && grid[y][x-1]->type != 2 && grid[y][x-1]->type != 3)
      {
        int dif = rand()%2 == 1? 1 : -1;
        Swap(grid, x, y, x+ dif, y);
      }
      
      else if (x < (xLimit-1) && grid[y][x+1]->type != 1 && grid[y][x+1]->type != 2 && grid[y][x+1]->type != 3)
      {
        Swap(grid, x, y, x+1, y);
      }

      else if (x > 0 && grid[y][x-1]->type != 1 && grid[y][x-1]->type != 2 && grid[y][x-1]->type != 3)
      {
        Swap(grid, x, y, x-1, y);
      }
    }

  }
};

class Grid
{
  public:
  int particleSize;
  int gridX;
  int gridY;

  Particle*** grid;

  public:
  Grid(int pSize, int gridX, int gridY)
  {
    this->particleSize = pSize;
    this->gridX = gridX;
    this->gridY = gridY;

    //Creating the 2D Array
    grid = (Particle***)malloc(sizeof(Particle**) * gridY);
    for (int i = 0; i < gridY; i++)
    {
      Particle** row = (Particle**)malloc(sizeof(Particle*) * gridX);
      for (int j = 0; j < gridX; j++)
      {
        Particle* temp = new Particle(this->particleSize, Vector2i(j, i));
        
        row[j] = temp;
      }
      grid[i] = row;     
    }
  }
  void Draw(RenderWindow& win)
  {
    for (int i = 0; i < gridY; i++)
    {
      for (int j = 0; j < gridX; j++)
      {
        grid[i][j]->Draw(win);
      }
      
    }
    
  }
  void AddParticle(Vector2i pos, int type)
  {
    if(pos.x >= 0 && pos.x < gridX && pos.y >= 0 && pos.y < gridY && grid[pos.y][pos.x]->type == 0)
    {
      if(type == 1)
      {
        free(grid[pos.y][pos.x]); 
        grid[pos.y][pos.x] = new Sand(this->particleSize, pos);
      }
      else if (type == 2)
      {
        free(grid[pos.y][pos.x]); 
        grid[pos.y][pos.x] = new Water(this->particleSize, pos);
      }
      else if (type == 3)
      {
        free(grid[pos.y][pos.x]); 
        grid[pos.y][pos.x] = new Particle(this->particleSize, pos, Color::Red);
        grid[pos.y][pos.x]->type = 3;
      }
      
      
    }
    
  }
  void DeleteParticle(Vector2i pos)
  {
    if(pos.x >= 0 && pos.x < gridX && pos.y >= 0 && pos.y < gridY)
    {
      cout << grid[pos.y][pos.x]->type << "\n";
      if(grid[pos.y][pos.x]->type != 0)
      {
        free(grid[pos.y][pos.x]);
        grid[pos.y][pos.x] = new Particle(particleSize, pos);
      }
    }
  }
  void Update()
  {
    for (int i = gridY-1; i >= 0; i--)
    {
      for (int j = gridX - 1; j >= 0; j--)
      {
        if(grid[i][j]->type != 0)
        {
          grid[i][j]->Update(grid, gridX, gridY);
        }
      }
      
    }
    
  }
  void DebugPrint()
  {
    system("clear");
    for (int i = 0; i < gridY; i++)
    {
      for (int j = 0; j < gridX; j++)
      {
        cout << (grid[i][j]->type) << " ";
      }
      cout << "\n";
      
    }
    
  }
  void DebugType(Vector2i pos)
  {
    if(pos.x >= 0 && pos.x < gridX && pos.y >= 0 && pos.y < gridY)
    {
      cout << grid[pos.y][pos.x]->type << "\n";
    }
  }
};


#endif