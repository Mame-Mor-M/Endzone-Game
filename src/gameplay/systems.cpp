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

    float rightScreenBorder = 720.0f;
    float bottomScreenBorder = 520.0f;

    if (state.playerPosition.x > rightScreenBorder ) {
        state.playerPosition.x = state.playerPosition.x - 1;
    }
    if (state.playerPosition.x < 0.f) {
        state.playerPosition.x = state.playerPosition.x + 1;
    }

    if (state.playerPosition.y < 0.f) {
        state.playerPosition.y = state.playerPosition.y + 1;
    }

    if (state.playerPosition.y > bottomScreenBorder) {
        state.playerPosition.y = state.playerPosition.y - 1;
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

void SceneChange::update(GameState& state, SceneManager& scene) {
    float rightScreenBorder = 720.f;

    if (state.playerPosition.x >= rightScreenBorder && scene.currentLevel != Level::Sideline) {
        state.currentMenu = MenuState::LevelPrompt;
    }
    else if (state.playerPosition.x <= 0.f && scene.currentLevel == Level::Sideline){
        state.currentMenu = MenuState::LevelPrompt;
    }
    else if (state.playerPosition.y <= 0 && scene.currentLevel != Level::Sideline) {
        int index = static_cast<int>(scene.currentLevel);
        IncreasePoints pointIncrease;
        if (index < static_cast<size_t>(Level::Count) - 1) {
            index += 1;
            scene.SetCurrentScene(index);
            state.playerPosition = { 390.f, 500.f };
        }
        else {
            scene.SetCurrentScene(0);
            state.currentMenu = MenuState::TouchdownPrompt;
            pointIncrease.update(state, 7);
        }

    }
    
}
void EnemySpawner::despawn(int index, SceneManager& scene) {
    //state.enemyPositions.erase(state.enemyPositions.begin() + index);
    //state.enemySpeeds.erase(state.enemySpeeds.begin() + index);

    scene.GetCurrentScene()->DespawnEnemy(index);
}

void ReduceStamina::update(GameState& state, int amount) {
    state.playerStamina -= amount;
    state.staminaLost = amount;

    std::cout << "Player stamina reduced, now: " << state.playerStamina << "\n";

    if (state.playerStamina <= 0) {
        std::cout << "You are exhausted!\n";
    }
}

void ReduceHealth::update(GameState& state, int posIndex, int amount, SceneManager& scene) {
    EnemySpawner spawner;
    state.playerHealth -= amount;
    state.healthLost = amount;

    spawner.despawn(posIndex, scene);
    std::cout << "Health reduced, new health: " << state.playerHealth << "\n";

    if (state.playerHealth <= 0) {
        std::cout << "GAME OVER! YOU LOSE"  << "\n";
        state.gameOver = true;
    }
}

void ReduceDowns::update(GameState& state, int posIndex, SceneManager& scene) {
    EnemySpawner spawner;
    state.playerDowns -= 1;
    if (posIndex >= 0) {
        spawner.despawn(posIndex, scene);
    }
    
    std::cout << "Downs Remaining: " << state.playerDowns << "\n";

    if (state.playerDowns <= 0) {
        std::cout << "YOU RAN OUT OF DOWNS! GO TO THE SIDELINE!" << "\n";
    }
}

void IncreasePoints::update(GameState& state, int amount) {
    // Points calculated by how many opposing players you encounter 
    // before you reach the endzone. Tradeoff, try to eliminate as many
    // enemies as possible while still reaching the endzone (YARDS)
    state.totalPoints += amount * state.pointMultiplier + state.totalYards;
    std::cout << "\nTouchdown, you scored " << state.totalPoints << " points\nyou finished with " << state.totalYards << " yards\n" << "Your durability is: " << state.playerHealth << "\nYour stamina is: " << state.playerStamina << "\n And you had " << state.playerDowns << " downs to spare.\n" << "Your final point multipler was: " << state.pointMultiplier;
}

void IncreaseMultiplier::update(GameState& state, float amount) {
    int yardCost = 20;
    if ((state.totalYards - yardCost) >= 0) {
        state.pointMultiplier += amount;
        state.totalYards -= yardCost;
        std::cout << "You spent: " << yardCost << " yards to buy a " << amount << " increase in your point multiplier. You now have: " << state.totalYards << " yards and " << state.pointMultiplier << " point multiplier\n";
    }
    else {
        std::cout << "Broke";
    }
}

void IncreaseYards::update(GameState& state, int amount) {
    state.totalYards += amount;
}

void IncreaseDowns::update(GameState& state, int amount) {
    state.playerDowns += amount;

}

void IncreaseHealth::update(GameState& state, int amount) {
    if ((state.totalYards - amount / 2) >= 0) {
        state.playerHealth += amount;
        state.totalYards -= amount / 2;
        std::cout << "You spent: " << amount / 2 << " yards to buy " << amount << " durability. You now have: " << state.totalYards << " yards " << state.playerHealth << " durability\n";
    }
    else {
        std::cout << "Broke";
    }
}

void IncreaseStamina::update(GameState& state, int amount) {
    if ((state.totalYards - amount / 2) >= 0) {
        state.playerStamina += amount;
        state.totalYards -= amount / 2;
        std::cout << "You spent: " << amount / 2 << " yards to buy " << amount << " stamina. You now have: " << state.totalYards << " yards " << state.playerStamina << " stamina\n";
    }
    else {
        std::cout << "Broke";
    }
    
}

void EnemySpawner::update(GameState& state, int enemyNum, SceneManager& scene) {
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

        scene.GetCurrentScene()->GetEnemySpeeds().push_back(speed);
    }

}


