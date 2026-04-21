#include "systems.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>


void PlayerMovement::update(GameState& state, float dt) {
    float speed = 400.0f;
    bool h = false; // Horizontal movement
    bool v = false; // Vertical movement
    bool keyPressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        state.playerMoveDir = 0;
        keyPressed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        state.playerMoveDir = 1;
        keyPressed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        state.playerMoveDir = 2;
        keyPressed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        state.playerMoveDir = 3; 
        keyPressed = true;
    }

    if (keyPressed == false) {
        state.playerMoveDir = -1;
    }




    switch (state.playerMoveDir) {
    case (0):
        state.playerPosition.x -= (speed * dt);
        break;
    case (1):
        state.playerPosition.x += (speed * dt);
        break;
    case (2):
        state.playerPosition.y -=  (speed * dt);
        break;
    case (3):
        state.playerPosition.y += (speed * dt);
        break;
    default:
        state.playerPosition.x += (0);
        state.playerPosition.y += (0);
        break;
    }

}

//void EnemySpawner::update(GameState& state, float dt) {
//    state.spawnTimer += dt;
//
//    if (spawnTimer > 2.0f) {
//        spawnTimer = 0.0f;
//
//        sf::Vector2f pos;
//        pos.x = GenerateRandomNumber(400, 800);
//        pos.y = GenerateRandomNumber(400, 600);
//
//        state.enemyPositions.push_back(pos);
//    }
//}

void EnemyMovement::update(GameState& state, float dt) {
    float speed = 300.0f;

        sf::Vector2f dir = state.playerPosition - state.enemyPosition;

        std::cout << "X POSITION: " << dir.x;
        std::cout << "THE OTHER Y POSITION: " << dir.y*-1;

        if (std::abs(dir.x) >= std::abs(dir.y)) { // Buffer dist of 0.1 for following direction
            dir.y = 0;
            dir.x = (dir.x > 0) ? 1.0f : -1.0f; // Checks if enemy should move left or right
        }
        else {
            dir.x = 0;
            dir.y = (dir.y > 0) ? 1.0f : -1.0f;
        }

        state.enemyPosition += dir * speed * dt;
        
}

