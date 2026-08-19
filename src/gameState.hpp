#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include<map>
#include<string>



enum class MenuState {
    None,
    Paused,
    DownPrompt,
    PlayPrompt,
    ResultPrompt,
    LevelPrompt,
    NPCPrompt,
};

enum class SkillMove {
    None,
    Truck,
    Juke,
    Hurdle,
    StiffArm,
    Slide
};

enum class NPCTypes {
    Coach,
    Trainer,
    WaterBoy
};

enum TackleType {
    High, // Countered by truck
    Low, // Countered by hurdle
    HitStick, // Countered by juke
};



struct GameState {
    sf::Vector2f playerPosition{ 390.f, 500.f };
    std::vector<sf::Vector2f> enemyPositions;
    std::vector<float> enemySpeeds;

    int playerDowns = 4;
    int playerHealth = 100;
    int healthLost = 0;
    int totalPoints = 0;
    int totalYards = 0; // Spendable, this is the in-game currency
    int pointMultiplier = 1;
    std::string currentNPC = "";

    int playerRoll;
    int opponentRoll;
    TackleType opponentTackle;

    std::map<SkillMove, TackleType> skill_counters = {
        {SkillMove::Hurdle, TackleType::High},
        {SkillMove::Truck, TackleType::Low},
        {SkillMove::Juke, TackleType::Low},  // Make hit sticks deal more damage if successful, success rate is just low
    };

    std::map<TackleType, SkillMove> tackle_counters = {
    {TackleType::High, SkillMove::Truck},
    {TackleType::Low, SkillMove::Hurdle},
    {TackleType::HitStick, SkillMove::Juke},
    };

    // --- Player Ratings ---
    int jukeProficiency = 1;
    int truckProficiency = 1;
    int hurdleProficiency = 1;

    bool gameOver = false;
    bool successfulEncounter = true;

    int playerMoveDir = 0;

    MenuState currentMenu = MenuState::None;
    SkillMove skillMove = SkillMove::None;

    int menuSelection = 0; // 0 = first option, 1 = second option
    int enemyIndex = -1;
    void getState();
};

