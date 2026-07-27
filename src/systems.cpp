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
void EnemySpawner::despawn(GameState& state, int index) {
    state.enemyPositions.erase(state.enemyPositions.begin() + index);
    state.enemySpeeds.erase(state.enemySpeeds.begin() + index);
}

void ReduceHealth::update(GameState& state, int posIndex, int amount) {
    EnemySpawner spawner;
    state.playerHealth -= amount;

    state.enemyPositions[posIndex] = {100.f, 200.f};
    spawner.despawn(state, posIndex);
    std::cout << "PLAYER HEALTH: " << state.playerHealth << "\n";

    if (state.playerHealth <= 0) {
        std::cout << "GAME OVER! YOU LOSE"  << "\n";
        state.gameOver = true;
    }
}

void ReduceDowns::update(GameState& state, int posIndex) {
    EnemySpawner spawner;
    state.playerDowns -= 1;
    state.enemyPositions[posIndex] = {100.f, 200.f};
    spawner.despawn(state, posIndex);
    std::cout << "Downs Remaining: " << state.playerDowns << "\n";

    if (state.playerDowns <= 0) {
        std::cout << "GO TO THE SIDELINE AND WAIT FOR DOWNS TO RECHARGE" << "\n";
    }
}

void EnemySpawner::update(GameState& state, int enemyNum) {
    static std::mt19937 gen(std::random_device{}()); // Create generator once so we don't make a new one every call
    std::uniform_int_distribution<> distribX(100, 600); // Distrib transforms the random unsigned int (no defined datatype so it could be anything)
    std::uniform_int_distribution<> distribY(50, 100);
    for (int i = 0; i < enemyNum; i++) {
        sf::Vector2f pos;
        pos.x = distribX(gen);
        pos.y = distribY(gen);

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
    
    EnemyOverlap collisionCheck;
    dt = std::min(dt, 1.0f / 30.0f); // Prevents enemy from being flung across screen after blocking game loop

    for (int i = 0; i < state.enemyPositions.size(); i++) {
        sf::Vector2f dir = state.playerPosition - state.enemyPositions[i];
        float speed = state.enemySpeeds[i];

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
        state.currentMenu = MenuState::DownPrompt;
        state.menuSelection = 0;
        state.enemyIndex = i;

    }

}

void MenuSystem::handleEvent(GameState& state, const sf::Event& event) {
    MenuSystem menuSystem;
    if (state.currentMenu == MenuState::DownPrompt) {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Down || keyPressed->code == sf::Keyboard::Key::Up || keyPressed->code == sf::Keyboard::Key::W || keyPressed->code == sf::Keyboard::Key::S) {
                state.menuSelection = 1 - state.menuSelection; // Menu == 0, then 1 - 0 is 1, menu == 1, then 1-1 is 0
            }

            if (keyPressed->code == sf::Keyboard::Key::Enter || keyPressed->code == sf::Keyboard::Key::Space) {
                ReduceDowns downsDeduction;
                int i = state.enemyIndex;
                if (state.menuSelection == 0) {
                    state.currentMenu = MenuState::PlayPrompt;
                }
                else {
                    downsDeduction.update(state, i);
                    state.currentMenu = MenuState::None;
                    state.enemyIndex = -1;
                }
            }
        }
    }

    else if (state.currentMenu == MenuState::PlayPrompt) {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Down || keyPressed->code == sf::Keyboard::Key::Up || keyPressed->code == sf::Keyboard::Key::W || keyPressed->code == sf::Keyboard::Key::S) {
                state.menuSelection = 1 - state.menuSelection; // Menu == 0, then 1 - 0 is 1, menu == 1, then 1-1 is 0
            }

            if (keyPressed->code == sf::Keyboard::Key::Enter || keyPressed->code == sf::Keyboard::Key::Space) {
                int i = state.enemyIndex;
                if (state.menuSelection == 0) {
                    state.skillMove = SkillMove::Truck;
                }
                else if (state.menuSelection == 1){
                    state.skillMove = SkillMove::Juke;
                }
                
                menuSystem.calculateResult(state);

                

            }
        }
    }
    else if (state.currentMenu == MenuState::ResultPrompt) {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Enter || keyPressed->code == sf::Keyboard::Key::Space) {
                state.currentMenu = MenuState::None;
                state.enemyIndex = -1;
            }
        }
    }
}

    

void MenuSystem::calculateResult(GameState& state) {
    int i = state.enemyIndex;
    ReduceHealth healthDeduction;
    ReduceDowns downsDeduction;
    switch (state.skillMove) {
    case (SkillMove::Truck):
        healthDeduction.update(state, i, 10);
        break;
    case (SkillMove::Juke):
        healthDeduction.update(state, i, 0);
        break;
    }
    state.currentMenu = MenuState::ResultPrompt;
}

//void NPCOverlap::update(GameState& state, float dt, int i) {
//
//}

void NPCSpawner::update(GameState& state, float dt) {
    state.npcs = { {1, {"Coach", 300,200}}, {2, {"Trainer", 300,300}}, {3, {"Water Boy", 300,400}}};
}