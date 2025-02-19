/**
 * @file Game.h
 * @brief Header-Datei für dieses Snake Spiel
 */
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"

/**
 * @brief Größe eines Tiles in Pixeln
 */
extern const int TILE_SIZE;
/**
 * @brief Breite des Spielfeldes in Anzahl der Tiles
 */
extern const int GRID_WIDTH;
/**
 * @brief Höhe des Spielfeldes in Anzahl der Tiles
 */
extern const int GRID_HEIGHT;
/**
 * @brief Höhe des Bereiches für den Score in Pixeln
 */
extern const int SCORE_HEIGHT;

/**
 * @class Game
 * @brief Hautpklasse für das Snake Spiel
 * @details Diese Klasse verwaltet das komplette Spiel. Sie initialisiert das Spielfeld, verarbeitet Eingaben,
 * aktualisiert den Spielzustand und rendert die Grafiken
 */
class Game {
public:
    /**
     * @brief Konstruktor der Game-Klasse
     * @details Initialisiert das Spielfenster, lädt Ressourcen und setzt alle Spielvariablen auf ihren Startwert
     */
    Game();

    /**
     * @brief Startet die Hauptschleife für das Spiel
     */
    void run();

private:
    /**
     * @brief Verarbeitet Benutzereingaben
     */
    void handleInput();

    /**
     * @brief Aktualisiert den Spielzustand
     */
    void update();

    /**
     * @brief Rendert das Spiel und die Elemente
     */
    void render();

    /**
     * @brief setzt das Spiel nach einer Kollision zurück
     */
    void resetGame();

    sf::RenderWindow window;    /// Spielfenster
    Snake snake;                /// Instanz der Snake-Klasse
    Food food;                  /// Instanz der Food-Klasse

    sf::Font font;              /// Schriftart
    sf::Text scoreText;         /// Text für den Score
    sf::Text highScoreText;     /// Text für den Highscore

    sf::Texture backgroundTexture;  /// Hintergrund-Textur
    sf::Sprite backgroundSprite;    /// Hintergrund-Sprite

    sf::Texture foodTexture;        /// Textur für das Essen
    sf::Sprite foodSprite;          /// Sprite für das Essen

    sf::Texture highScoreTexture;   /// Textur für den Highscore
    sf::Sprite highScoreSprite;     /// Sprite für den Highscore

    sf::RectangleShape gameOverOverlay; /// Overlay bei einer Spielniederlage
    sf::Sprite gameOverhighScoreSprite; /// Sprite für den Highscore im Overlay
    sf::Sprite gameOverfoodSprite;      /// Sprite für den Score im Overlay
    sf::Text gameOverScoreText;         /// Text für den Score im Overlay
    sf::Text gameOverHighScoreText;     /// Text für den Highscore im Overlay

    sf::RectangleShape restartButton;   /// Button zum Spiel neu starten
    sf::Text restartText;               /// Text für den restart-Button
    sf::RectangleShape quitButton;      /// Button zum Spiel schließen
    sf::Text quitText;                  /// Text für den quit-Button

    bool gameOver;      /// Statusvariable für das Spielende
    bool gameStarted;   /// Statusvariable für den Spielstart
    int highScore = 0;  /// Speichert den Highscore
};


#endif
