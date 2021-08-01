#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "Platform/Platform.hpp"

using namespace sf;
void updateBranches(int seed);

const int WIDTH = 1920, HEIGHT = 1080;
const int CENTER_X = WIDTH / 2, CENTER_Y = HEIGHT / 2;
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main() {
  VideoMode vm(WIDTH, HEIGHT);

  RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

  Texture textureBackground;

  textureBackground.loadFromFile("graphics/background.png");

  Sprite spBackground;
  spBackground.setTexture(textureBackground);
  spBackground.setPosition(0, 0);

  // Make a tree sp
  Texture textureTree;
  textureTree.loadFromFile("graphics/tree.png");
  Sprite spTree;
  spTree.setTexture(textureTree);
  spTree.setPosition(810, 0);

  // Prepare the bee
  Texture textureBee;
  textureBee.loadFromFile("graphics/bee.png");
  Sprite spBee;
  spBee.setTexture(textureBee);
  spBee.setPosition(0, 800);

  bool beeActive = false;
  float beeSpeed = 0.0f;
  Texture textureCloud;
  textureCloud.loadFromFile("graphics/cloud.png");
  const int NUM_CLOUDS = 6;
  Sprite clouds[NUM_CLOUDS];
  int cloudSpeeds[NUM_CLOUDS];
  bool cloudsActive[NUM_CLOUDS];
  for (int i = 0; i < NUM_CLOUDS; i++) {
    clouds[i].setTexture(textureCloud);
    clouds[i].setPosition(-300, i * 150);
    cloudsActive[i] = false;
    cloudSpeeds[i] = 0;
  }

  // Variables to control time itself
  Clock clock;
  // Time bar
  RectangleShape timeBar;
  float timeBarStartWidth = 400, timeBarHeight = 80;
  timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
  timeBar.setFillColor(Color::Red);
  timeBar.setPosition((CENTER_X)-timeBarStartWidth / 2, 980);

  Time gameTimeTotal;
  float timeRemaining = 6.0f;
  float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

  bool paused = true;
  int score = 0;

  Text messageText, scoreText;
  Font font;
  font.loadFromFile("fonts/KOMIKAP_.ttf");

  messageText.setFont(font);
  scoreText.setFont(font);
  messageText.setString("Press Enter to start!");
  scoreText.setString("Score = 0");
  messageText.setCharacterSize(75);
  scoreText.setCharacterSize(100);
  messageText.setFillColor(Color::White);
  scoreText.setFillColor(Color::White);
  FloatRect textRect = messageText.getLocalBounds();
  messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                        textRect.top + textRect.height / 2.0f);
  messageText.setPosition(CENTER_X, CENTER_Y);
  scoreText.setPosition(20, 20);
  Texture textureBranch;
  textureBranch.loadFromFile("graphics/branch.png");

  // Set the texture for each branch sp
  for (int i = 0; i < NUM_BRANCHES; i++) {
    branches[i].setTexture(textureBranch);
    branches[i].setPosition(-2000, -2000);

    // Set the sp's origin to dead center
    // We can then spin it round without changing its position
    branches[i].setOrigin(220, 20);
  }

  // Prepare the player
  Texture texturePlayer;
  texturePlayer.loadFromFile("graphics/player.png");
  Sprite spPlayer;
  spPlayer.setTexture(texturePlayer);
  spPlayer.setPosition(580, 720);
  side playerSide = side::LEFT;

  // Prepare the gravestone
  Texture textureRIP;
  textureRIP.loadFromFile("graphics/rip.png");
  Sprite spRIP;
  spRIP.setTexture(textureRIP);
  spRIP.setPosition(600, 860);

  // Prepare the axe
  Texture textureAxe;
  textureAxe.loadFromFile("graphics/axe.png");
  Sprite spAxe;
  spAxe.setTexture(textureAxe);
  spAxe.setPosition(700, 830);

  // Line the axe up with the tree
  const float AXE_POSITION_LEFT = 700, AXE_POSITION_RIGHT = 1075;
  Texture textureLog;
  textureLog.loadFromFile("graphics/log.png");
  Sprite spLog;
  spLog.setTexture(textureLog);
  spLog.setPosition(810, 720);

  bool logActive = false;
  float logSpeedX = 1000, logSpeedY = -1500;
  bool acceptInput = false;

  // Prepare the sound
  SoundBuffer chopBuffer;
  chopBuffer.loadFromFile("sound/chop.wav");
  Sound chop;
  chop.setBuffer(chopBuffer);

  SoundBuffer deathBuffer;
  deathBuffer.loadFromFile("sound/death.wav");
  Sound death;
  death.setBuffer(deathBuffer);

  // Out of time
  SoundBuffer ootBuffer;
  ootBuffer.loadFromFile("sound/out_of_time.wav");
  Sound outOfTime;
  outOfTime.setBuffer(ootBuffer);

  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::KeyReleased && !paused) {
        acceptInput = true;
        spAxe.setPosition(2000, spAxe.getPosition().y);
      }
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }

    // Start the game
    if (Keyboard::isKeyPressed(Keyboard::Return)) {
      paused = false;

      // Reset the time and the score
      score = 0;
      timeRemaining = 6;

      // Make all the branches disappear
      for (int i = 1; i < NUM_BRANCHES; i++) {
        branchPositions[i] = side::NONE;
      }

      // Make sure the gravestone is hidden
      spRIP.setPosition(675, 2000);
      spPlayer.setPosition(580, 720);

      acceptInput = true;
    }

    if (acceptInput) {
      if (Keyboard::isKeyPressed(Keyboard::Right)) {
        playerSide = side::RIGHT;
        score++;
        timeRemaining += (2 / score) + .15;

        spAxe.setPosition(AXE_POSITION_RIGHT, spAxe.getPosition().y);

        spPlayer.setPosition(1200, 720);

        // update the branches
        updateBranches(score);

        // set the log flying to the left
        spLog.setPosition(810, 720);
        logSpeedX = -5000;
        logActive = true;
        acceptInput = false;
        chop.play();
      }

      // Handle the left cursor key
      if (Keyboard::isKeyPressed(Keyboard::Left)) {
        playerSide = side::LEFT;
        score++;

        // Add to the amount of time remaining
        timeRemaining += (2 / score) + .15;

        spAxe.setPosition(AXE_POSITION_LEFT, spAxe.getPosition().y);

        spPlayer.setPosition(580, 720);

        // update the branches
        updateBranches(score);

        // set the log flying
        spLog.setPosition(810, 720);
        logSpeedX = 5000;
        logActive = true;

        acceptInput = false;

        // Play a chop sound
        chop.play();
      }
    }

    if (!paused) {
      // Measure time
      Time dt = clock.restart();
      timeRemaining -= dt.asSeconds();
      // size up the time bar
      timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

      if (timeRemaining <= 0.0f) {
        paused = true;
        messageText.setString("Out of time!!");

        FloatRect textRect = messageText.getLocalBounds();
        messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                              textRect.top + textRect.height / 2.0f);

        messageText.setPosition(CENTER_X, CENTER_Y);

        outOfTime.play();
      }

      // Setup the bee
      if (!beeActive) {
        srand((int)time(0) * 10);
        beeSpeed = (rand() % 200) + 200;
        srand((int)time(0) * 10);
        float height = (rand() % 500) + 500;
        spBee.setPosition(2000, height);
        beeActive = true;
      } else {
        spBee.setPosition(spBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                          spBee.getPosition().y);

        if (spBee.getPosition().x < -100) beeActive = false;
      }

      for (int i = 0; i < NUM_CLOUDS; i++) {
        if (!cloudsActive[i]) {
          srand((int)time(0) * i);
          cloudSpeeds[i] = (rand() % 200);

          srand((int)time(0) * i);
          float height = (rand() % 150);
          clouds[i].setPosition(-200, height);
          cloudsActive[i] = true;
        } else {
          clouds[i].setPosition(clouds[i].getPosition().x + (cloudSpeeds[i] * dt.asSeconds()),
                                clouds[i].getPosition().y);
          if (clouds[i].getPosition().x > WIDTH) cloudsActive[i] = false;
        }
      }

      std::stringstream ss;
      ss << "Score = " << score;
      scoreText.setString(ss.str());

      // update the branch sps
      for (int i = 0; i < NUM_BRANCHES; i++) {
        float height = i * 150;

        if (branchPositions[i] == side::LEFT) {
          // Move the sp to the left side
          branches[i].setPosition(610, height);
          // Flip the sp round the other way
          branches[i].setOrigin(220, 40);
          branches[i].setRotation(180);
        } else if (branchPositions[i] == side::RIGHT) {
          // Move the sp to the right side
          branches[i].setPosition(1330, height);
          // Set the sp rotation to normal
          branches[i].setOrigin(220, 40);
          branches[i].setRotation(0);
        } else {
          branches[i].setPosition(3000, height);
        }
      }

      // Handle a flying log
      if (logActive) {
        spLog.setPosition(spLog.getPosition().x + (logSpeedX * dt.asSeconds()),
                          spLog.getPosition().y + (logSpeedY * dt.asSeconds()));

        if (spLog.getPosition().x < -100 || spLog.getPosition().x > 2000) {
          // Set it up ready to be a whole new cloud next frame
          logActive = false;
          spLog.setPosition(810, 720);
        }
      }

      // dead
      if (branchPositions[5] == playerSide) {
        paused = true;
        acceptInput = false;

        // Draw the gravestone
        spRIP.setPosition(525, 760);
        spPlayer.setPosition(2000, 660);
        messageText.setString("SQUISHED!!");
        FloatRect textRect = messageText.getLocalBounds();
        messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                              textRect.top + textRect.height / 2.0f);

        messageText.setPosition(CENTER_X, CENTER_Y);
        death.play();
      }

    }  // End if(!paused)

    window.clear();
    window.draw(spBackground);
    for (int i = 0; i < NUM_CLOUDS; i++) window.draw(clouds[i]);
    for (int i = 0; i < NUM_BRANCHES; i++) window.draw(branches[i]);

    window.draw(spTree);
    window.draw(spPlayer);
    window.draw(spAxe);
    window.draw(spLog);
    window.draw(spRIP);
    window.draw(spBee);
    window.draw(scoreText);
    window.draw(timeBar);

    if (paused) {
      window.draw(messageText);
    }
    window.display();
  }

  return 0;
}

// Function definition
void updateBranches(int seed) {
  // Move all the branches down one place
  for (int j = NUM_BRANCHES - 1; j > 0; j--) {
    branchPositions[j] = branchPositions[j - 1];
  }

  // LEFT, RIGHT or NONE
  srand((int)time(0) + seed);
  int r = (rand() % 5);
  switch (r) {
    case 0:
      branchPositions[0] = side::LEFT;
      break;
    case 1:
      branchPositions[0] = side::RIGHT;
      break;
    default:
      branchPositions[0] = side::NONE;
      break;
  }
}
