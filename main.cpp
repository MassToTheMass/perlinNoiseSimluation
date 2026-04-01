#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.hpp"
#include "ValueStorage.hpp"

int main() {

    int detail = 20;
    std::cout << "Detail: ";
    std::cin >> detail;

    int vectors = 20;
    std::cout << "Vectors per dimension: ";
    std::cin >> vectors;

    Grid vectorGrid(vectors);

    // set width and height of screen
    const int WIDTH = (vectors - 1) * detail;
    const int HEIGHT = (vectors - 1) * detail;

    ValueStorage storage(WIDTH, HEIGHT);

    storage.FillAllCellsInfluenceValues(vectorGrid, detail);
    // storage.printAverages();

    sf::RenderWindow window(
        sf::VideoMode(WIDTH, HEIGHT),
        "Pixel Grid"
    );

    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);
    window.setFramerateLimit(10);

    sf::Texture texture;
    sf::Sprite sprite;

    int dz = 1; // direction of z change

    int z = 0; // for 2D visualization, we can fix z to 0
    int depth = (vectors - 1);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- PIXEL WRITING ZONE ---
        auto rebuildImage = [&](int z) {
            for (int y = 0; y < HEIGHT; ++y) {
                for (int x = 0; x < WIDTH; ++x) {
                    sf::Uint8 pixel = static_cast<sf::Uint8>(
                        (storage.getValue(x, y, z) + 1) * 127.5
                    );
                    image.setPixel(x, y, sf::Color(0, 0, pixel));
                }
            }
            texture.loadFromImage(image);
        };
        rebuildImage(z);
        // --------------------------

        texture.loadFromImage(image);
        sprite.setTexture(texture);

        window.clear();
        window.draw(sprite);
        window.display();

        // advance z slice for next frame
        z += dz;
        if (z >= depth || z <= 0) dz *= -1;  // loop back
    }

    return 0;
}
