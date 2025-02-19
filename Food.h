#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>

class Food {
public:
    Food(int gridWidth, int gridHeight);
    void respawn();
    sf::Vector2i getPosition() const;
    void draw(sf::RenderWindow& window);
    void setFoodTexture(const sf::Texture& texture);

private:
    sf::Vector2i position;
    int gridWidth, gridHeight;
    sf::Texture foodTexture;
    sf::Sprite foodSprite;
};

#endif