void EnemyMovement::update(GameState& state, float dt, SceneManager& sceneManager) {
    
    EnemyOverlap collisionCheck;
    dt = std::min(dt, 1.0f / 30.0f); // Prevents enemy from being flung across screen after blocking game loop
    std::vector<sf::Vector2f> enemyPositions = sceneManager.GetCurrentScene()->GetEnemyPositions();
    std::vector<float> enemySpeeds = sceneManager.GetCurrentScene()->GetEnemySpeeds();

    for (int i = 0; i < enemyPositions.size(); i++) {
        sf::Vector2f dir = state.playerPosition - enemyPositions[i];
        float speed = enemySpeeds[i];

        if (std::abs(dir.x) >= std::abs(dir.y)) { // Buffer dist of 0.1 for following direction
            dir.y = 0;
            dir.x = (dir.x > 0) ? 1.0f : -1.0f; // Checks if enemy should move left or right
        }
        else {
            dir.x = 0;
            dir.y = (dir.y > 0) ? 1.0f : -1.0f;
        }
        
        
        enemyPositions[i] += dir * speed * dt;

        sceneManager.GetCurrentScene()->SetEnemyPosition(i, enemyPositions[i]);

        collisionCheck.update(state, i, sceneManager);
    }
}

void EnemyOverlap::update(GameState& state, int i, SceneManager& sceneManager) {
    MenuSystem gameMenu;
    EnemyRoll enemyRoll;
    sf::Vector2f collisionDist = { 10.0f, 10.0f };
    int response = -1;

    std::vector<sf::Vector2f> enemyPositions = sceneManager.GetCurrentScene()->GetEnemyPositions();

    // Checks if enemy is colliding with player, currently resets pos for all enemies
    if (std::abs(enemyPositions[i].x - state.playerPosition.x) <= collisionDist.x && std::abs(enemyPositions[i].y - state.playerPosition.y) <= collisionDist.y) {

        state.currentMenu = MenuState::DownPrompt;
        state.menuSelection = 0;
        state.enemyIndex = i;
        enemyRoll.update(state);

    }

}

void EnemyRoll::update(GameState& state) {

    RollNumber rollNum;

    TackleType tackle = static_cast<TackleType>(rollNum.update(0, 2));

    switch (tackle) {
    case (0):
        std::cout << "High Tackle\n";
        state.opponentTackle = TackleType::High;
        state.opponentRoll = rollNum.update(1, 3);
        break;
    case (1):
        std::cout << "Low Tackle\n";
        state.opponentTackle = TackleType::Low;
        state.opponentRoll = rollNum.update(4, 10);
        break;
    case (2):
        std::cout << "Hit Stick Tackle\n";
        state.opponentTackle = TackleType::HitStick;
        state.opponentRoll = rollNum.update(1, 10);
        break;
    }
    
}

