#include "renderer.hpp"
#include <random>
#include <iostream>

int GenerateRandomNumber(int a, int b);
sf::RectangleShape CreateDefender();

Renderer::Renderer() {
    playerShape.setFillColor(sf::Color::Blue);

    if (!font.openFromFile("C:/Users/mamem/VS 2026 PROJECTS/Endzone-Game/src/assets/DigitalArcade.ttf")) {// DIOWNLAOD A FONT AND LOAD HERE AFTER YOU BACK FROM WORK
        std::cerr << "Couldn't find the requested font";
    }

}

void Renderer::draw(sf::RenderWindow& window, const GameState& state) {
    playerShape.setPosition(state.playerPosition);

    std::vector<sf::RectangleShape> enemies;

    for(const sf::Vector2f& enemy : state.enemyPositions)
    {
        sf::RectangleShape enemySprite;
        enemySprite.setSize({ 40,40 });
        enemySprite.setOutlineColor(sf::Color::Red);
        enemySprite.setFillColor(sf::Color::Blue);
        enemySprite.setPosition(enemy);
        enemies.push_back(enemySprite);
    }
    std::vector<sf::CircleShape> npcSprites;

    for (auto& [id,npc] :state.npcs) {
        sf::CircleShape npcSprite;
        npcSprite.setRadius({ 40.0f });
        npcSprite.setOutlineColor(sf::Color::Yellow);
        npcSprite.setFillColor(sf::Color::Yellow);
        npcSprite.setPosition({npc.x, npc.y});
        npcSprites.push_back(npcSprite);
    }

    window.draw(playerShape);



    for (const auto& enemy : enemies) {
        window.draw(enemy);
    }

    for (const auto& npcSprite : npcSprites) {
        window.draw(npcSprite);
    }

}


// Don't use random pos for enemy yet
int GenerateRandomNumber(int a, int b) {
    static std::mt19937 gen(std::random_device{}()); // Create generator once so we don't make a new one every call
    std::uniform_int_distribution<> distrib(a, b); // Distrib transforms the random unsigned int (no defined datatype so it could be anything)

    return distrib(gen);
}

void Renderer::drawDownPrompt(sf::RenderWindow& window, const GameState& state) {
    sf::RectangleShape background;
    background.setFillColor(sf::Color::White);
    background.setSize({600.0f,200.0f});
    background.setPosition({ 100.0f,450.0f });

    sf::Text yesText(font, "Play Down", 24);
    sf::Text noText(font, "Forfeit Down", 24);

    yesText.setPosition({ 200.f, 450.f });
    noText.setPosition({ 200.f, 500.f });

    yesText.setFillColor(sf::Color::Black);
    noText.setFillColor(sf::Color::Black);

    // Little triangle pointing right, used as selection marker
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, { 0.f, 0.f });
    triangle.setPoint(1, { 0.f, 20.f });
    triangle.setPoint(2, { 15.f, 10.f });
    triangle.setFillColor(sf::Color::Yellow);

    // Position it beside whichever option is selected
    float yOffset = (state.menuSelection == 0) ? 450.f : 500.f;
    triangle.setPosition({ 175.f, yOffset + 9.f});

    window.draw(background);
    window.draw(yesText);
    window.draw(noText);
    window.draw(triangle);
}

void Renderer::drawPlayPrompt(sf::RenderWindow& window, const GameState& state) {
    sf::RectangleShape background;
    background.setFillColor(sf::Color::White);
    background.setSize({ 600.0f,200.0f });
    background.setPosition({ 100.0f,450.0f });

    sf::Text actionText1(font, "Truck", 24);
    sf::Text actionText2(font, "Juke", 24);
    sf::Text actionText3(font, "Hurdle", 24);

    actionText1.setPosition({ 200.f, 450.f });
    actionText2.setPosition({ 200.f, 500.f });
    actionText3.setPosition({ 200.f, 550.f });

    actionText1.setFillColor(sf::Color::Black);
    actionText2.setFillColor(sf::Color::Black);
    actionText3.setFillColor(sf::Color::Black);

    // Little triangle pointing right, used as selection marker
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, { 0.f, 0.f });
    triangle.setPoint(1, { 0.f, 20.f });
    triangle.setPoint(2, { 15.f, 10.f });
    triangle.setFillColor(sf::Color::Yellow);

    float yOffset = 0;

    switch (state.menuSelection) {
    case (0):
        yOffset = 450.f;
        break;
    case(1):
        yOffset = 500.f;
        break;
    case(2):
        yOffset = 550.f;
        break;
    }
    triangle.setPosition({ 175.f, yOffset + 9.f });

    window.draw(background);
    window.draw(actionText1);
    window.draw(actionText2);
    window.draw(actionText3);
    window.draw(triangle);
}

void Renderer::drawResultPrompt(sf::RenderWindow& window, const GameState& state) {
    sf::RectangleShape background;
    background.setFillColor(sf::Color::White);
    background.setSize({ 600.0f,200.0f });
    background.setPosition({ 100.0f,450.0f });

    sf::Text resultText(font, std::to_string(state.playerHealth), 24);
    std::string responseText;
    if (state.successfulEncounter) 
    {
        switch (state.skillMove) 
        {
        case(SkillMove::Truck):
            responseText = "You trucked the defender! You lost: " + std::to_string(state.healthLost) + " durability\nYour durability is now : " + std::to_string(state.playerHealth);
            resultText.setString(responseText);
            break;
        case(SkillMove::Juke):
            responseText = "You hem hemmed the defender! You lost: " + std::to_string(state.healthLost) + " durability\nYour durability is now: " + std::to_string(state.playerHealth);
            resultText.setString(responseText);
            break;
        case(SkillMove::Hurdle):
            responseText = "You jumped over your defender! You lost: " + std::to_string(state.healthLost) + " durability\nYour durability is now: " + std::to_string(state.playerHealth);
            resultText.setString(responseText);
            break;
        }
    }
    else 
    {
        switch (state.skillMove) 
        {
        case(SkillMove::Truck):
            responseText = "You trucked the defender badly! You lost: " + std::to_string(state.healthLost) + " durability\nYour durability is now : " + std::to_string(state.playerHealth);
            resultText.setString(responseText);
            break;
        case(SkillMove::Juke):
            responseText = "You failed to juke the defender! You lost: " + std::to_string(state.healthLost) + " durability\nYour durability is now: " + std::to_string(state.playerHealth);
            resultText.setString(responseText);
            break;
        case(SkillMove::Hurdle):
            responseText = "You failed a hurdle! You lost: " + std::to_string(state.healthLost) + " durability\nYour durability is now: " + std::to_string(state.playerHealth);
            resultText.setString(responseText);
            break;
        }
    }


    resultText.setPosition({ 150.f, 450.f });

    resultText.setFillColor(sf::Color::Black);


    window.draw(background);
    window.draw(resultText);
}
