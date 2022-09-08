#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <random>
#include <cmath>
#include "glm/vec3.hpp"

#define PARTICLE_SIZE 3.f
#define WIN_WIDTH 1000
#define WIN_HEIGHT 500 *2
#define in :
#define PARTICLE_COUNT 200


class Particle : public sf::RectangleShape
{
public:
    Particle(sf::Vector2f coords, sf::Color color) : sf::RectangleShape{{PARTICLE_SIZE, PARTICLE_SIZE}}, Velocity({0, 0})
    {
        this->setPosition(coords);
        this->setFillColor(color);
        this->setSize({PARTICLE_SIZE, PARTICLE_SIZE});

    }
    Particle(sf::Vector2f& coords, sf::Color color, sf::Vector2f Velocity) : sf::RectangleShape{coords}
    {
        Particle(coords, color);
        Velocity = Velocity;
    }
    // Write a constructor
    float side;
    sf::Vector2f Velocity;
};


using P_Vec = std::vector<Particle*>;

auto* particles = new std::vector<P_Vec*>{};

int random(int from = 0, int to = WIN_WIDTH)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rndNum(from,to);

    auto num = rndNum(rng);

    std::cout <<  num << "\n";
    return num;
}

std::vector<Particle*>* createGroup(int number, sf::Color color)
{
    auto group = new std::vector<Particle*>{} ;
    for (size_t i{}; i < number; ++i)
    {
        auto tmp_vec = sf::Vector2f{random() * 1.f, random() * 1.f};
        auto part = new Particle{tmp_vec, color};
        group->push_back(part);

    }

    particles->push_back(group);

    return group;
}


void Draw(sf::RenderWindow* window, Particle* particle)
{
    window->draw(*particle);
}

void checkBounds()
{
    for (auto gr : *particles)
    {
        for (auto a in *gr)
        {
            auto aX = a->getPosition().x, aY = a->getPosition().y;


//            if (aX <= 0 || aX >= WIN_WIDTH)
//            {
//                a->Velocity.x *= -1;
//            }
//            if (aY <= 0 || aY >= WIN_HEIGHT) {
//                a->Velocity.y *= -1;
//            }
            if (aX <= 0) {
                a->Velocity.x *= -1;
                a->setPosition(0, a->getPosition().y);
            }
            if (aX >= WIN_WIDTH)
            {
                a->Velocity.x *= -1;
                a->setPosition(WIN_WIDTH, a->getPosition().y);
            }
            if (aY <= 0) {
                a->Velocity.y *= -1;
                a->setPosition(a->getPosition().x, 0);
            }
            if (aY >= WIN_HEIGHT)
            {
                a->Velocity.y *= -1;
                a->setPosition(a->getPosition().x, WIN_HEIGHT);
            }



        }
    }
}

void rule(P_Vec* particles1, P_Vec* particles2, float g)
{
    for (size_t i{}; i < particles1->size(); ++i) {


        float fx{0}, fy{0};
        Particle *a = nullptr;
        Particle *b = nullptr;
        for (size_t j{}; j < particles2->size(); ++j) {


            a = (*particles1)[i];
            b = (*particles2)[j];

            auto aCoord = a->getPosition();
            auto bCoord = b->getPosition();

            auto dx = aCoord.x - bCoord.x;
            auto dy = aCoord.y - bCoord.y;

            auto d = sqrtf(dx * dx + dy * dy);

            if (d > 0 && d < 80) {
                auto F = g * 1.0f / d;
                fx += (F * dx);
                fy += (F * dy);
            }
            //std::cout << "a position: " << aCoord.x << " : " << aCoord.y << "\n";
            //a->setPosition(aCoord.x + 1, aCoord.y + 1);
        }

        a->Velocity = {(a->Velocity.x + fx)/2, (a->Velocity.y + fy)/2};
//        auto aX = a->getPosition().x, aY = a->getPosition().y;
//        if (aX <= 0) {
//            a->Velocity.x *= -1;
//            a->setPosition(0, a->getPosition().y);
//        }
//        else if (aX >= WIN_WIDTH)
//        {
//            a->Velocity.x *= -1;
//            a->setPosition(WIN_WIDTH, a->getPosition().y);
//        }
//
//        if (aY <= 0) {
//            a->Velocity.y *= -1;
//            a->setPosition(a->getPosition().x, 0);
//        }
//        else if (aX >= WIN_HEIGHT)
//        {
//            a->Velocity.y *= -1;
//            a->setPosition(a->getPosition().x, WIN_HEIGHT);
//        }


        a->move(a->Velocity.x, a->Velocity.y);


    }
    checkBounds();
}

int main()
{
    using namespace sf;

    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "SFML Application");
    window.setFramerateLimit(120);

    /// Initial region

    auto yellow = createGroup(PARTICLE_COUNT, Color::Yellow);
    auto red = createGroup(PARTICLE_COUNT, Color::Red);
    auto green = createGroup(PARTICLE_COUNT, Color::Green);

#pragma region Update
        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            rule(green, green, -0.32);
            rule(green, red, -0.17);
            rule(green, yellow, .34);
            rule(red, red, -0.1);
            rule(red, green, -.34);
            rule(yellow, yellow, .15);
            rule(yellow, green, -0.20);


            window.clear();


            for (auto particleVec : *particles) {
                for (auto particle : *particleVec) {

                //std::cout << "particle position: " << particle->getPosition().x
                         // << " : " << particle->getPosition().y << "\n";
                window.draw(*particle);
                }
            }

            window.display();
        }
#pragma endregion

    // Need to free memory

}





