#include "renderer.hpp"
#include <random>

int GenerateRandomNumber(int a, int b);
sf::RectangleShape CreateDefender();

Renderer::Renderer() {
    playerShape.setFillColor(sf::Color::Blue);
    enemyShape = CreateDefender();

    if (!font.openFromFile("assets/8-bit Arcade Out.ttf")) {// DIOWNLAOD A FONT AND LOAD HERE AFTER YOU BACK FROM WORK
        // Print error, no font
    }

}

void Renderer::draw(sf::RenderWindow& window, const GameState& state) {
    playerShape.setPosition(state.playerPosition);

    std::vector<sf::RectangleShape> enemies;
    enemyShape.setPosition(state.enemyPosition);

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
    window.draw(enemyShape);



    for (const auto& enemy : enemies) {
        window.draw(enemy);
    }

    for (const auto& npcSprite : npcSprites) {
        window.draw(npcSprite);
    }

}





sf::RectangleShape CreateDefender() {
    sf::RectangleShape enemy;
    enemy.setSize({ 30,30 });
    enemy.setOutlineColor(sf::Color::Red);
    enemy.setFillColor(sf::Color::Red);
    int x = GenerateRandomNumber(300, 700);
    int y = GenerateRandomNumber(300, 700);
    sf::Vector2f pos(x, y);
    enemy.setPosition(pos);
    return enemy;
}

// Don't use random pos for enemy yet
int GenerateRandomNumber(int a, int b) {
    static std::mt19937 gen(std::random_device{}()); // Create generator once so we don't make a new one every call
    std::uniform_int_distribution<> distrib(a, b); // Distrib transforms the random unsigned int (no defined datatype so it could be anything)

    return distrib(gen);
}

void Renderer::drawPrompt(sf::RenderWindow& window, const GameState& state) {
    sf::RectangleShape background;
    background.setFillColor(sf::Color::White);
    background.setSize({100.0f,100.0f});
    background.setPosition({ 0.0f,400.0f });

    sf::Text yesText(font, "YES - Take Health Damage", 24);
    sf::Text noText(font, "NO - Use a Down", 24);

    yesText.setPosition({ 340.f, 250.f });
    noText.setPosition({ 340.f, 300.f });

    yesText.setFillColor(sf::Color::White);
    noText.setFillColor(sf::Color::White);

    // Little triangle pointing right, used as the selection marker
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, { 0.f, 0.f });
    triangle.setPoint(1, { 0.f, 20.f });
    triangle.setPoint(2, { 15.f, 10.f });
    triangle.setFillColor(sf::Color::Yellow);

    // Position it beside whichever option is selected
    float yOffset = (state.menuSelection == 0) ? 250.f : 300.f;
    triangle.setPosition({ 310.f, yOffset });

    window.draw(yesText);
    window.draw(noText);
    window.draw(triangle);
}
