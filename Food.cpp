#include "Food.h"
#include <cstdlib>
#include <iostream>

#include "Game.h"

Food::Food(int gridWidth, int gridHeight)
    : gridWidth(gridWidth), gridHeight(gridHeight) {
    respawn();
}

void Food::setFoodTexture(const sf::Texture& texture) {
    foodTexture = texture;
    foodSprite.setTexture(foodTexture);
}

void Food::respawn() {
    position.x = rand() % gridWidth;
    position.y = rand() % gridHeight;
}

sf::Vector2i Food::getPosition() const {
    return position;
}

void Food::draw(sf::RenderWindow& window) {
    foodSprite.setPosition(position.x * TILE_SIZE, position.y * TILE_SIZE + SCORE_HEIGHT);
    window.draw(foodSprite);
}
