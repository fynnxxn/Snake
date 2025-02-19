#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <deque>

/**
 * @brief Bwegungsrichtungen der Schlange
 */
enum class Direction { UP, DOWN, LEFT, RIGHT };

/**
 * @class Snake
 * @brief Klasse welche die Schlange im Spiel repräsentiert
 * @details Diese Klasse verwaltet die Position, Bewegung und Kollision der Schlange.
 */
class Snake {
public:
    /**
     * @brief Konstruktor der Schlange
     * @details Erstellt eine Schlange mit einer Startposition auf dem Spielfeld
     * @param gridWidth Breite des Spielfeldes in Tiles
     * @param gridHeight Höhe des Spielfeldes in Tiles
     */
    Snake(int gridWidth, int gridHeight);

    /**
     * @brief Bewegt die Schlange in die aktuelle Richtung
     */
    void move();

    /**
     * @brief Erhöht die Länge der Schlange um ein Segment
     */
    void grow();

    /**
     * @brief Setzt die Bewegungsrichtung der Schlange
     * @param dir Neue Bewegungsrichtung
     */
    void setDirection(Direction dir);

    /**
     * @brief Überprüft, ob die Schlange kollidiert ist
     * @return True, wenn die Schlange kollidiert ist, sonst False
     */
    bool checkCollision();

    /**
     * @brief Gibt die aktuelle Position des Schlangenkopfes zurück
     * @return Position des Kopfes
     */
    sf::Vector2i getHeadPosition() const;

    /**
     * @brief Gibt die aktuelle Länge der Schlange zurück
     * @return Anzahl der Segmente der Schlange
     */
    int getSize() const;

    /**
     * @brief Zeichnet die Schlange auf das Spielfenster
     * @param window Referenz auf das Renderfenster
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Setzt die Schlange zurück
     */
    void reset();

private:
    std::deque<sf::Vector2i> body;  /// Positionen der Schlangensegmente
    Direction direction;            /// Aktuelle Bewegungsrichtung der Schlange
    Direction nextDirection;        /// nächste Bewegungsrichtung der Schlange
    int gridWidth, gridHeight;      /// Spielfeldgröße in Tiles
};

#endif
