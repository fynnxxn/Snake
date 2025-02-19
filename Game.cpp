#include "Game.h"
#include <iostream>

Game::Game()
    :   window(sf::VideoMode(GRID_WIDTH * TILE_SIZE, GRID_HEIGHT * TILE_SIZE + SCORE_HEIGHT), "Snake"),
        snake(GRID_WIDTH, GRID_HEIGHT),
        food(GRID_WIDTH, GRID_HEIGHT),
        gameStarted(false),
        gameOver(false) {

    if (!font.loadFromFile("../fonts/arial.ttf")) {
        std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("../graphics/Snake_background.PNG")) {
        std::cerr << "Fehler beim Laden des Hintergrunds" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    if (!foodTexture.loadFromFile("../graphics/food.png")) {
        std::cerr << "Fehler beim Laden des Essens" << std::endl;
    }
    food.setFoodTexture(foodTexture);
    gameOverfoodSprite.setTexture(foodTexture);

    if (!highScoreTexture.loadFromFile("../graphics/trophy.png")) {
        std::cerr << "Fehler beim Laden des Pokals" << std::endl;
    }
    gameOverhighScoreSprite.setTexture(highScoreTexture);
    highScoreSprite.setTexture(highScoreTexture);
    highScoreSprite.setPosition(100, 8);

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(50, 10);
    scoreText.setString("0");

    foodSprite.setTexture(foodTexture);
    foodSprite.setPosition(10, 10);

    highScoreText.setFont(font);
    highScoreText.setCharacterSize(24);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition(140, 10 );
    highScoreText.setString("0");

}

void Game::run() {
    window.setFramerateLimit(120);

    sf::Clock clock;

    while (window.isOpen()) {
        handleInput();

        if (!gameOver && clock.getElapsedTime().asMilliseconds() > 150) {
            update();
            clock.restart();
        }

        render();
    }
}

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            gameStarted = true;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) snake.setDirection(Direction::UP);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) snake.setDirection(Direction::DOWN);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) snake.setDirection(Direction::LEFT);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) snake.setDirection(Direction::RIGHT);
        }

        if (event.type == sf::Event::MouseButtonPressed && gameOver) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                resetGame();
            }
        }

        if (event.type == sf::Event::MouseButtonPressed && gameOver) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                window.close();
            }
        }
    }
}

void Game::update() {
    if (!gameStarted || gameOver) {
        return;
    }

    snake.move();

    if (snake.checkCollision()) {
        gameOver = true;
    }

    if (snake.getHeadPosition() == food.getPosition()) {
        snake.grow();
        food.respawn();
    }

    scoreText.setString(std::to_string(snake.getSize() - 1));
    highScoreText.setString(std::to_string(highScore));

    if (snake.getSize() - 1 > highScore) {
        highScoreText.setString(std::to_string(snake.getSize() - 1));
        highScore = snake.getSize() - 1;
    }
}

void Game::resetGame() {
    snake = Snake(GRID_WIDTH, GRID_HEIGHT);
    food.respawn();
    gameOver = false;
    gameStarted = false;
    scoreText.setString("0");
}

void Game::render() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(foodSprite);
    window.draw(highScoreSprite);
    snake.draw(window);
    food.draw(window);

    if (gameOver) {

        gameStarted = false;

        // Overlay (grauer Kasten)
        gameOverOverlay.setSize(sf::Vector2f(288, 352));
        gameOverOverlay.setFillColor(sf::Color(100, 100, 100, 170));
        gameOverOverlay.setPosition(128, 82);

        // Game Over Score
        gameOverfoodSprite.setPosition(192, 146);
        gameOverScoreText.setFont(font);
        gameOverScoreText.setString(std::to_string(snake.getSize() - 1));
        gameOverScoreText.setCharacterSize(24);
        gameOverScoreText.setFillColor(sf::Color::White);
        gameOverScoreText.setPosition(264, 146);

        // Game Over High Score
        gameOverhighScoreSprite.setPosition(192, 210);
        gameOverHighScoreText.setFont(font);
        gameOverHighScoreText.setString(std::to_string(highScore));
        gameOverHighScoreText.setCharacterSize(24);
        gameOverHighScoreText.setFillColor(sf::Color::White);
        gameOverHighScoreText.setPosition(264, 210);

        // Nochmal Spielen Button
        restartButton.setSize(sf::Vector2f(224, 32));
        restartButton.setFillColor(sf::Color(66,133,244));
        restartButton.setPosition(160, 8 * TILE_SIZE + SCORE_HEIGHT);
        restartText.setFont(font);
        restartText.setString("Spielen");
        restartText.setCharacterSize(18);
        restartText.setFillColor(sf::Color::White);
        restartText.setPosition(165, 310);

        // Quit Button
        quitButton.setSize(sf::Vector2f(224, 32));
        quitButton.setFillColor(sf::Color(66,133,244));
        quitButton.setPosition(160, 10 * TILE_SIZE + SCORE_HEIGHT);
        quitText.setFont(font);
        quitText.setString("Spiel beenden");
        quitText.setCharacterSize(18);
        quitText.setFillColor(sf::Color::White);
        quitText.setPosition(165, 374);

        // Alles drawen
        window.draw(gameOverOverlay);
        window.draw(gameOverhighScoreSprite);
        window.draw(gameOverfoodSprite);
        window.draw(gameOverScoreText);
        window.draw(gameOverHighScoreText);
        window.draw(restartButton);
        window.draw(restartText);
        window.draw(quitButton);
        window.draw(quitText);

    }

    window.draw(scoreText);
    window.draw(highScoreText);
    window.display();
}