void NPCOverlap::update(GameState& state, SceneManager& sceneManager) {
    MenuSystem gameMenu;
    sf::Vector2f collisionDist = { 80.0f, 80.0f };

    const std::map<int,std::unique_ptr<Scene::NPC>>& npcs = sceneManager.GetCurrentScene()->GetNPCs();

    if (npcs.empty()) {
        return;
    }

    for (auto& [id, npc] : npcs) {
        if (std::abs(npc->x - state.playerPosition.x) <= collisionDist.x && std::abs(npc->y - state.playerPosition.y) <= collisionDist.y ) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
                state.currentMenu = MenuState::NPCPrompt;
                state.currentNPC = npc->npcType;
            }

        }
    }
}

void MenuSystem::handleEvent(GameState& state, const sf::Event& event, SceneManager& scene) {
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
                    downsDeduction.update(state, i, scene);
                    state.currentMenu = MenuState::None;
                    state.enemyIndex = -1;
                }
            }
        }
    }

    else if (state.currentMenu == MenuState::PlayPrompt) {
        RollNumber rollNum;
        JudgeEncounter judge;
        int menuCapacity = 3;
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Down || keyPressed->code == sf::Keyboard::Key::S) {
                state.menuSelection = state.menuSelection < menuCapacity - 1 ? state.menuSelection += 1 : state.menuSelection = 0; // Menu == 0, then 1 - 0 is 1, menu == 1, then 1-1 is 0
                std::cout << state.menuSelection;
            }
            if (keyPressed->code == sf::Keyboard::Key::Up || keyPressed->code == sf::Keyboard::Key::W) {
                state.menuSelection = state.menuSelection > 0 ? state.menuSelection -= 1 : state.menuSelection = menuCapacity - 1;
            }

            if (keyPressed->code == sf::Keyboard::Key::Enter || keyPressed->code == sf::Keyboard::Key::Space) {
                int i = state.enemyIndex;
                if (state.menuSelection == 0) {
                    state.skillMove = SkillMove::Truck;
                    state.playerRoll = rollNum.update(state.truckProficiency * 1.5, 10);
                }
                else if (state.menuSelection == 1){
                    state.skillMove = SkillMove::Juke;
                    state.playerRoll = rollNum.update(state.jukeProficiency * 1.5, 10);
                }
                else if (state.menuSelection == 2) {
                    state.skillMove = SkillMove::Hurdle;
                    state.playerRoll = rollNum.update(state.hurdleProficiency * 1.5, 10);
                }
                judge.update(state, scene);
                menuSystem.calculateResult(state, scene);

                

            }
        }
    }

    else if (state.currentMenu == MenuState::NPCPrompt) {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Down || keyPressed->code == sf::Keyboard::Key::Up || keyPressed->code == sf::Keyboard::Key::W || keyPressed->code == sf::Keyboard::Key::S) {
                state.menuSelection = 1 - state.menuSelection; // Menu == 0, then 1 - 0 is 1, menu == 1, then 1-1 is 0
            }

            if (keyPressed->code == sf::Keyboard::Key::Enter || keyPressed->code == sf::Keyboard::Key::Space) {
                if (state.menuSelection == 0) {
                    switch (state.currentNPC) {
                    case (NPCTypes::Coach):
                        IncreaseMultiplier buyPointMultiplier;
                        buyPointMultiplier.update(state, 0.1);
                        break;
                    case (NPCTypes::Trainer):
                        IncreaseHealth buyHealth;
                        buyHealth.update(state, 15); // Change it so players can increase health by 5,15, or 25 (spends certain amount of yards)
                        break;
                    case (NPCTypes::WaterBoy):
                        IncreaseStamina buyStamina;
                        buyStamina.update(state, 15);
                        break;
                    }
                    state.currentMenu = MenuState::None;
                }
                else {
                    state.currentMenu = MenuState::None;
                }
                state.currentNPC = NPCTypes::None;
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

    else if (state.currentMenu == MenuState::LevelPrompt) {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Down || keyPressed->code == sf::Keyboard::Key::Up || keyPressed->code == sf::Keyboard::Key::W || keyPressed->code == sf::Keyboard::Key::S) {
                state.menuSelection = 1 - state.menuSelection; 
            }

            if (keyPressed->code == sf::Keyboard::Key::Enter || keyPressed->code == sf::Keyboard::Key::Space) {
                if (state.menuSelection == 0) {
                    if (scene.currentLevel == Level::Sideline) {
                        scene.SetCurrentScene(1);
                        state.playerPosition = { 390.f, 500.f };
                    }
                    else {
                        scene.SetCurrentScene(0);
                        state.playerDowns = state.maxDowns;
                        state.playerPosition = { 20.f, state.playerPosition.y };
                    }
                    state.currentMenu = MenuState::None;
                    state.enemyIndex = -1;
                }
                else {
                    state.currentMenu = MenuState::None;
                }
            }
        }
    }
}

    

