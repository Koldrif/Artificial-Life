#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <random>
#include "glm/vec3.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
    sf::RectangleShape shape;
    float pX{100.f}, pY{100.f};
    sf::Vector2f radius{3, 3};
    shape.setSize(radius);
    shape.setPosition(pX, pY);
    shape.setFillColor(sf::Color::Cyan);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rndNum(0,640); // distribution in range [1, 6]

    std::cout << rndNum(rng) << std::endl;

    std::vector<sf::Transformable*> shapes{};

    for (size_t i{}; i < 100; ++i)
    {
        shapes.push_back(new sf::RectangleShape{radius});
        shapes[i]->setPosition((float)rndNum(rng), (float)rndNum(rng));
    }


    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
//
//        pX = fmod(pX, 600.f) + .1f;
//        pY = fmod(pY, 480.f) + .1f;
        for (auto sh : shapes)
        {
         //   sh->setPosition(pX * rndNum(rng) * 0.3, pY* rndNum(rng) * 0.3);

            window.draw(*dynamic_cast<sf::Drawable*>(sh));
        }




        window.display();
    }
}
