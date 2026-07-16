#include "systems.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <random>

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

void ReduceHealth::update(GameState& state, int posIndex) {
    state.playerHealth -= 10;
    //auto targetPos = std::find(state.enemyPositions.begin(), state.enemyPositions.end(), enemyPos);
    //auto posIndex = std::distance(state.enemyPositions.begin(), targetPos);

    state.enemyPositions[posIndex] = {100.f, 200.f};

    std::cout << "PLAYER HEALTH: " << state.playerHealth << "\n";

    if (state.playerHealth <= 0) {
        std::cout << "GAME OVER! YOU LOSE"  << "\n";
        state.gameOver = true;
    }
}

void ReduceDowns::update(GameState& state, int posIndex) {
    state.playerDowns -= 1;
    state.enemyPositions[posIndex] = {100.f, 200.f};
    std::cout << "Downs Remaining: " << state.playerDowns << "\n";

    if (state.playerDowns <= 0) {
        std::cout << "GO TO THE SIDELINE AND WAIT FOR DOWNS TO RECHARGE" << "\n";
    }
}

void EnemySpawner::update(GameState& state, int enemyNum) {
    static std::mt19937 gen(std::random_device{}()); // Create generator once so we don't make a new one every call
    std::uniform_int_distribution<> distrib(100, 600); // Distrib transforms the random unsigned int (no defined datatype so it could be anything)

    for (int i = 0; i < enemyNum; i++) {
        sf::Vector2f pos;
        pos.x = distrib(gen);
        pos.y = distrib(gen);

        state.enemyPositions.push_back(pos);
    }

    std::uniform_int_distribution<> distribSpeed(100, 300);

    for (int i = 0; i < enemyNum; i++) {
        sf::Vector2f pos;
        float speed = distribSpeed(gen);
        state.enemySpeeds.push_back(speed);
    }

}


void EnemyMovement::update(GameState& state, float dt) {
    float speed = 200.0f;
    EnemyOverlap collisionCheck;
    dt = std::min(dt, 1.0f / 30.0f); // Prevents enemy from being flung across screen after blocking game loop

    for (int i = 0; i < state.enemyPositions.size(); i++) {
        sf::Vector2f dir = state.playerPosition - state.enemyPositions[i];


        if (std::abs(dir.x) >= std::abs(dir.y)) { // Buffer dist of 0.1 for following direction
            dir.y = 0;
            dir.x = (dir.x > 0) ? 1.0f : -1.0f; // Checks if enemy should move left or right
        }
        else {
            dir.x = 0;
            dir.y = (dir.y > 0) ? 1.0f : -1.0f;
        }
        
        state.enemyPositions[i] += dir * speed * dt;

        collisionCheck.update(state, i);
    }
}

void EnemyOverlap::update(GameState& state, int i) {
    MenuSystem gameMenu;
    sf::Vector2f collisionDist = { 10.0f, 10.0f };
    int response = -1;

    // Checks if enemy is colliding with player, currently resets pos for all enemies
    if (std::abs(state.enemyPositions[i].x - state.playerPosition.x) <= collisionDist.x && std::abs(state.enemyPositions[i].y - state.playerPosition.y) <= collisionDist.y) {

        std::cout << "Play down?: ";
        std::cout << std::abs(state.enemyPositions[i].x - state.playerPosition.x) << "\n";
        state.currentMenu = MenuState::Prompt;
        state.menuSelection = 0;
        state.enemyIndex = i;

    }

}

void MenuSystem::handleEvent(GameState& state, const sf::Event& event) {
    if (state.currentMenu != MenuState::Prompt) {
        return;
    }

    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Down || keyPressed->code == sf::Keyboard::Key::Up) {
            state.menuSelection = 1 - state.menuSelection; // Menu == 0, then 1 - 0 is 1, menu == 1, then 1-1 is 0
        }

        if (keyPressed->code == sf::Keyboard::Key::Enter) {
            ReduceHealth healthDeduction;
            ReduceDowns downsDeduction;
            int i = state.enemyIndex;
            if (state.menuSelection == 0) {
                downsDeduction.update(state, i);
            }
            else {
                healthDeduction.update(state, i);
            }
            if (state.menuSelection == 0) {
                healthDeduction.update(state, i);
            }
            else {
                downsDeduction.update(state, i);
            }

            state.currentMenu = MenuState::None;
            state.enemyIndex = -1;
            
        }
    }

}

//void NPCOverlap::update(GameState& state, float dt, int i) {
//
//}

void NPCSpawner::update(GameState& state, float dt) {
    state.npcs = { {1, {"Coach", 300,200}}, {2, {"Trainer", 300,300}}, {3, {"Water Boy", 300,400}}};
}
//
//// Don't use random pos for enemy yet
//int GenerateRandomNumber(int a, int b) {
//    static std::mt19937 gen(std::random_device{}()); // Create generator once so we don't make a new one every call
//    std::uniform_int_distribution<> distrib(a, b); // Distrib transforms the random unsigned int (no defined datatype so it could be anything)
//
//    return distrib(gen);
//}