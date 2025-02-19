#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <deque>

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
public:
    Snake(int gridWidth, int gridHeight);
    void move();
    void grow();
    void setDirection(Direction dir);
    bool checkCollision();
    sf::Vector2i getHeadPosition() const;
    int getSize() const;
    void draw(sf::RenderWindow& window);
    void reset();

private:
    std::deque<sf::Vector2i> body;
    Direction direction;
    int gridWidth, gridHeight;
};

#endif
