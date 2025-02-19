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
    position.x = rand() % gridWidth;    // zufällige x-Position innerhalb des Spielfeldes
    position.y = rand() % gridHeight;   // zufällige y-Position innerhalb des Spielfeldes
}

sf::Vector2i Food::getPosition() const {
    return position;
}

void Food::draw(sf::RenderWindow& window) {
    foodSprite.setPosition(position.x * TILE_SIZE, position.y * TILE_SIZE + SCORE_HEIGHT);
    window.draw(foodSprite);
}