void MenuSystem::calculateResult(GameState& state, SceneManager& scene) {
    int i = state.enemyIndex;

    state.menuSelection = 0;
    state.currentMenu = MenuState::ResultPrompt;
}

int RollNumber::update(int min, int max) {
    static std::mt19937 gen(std::random_device{}()); 
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

void JudgeEncounter::update(GameState& state, SceneManager& scene) {
    int playerRoll = state.playerRoll;
    int opponentRoll = state.opponentRoll;
    int result = playerRoll - opponentRoll; // Positive number -> player wins, negative number -> enemy wins


    int i = state.enemyIndex;
    ReduceHealth healthDeduction;
    ReduceDowns downsDeduction;
    ReduceStamina staminaDeduction;

    IncreaseYards yardsIncrease;

    if (state.opponentTackle == state.skill_counters[state.skillMove]) {
        result -= 5;
        std::cout << "\nYou got countered\n";
    }

    if (state.skillMove == state.tackle_counters[state.opponentTackle]) {
        result += 5;
        std::cout << "\nOpponent got countered\n";
    }
    int healthChange;
    int staminaChange;

    if (result > 0) {
        // Player wins, check what type of skill move it was. A successful hurdle causes no reduction in health but lowers stamina tremendously
        switch (state.skillMove) {
        case(SkillMove::Hurdle):
            healthChange = 0;
            staminaChange = 15;
            healthDeduction.update(state, i, healthChange, scene);
            staminaDeduction.update(state, staminaChange);
            downsDeduction.update(state, -1, scene);
            break;
        case(SkillMove::Truck):
            healthChange = 5;
            staminaChange = 5;
            healthDeduction.update(state, i, healthChange, scene);
            staminaDeduction.update(state, staminaChange);
            downsDeduction.update(state, -1, scene);
            break;
        case(SkillMove::Juke):
            healthChange = 0;
            staminaChange = 15;
            healthDeduction.update(state, i, healthChange, scene);
            staminaDeduction.update(state, staminaChange);
            downsDeduction.update(state, -1, scene);
            break;
        }
        yardsIncrease.update(state, result);
    }
    else if (result < 0) {
        switch (state.opponentTackle) {
        case(TackleType::High):
            healthChange = 25;
            staminaChange = 15;
            healthDeduction.update(state, i, healthChange, scene);
            staminaDeduction.update(state, staminaChange);
            downsDeduction.update(state, -1, scene);
            break;
        case(TackleType::Low):
            healthChange = 15;
            staminaChange = 5;
            healthDeduction.update(state, i, healthChange, scene);
            staminaDeduction.update(state, staminaChange);
            downsDeduction.update(state, -1, scene);
            break;
        case(TackleType::HitStick):
            healthChange = 20;
            staminaChange = 15;
            healthDeduction.update(state, i, healthChange, scene);
            staminaDeduction.update(state, staminaChange);
            downsDeduction.update(state, -1, scene);
            break;
        }
    }
    else{
    // Upon a tie, deduct minimal health and stamina
    }

    std::cout << "You rolled: " << playerRoll << "\nThe opponent rolled: " << opponentRoll << "\nResult: " << result << "\n";

    std::cout << "\nYou now have " << state.playerDowns << " downs remaining and " << state.totalYards << " yards to spend";
    
}