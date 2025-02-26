#include "Game.h"
#include <iostream>

const int TILE_SIZE = 32;
const int GRID_WIDTH = 17;
const int GRID_HEIGHT = 15;
const int SCORE_HEIGHT = 50;

Game::Game()
    :   window(sf::VideoMode(GRID_WIDTH * TILE_SIZE, GRID_HEIGHT * TILE_SIZE + SCORE_HEIGHT), "Snake"),
        snake(GRID_WIDTH, GRID_HEIGHT),
        food(GRID_WIDTH, GRID_HEIGHT),
        gameStarted(false),
        gameOver(false) {

    // Lädt die Schriftart
    if (!font.loadFromFile("../fonts/arial.ttf")) {
        std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
    }

    // Lädt die Hintergrundgrafik
    if (!backgroundTexture.loadFromFile("../graphics/Snake_background.PNG")) {
        std::cerr << "Fehler beim Laden des Hintergrunds" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Lädt den Apfel
    if (!foodTexture.loadFromFile("../graphics/food.png")) {
        std::cerr << "Fehler beim Laden des Essens" << std::endl;
    }
    food.setFoodTexture(foodTexture);
    gameOverfoodSprite.setTexture(foodTexture);

    // Lädt den Pokal
    if (!highScoreTexture.loadFromFile("../graphics/trophy.png")) {
        std::cerr << "Fehler beim Laden des Pokals" << std::endl;
    }
    gameOverhighScoreSprite.setTexture(highScoreTexture);
    highScoreSprite.setTexture(highScoreTexture);
    highScoreSprite.setPosition(100, 8);

    // Initialisiert die Score-Anzeige
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(50, 10);
    scoreText.setString("0");

    foodSprite.setTexture(foodTexture);
    foodSprite.setPosition(10, 10);

    // Initialisiert die Highscore-Anzeige
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

        // Events für die Steuerung
        if (event.type == sf::Event::KeyPressed) {
            gameStarted = true;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) snake.setDirection(Direction::UP);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) snake.setDirection(Direction::DOWN);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) snake.setDirection(Direction::LEFT);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) snake.setDirection(Direction::RIGHT);
        }

        // Klick Event für den restart-Button
        if (event.type == sf::Event::MouseButtonPressed && gameOver) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            if (restartButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                resetGame();
            }
        }

        // Klick Event für den quit-Button
        if (event.type == sf::Event::MouseButtonPressed && gameOver) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            if (quitButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
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

    // Schlange vergrößern, wenn die Schlange mit dem Essen kollidiert
    if (snake.getHeadPosition() == food.getPosition()) {
        snake.grow();
        food.respawn();
    }

    scoreText.setString(std::to_string(snake.getSize() - 1));
    highScoreText.setString(std::to_string(highScore));

    // Highscore anzeigen/aktualisieren, wenn es ein Highscore ist
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

    if (!gameOver) {
        snake.draw(window);
        food.draw(window);
    }

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

        // "Spielen" Button
        restartButton.setSize(sf::Vector2f(224, 32));
        restartButton.setFillColor(sf::Color(66,133,244));
        restartButton.setPosition(160, 8 * TILE_SIZE + SCORE_HEIGHT);
        restartText.setFont(font);
        restartText.setString("Spielen");
        restartText.setCharacterSize(18);
        restartText.setFillColor(sf::Color::White);
        restartText.setPosition(165, 310);

        // "Spiel beenden" Button
        quitButton.setSize(sf::Vector2f(224, 32));
        quitButton.setFillColor(sf::Color(66,133,244));
        quitButton.setPosition(160, 10 * TILE_SIZE + SCORE_HEIGHT);
        quitText.setFont(font);
        quitText.setString("Spiel beenden");
        quitText.setCharacterSize(18);
        quitText.setFillColor(sf::Color::White);
        quitText.setPosition(165, 374);

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
