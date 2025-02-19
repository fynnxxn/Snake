#include "Snake.h"

#include "Game.h"

Snake::Snake(int gridWidth, int gridHeight)
    : gridWidth(gridWidth), gridHeight(gridHeight), direction(Direction::RIGHT) {
    body.push_back(sf::Vector2i(gridWidth / 2, gridHeight / 2));
}

void Snake::move() {
    sf::Vector2i newHead = body.front();

    switch (direction) {
        case Direction::UP: newHead.y--; break;
        case Direction::DOWN: newHead.y++; break;
        case Direction::LEFT: newHead.x--; break;
        case Direction::RIGHT: newHead.x++; break;
    }

    body.push_front(newHead);
    body.pop_back();
}

void Snake::grow() {
    body.push_back(body.back());
}

void Snake::setDirection(Direction dir) {
    // verhindert direktes umkehren
    if ((direction == Direction::UP && dir == Direction::DOWN) ||
        (direction == Direction::DOWN && dir == Direction::UP) ||
        (direction == Direction::LEFT && dir == Direction::RIGHT) ||
        (direction == Direction::RIGHT && dir == Direction::LEFT)) {
        return;
        }
    direction = dir;
}

bool Snake::checkCollision() {
    const auto& head = body.front();

    // Überprüfung, ob die Schlange mit der Spielfeldbegrenzung kollidiert
    if (head.x < 0 || head.y < SCORE_HEIGHT / TILE_SIZE || head.x >= gridWidth || head.y >= gridHeight) {
        return true;
    }

    // Überprüfung, ob die Schlange mit sich selbst kollidiert
    for (size_t i = 1; i < body.size(); i++) {
        if (body[i] == head) return true;
    }

    return false;
}

sf::Vector2i Snake::getHeadPosition() const {
    return body.front();
}

int Snake::getSize() const {
    return body.size();
}

void Snake::draw(sf::RenderWindow& window) {
    sf::RectangleShape rect(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    rect.setFillColor(sf::Color(66,133,244));

    for (const auto& segment : body) {
        rect.setPosition(segment.x * TILE_SIZE, segment.y * TILE_SIZE + SCORE_HEIGHT);
        window.draw(rect);
    }
}