#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>

/**
 * @class Food
 * @brief Klasse für den Apfel im Spiel
 * @details Diese Klasse verwaltet die Position und Darstellung des Apfels (Food) im Spiel
 */
class Food {
public:
    /**
     * @brief Konstruktor der Food-Klasse.
     * @details Erstellt das Food-Objekt und legt die Spielfeldgröße fest
     * @param gridWidth Breite des Spielfelds in Tiles
     * @param gridHeight Höhe des Spielfelds in Tiles
     */
    Food(int gridWidth, int gridHeight);

    /**
     * @brief Respawnt das Essen an einer neuen zufälligen Position
     */
    void respawn();

    /**
     * @brief Gibt die aktuelle Position des Essens zurück
     * @return Position des Essens
     */
    sf::Vector2i getPosition() const;

    /**
     * @brief Zeichnet das Essen auf das Spielfenster
     * @param window Referenz auf das Renderfenster
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Setzt die Textur für das Essen
     * @param texture Textur, die dem Essen zugewiesen wird
     */
    void setFoodTexture(const sf::Texture& texture);

private:
    sf::Vector2i position;      /// Position des Essens auf dem Spielfeld
    int gridWidth, gridHeight;  /// Dimensionen des Spielfelds
    sf::Texture foodTexture;    /// Textur für das Essen
    sf::Sprite foodSprite;      /// Sprite für das Essen
};

#endif
