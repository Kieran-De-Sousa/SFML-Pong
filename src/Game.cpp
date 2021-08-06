
#include "Game.h"
#include <iostream>
#include <random>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  // Text settings //
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Font could not be loaded.\n";
  }
  p1_score_text.setString(std::to_string(p1_score));
  p1_score_text.setFont(font);
  p1_score_text.setCharacterSize(55);
  p1_score_text.setFillColor(sf::Color(255, 255, 255, 155));
  p1_score_text.setPosition(
    window.getSize().x * 0.25,
    window.getSize().y/10 - p1_score_text.getGlobalBounds().height/10);

  p2_score_text.setString(std::to_string(p2_score));
  p2_score_text.setFont(font);
  p2_score_text.setCharacterSize(55);
  p2_score_text.setFillColor(sf::Color(255, 255, 255, 155));
  p2_score_text.setPosition(
    window.getSize().x * 0.75,
    window.getSize().y/10 - p2_score_text.getGlobalBounds().height/10);

  start_text.setString("Press the 'F' key for single player and 'G' for multiplayer.");
  start_text.setFont(font);
  start_text.setCharacterSize(30);
  start_text.setFillColor(sf::Color(255, 255, 255, 255));
  start_text.setPosition(
    window.getSize().x/2 - start_text.getGlobalBounds().width/2,
    window.getSize().y/2 - start_text.getGlobalBounds().height/2);

  control_text.setString("P1: 'W' = UP  'S' = DOWN - P2: 'UP' = UP  'DOWN' = DOWN");
  control_text.setFont(font);
  control_text.setCharacterSize(30);
  control_text.setFillColor(sf::Color(255, 255, 255, 255));
  control_text.setPosition(
    window.getSize().x/2 - control_text.getGlobalBounds().width/2,
    window.getSize().y/1.5 - control_text.getGlobalBounds().height/1.5);

  pause_text.setString("Press P to pause the game.");
  pause_text.setFont(font);
  pause_text.setCharacterSize(20);
  pause_text.setFillColor(sf::Color(255, 255, 255, 155));
  pause_text.setPosition(
    window.getSize().x/2 - pause_text.getGlobalBounds().width/2,
    window.getSize().y/1.2 - pause_text.getGlobalBounds().height/1.2);

  quit_text.setString("Press Q to quit the game.");
  quit_text.setFont(font);
  quit_text.setCharacterSize(20);
  quit_text.setFillColor(sf::Color(255, 255, 255, 155));
  quit_text.setPosition(
    window.getSize().x/2 - quit_text.getGlobalBounds().width/2,
    window.getSize().y/1.1 - quit_text.getGlobalBounds().height/1.1);

  speed_ball_text.setString("Speed: " + std::to_string(ball_vector[0]));
  speed_ball_text.setFont(font);
  speed_ball_text.setCharacterSize(20);
  speed_ball_text.setFillColor(sf::Color(255, 255, 255, 155));
  speed_ball_text.setPosition(
    window.getSize().x/2 - speed_ball_text.getGlobalBounds().width/2,
    window.getSize().y/10 - speed_ball_text.getGlobalBounds().height/10);

  mode_swap_text.setString("Whilst paused, you may swap modes: "
                           "'F' Single Player - 'G' Multiplayer");
  mode_swap_text.setFont(font);
  mode_swap_text.setCharacterSize(27);
  mode_swap_text.setFillColor(sf::Color(0, 255, 0, 255));
  mode_swap_text.setPosition(
    window.getSize().x/2 - mode_swap_text.getGlobalBounds().width/2,
    window.getSize().y/2 - mode_swap_text.getGlobalBounds().height/2);

  mode_ai_selected_text.setString("Mode selected: Single Player");
  mode_ai_selected_text.setFont(font);
  mode_ai_selected_text.setCharacterSize(27);
  mode_ai_selected_text.setFillColor(sf::Color(0, 255, 0, 255));
  mode_ai_selected_text.setPosition(
    window.getSize().x/2 - mode_ai_selected_text.getGlobalBounds().width/2,
    window.getSize().y/1.5 - mode_ai_selected_text.getGlobalBounds().height/1.5);

  mode_2p_selected_text.setString("Mode selected: Multiplayer");
  mode_2p_selected_text.setFont(font);
  mode_2p_selected_text.setCharacterSize(27);
  mode_2p_selected_text.setFillColor(sf::Color(0, 255, 0, 255));
  mode_2p_selected_text.setPosition(
    window.getSize().x/2 - mode_2p_selected_text.getGlobalBounds().width/2,
    window.getSize().y/1.5 - mode_2p_selected_text.getGlobalBounds().height/1.5);

  // Sprite settings //
  if(!ball_texture.loadFromFile("Data/Images/ballGrey.png"))
  {
    std::cout << "Ball texture could not be loaded.\n";
  }
  ball.setTexture(ball_texture);
  ball.setPosition(
    window.getSize().x/2 - ball.getGlobalBounds().width/2,
    window.getSize().y/2 - ball.getGlobalBounds().height/2);

  if (!p1_texture.loadFromFile("Data/Images/paddleBlue.png"))
  {
    std::cout << "Player 1 paddle texture could not be loaded.\n";
  }
  p1_paddle.setTexture(p1_texture);
  p1_paddle.setRotation(90.f);
  p1_paddle.setPosition(
    0,
    window.getSize().y/2 - p1_paddle.getGlobalBounds().height/2);
  p1_paddle.setOrigin(sf::Vector2f(50, 50));

  if (!p2_texture.loadFromFile("Data/Images/paddleRed.png"))
  {
    std::cout << "Player 2 paddle texture could not be loaded.\n";
  }
  p2_paddle.setTexture(p2_texture);
  p2_paddle.setRotation(90.f);
  p2_paddle.setPosition(
    1010,
    window.getSize().y/2 - p2_paddle.getGlobalBounds().height/2);
  p2_paddle.setOrigin(sf::Vector2f(50, 50));

  return true;
}

void Game::update(float dt)
{
  if (pause_menu == false)
  {
    vectors((dt), (ball_reverse_x), (ball_reverse_y));
    collisionChecker();

    // P1 paddle movement code
    if (p1_idle == true)
    {
      p1_paddle.move(0, 0);
    }
    else if (p1_idle == false)
    {
      if (p1_y == true)
      {
        p1_paddle.move(0.0f, -1.0f * speed_paddle * dt);
      }
      else if (p1_y == false)
      {
        p1_paddle.move(0.0f, 1.0f * speed_paddle * dt);
      }
    }
    // P2 paddle movement code
    if (p2_idle == true)
    {
      p2_paddle.move(0, 0);
    }
    else if (p2_idle == false)
    {
      if (p2_y == true)
      {
        p2_paddle.move(0.0f, -1.0f * speed_paddle * dt);
      }
      else if (p2_y == false)
      {
        p2_paddle.move(0.0f, 1.0f * speed_paddle * dt);
      }
    }
    // AI paddle movement code
    if (mode_ai == true)
    {
      if (ball_reverse_x == true)
      {
        if (ball.getPosition().y > p2_paddle.getPosition().y)
        {
          p2_paddle.move(0.0f, 1.0f * (speed_paddle * 0.7) * dt);
        }
        else if (ball.getPosition().y < p2_paddle.getPosition().y)
        {
          p2_paddle.move(0.0f, -1.0f * (speed_paddle * 0.7) * dt);
        }
      }
    }
    p1_score_text.setString(std::to_string(p1_score));
    p2_score_text.setString(std::to_string(p2_score));
    speed_ball_text.setString("Speed: " + std::to_string(ball_vector[0]));
  }
}

void Game::render()
{
  if (start_menu)
  {
    window.draw(start_text);
    window.draw(control_text);
  }
  else if (!start_menu && pause_menu == true)
  {
    window.draw(p1_score_text);
    window.draw(p2_score_text);
    window.draw(quit_text);
    window.draw(pause_text);
    window.draw(speed_ball_text);
    window.draw(ball);
    window.draw(p1_paddle);
    window.draw(p2_paddle);
    window.draw(mode_swap_text);
    if (mode_ai == true)
    {
      window.draw(mode_ai_selected_text);
    }
    else if (mode_2p == true)
    {
      window.draw(mode_2p_selected_text);
    }
  }
  else if (!start_menu && !pause_menu)
  {
    window.draw(p1_score_text);
    window.draw(p2_score_text);
    window.draw(quit_text);
    window.draw(pause_text);
    window.draw(speed_ball_text);
    window.draw(ball);
    window.draw(p1_paddle);
    window.draw(p2_paddle);
  }
}

void Game::keyPressed(sf::Event event)
{
  if (pause_menu == true || start_menu == true)
  {
    if ((event.key.code == sf::Keyboard::F))
    {
      start_menu = false;
      mode_ai = true;
      mode_2p = false;
    }
    else if ((event.key.code == sf::Keyboard::G))
    {
      start_menu = false;
      mode_ai = false;
      mode_2p = true;
    }
  }

  if (!start_menu)
  {
    // Paddle movement code - Player 1
    if (
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
      p1_idle = false;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
      {
        p1_y = true;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
      {
        p1_y = false;
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
    {
      pause_menu = !pause_menu;
    }
    // Movement code relating to which game mode the user picks
    if (mode_2p == true)
    {
      // Paddle movement code - Player 2
      if (
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
      {
        p2_idle = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
          p2_y = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
          p2_y = false;
        }
      }
    }
  }

  if ((event.key.code == sf::Keyboard::Q))
  {
    window.close();
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}
// Handles vectors of ball
void Game::vectors(float dt, bool ball_reverse_x, bool ball_reverse_y)
{
  if (!start_menu)
  {
    if (ball_reverse_x == true && ball_reverse_y == true)
    {
      ball.move(ball_vector[0] * dt, ball_vector[1] * dt);
    }
    else if (ball_reverse_x == true && ball_reverse_y == false)
    {
      ball.move(ball_vector[0] * dt, (ball_vector[1] * -1) * dt);
    }
    else if (ball_reverse_x == false && ball_reverse_y == true)
    {
      ball.move((ball_vector[0] * -1) * dt, ball_vector[1] * dt);
    }
    else
    {
      ball.move((ball_vector[0] * -1) * dt, (ball_vector[1] * -1) * dt);
    }
  }
}

void Game::ballSpawn()
{
  int random_num = rand() % 600 + 120;
  ball.setPosition(
    window.getSize().x/2 - ball.getGlobalBounds().width/2, random_num);
}

void Game::collisionChecker()
{
  // Checks for ball hitting the paddles. && ensures that the ball doesn't get stuck inside paddle
  if (ball.getGlobalBounds().intersects(p1_paddle.getGlobalBounds()) &&
      ball_reverse_x == false)
  {
    ball_reverse_x = !ball_reverse_x;
    ball_vector[0] += 30;
  }
  else if (ball.getGlobalBounds().intersects(p2_paddle.getGlobalBounds()) &&
      ball_reverse_x == true)
  {
    ball_reverse_x = !ball_reverse_x;
    ball_vector[0] += 30;
  }
  // Checks for ball hitting the top and bottom of the screen
  if ((ball.getPosition().y >
       (window.getSize().y - ball.getGlobalBounds().height)) || (ball.getPosition().y < 0))
  {
    ball_reverse_y = !ball_reverse_y;
  }

  // Checks for ball touching the sides of the screen. ballSpawn() creates a new spawn location
  if ((ball.getPosition().x >
       (window.getSize().x - ball.getGlobalBounds().width)))
  {
    ballSpawn();
    ball_vector[0] = ball_direction_x;
    ball_reverse_x = !ball_reverse_x;
    p1_score = p1_score + 1;
    p1_paddle.setPosition(
      0,
      window.getSize().y/2 - p1_paddle.getGlobalBounds().height/2);
    p2_paddle.setPosition(
      1010,
      window.getSize().y/2 - p2_paddle.getGlobalBounds().height/2);
  }
  else if (ball.getPosition().x < 0)
  {
    ballSpawn();
    ball_vector[0] = ball_direction_x;
    ball_reverse_x = !ball_reverse_x;
    p2_score = p2_score + 1;
    p1_paddle.setPosition(
      0,
      window.getSize().y/2 - p1_paddle.getGlobalBounds().height/2);
    p2_paddle.setPosition(
      1010,
      window.getSize().y/2 - p2_paddle.getGlobalBounds().height/2);
  }

  // Checks if player 1 paddle touches top or bottom of screen
  if (p1_paddle.getPosition().y > window.getSize().y -
                                    p1_paddle.getLocalBounds().height)
  {
    p1_paddle.setPosition(0,window.getSize().y
                               - p1_paddle.getLocalBounds().height);
    p1_idle = true;
  }
  else if (p1_paddle.getPosition().y < p1_paddle.getLocalBounds().height)
  {
    p1_paddle.setPosition(0,(p1_paddle.getLocalBounds().height));
    p1_idle = true;
  }

  // Checks if player 2 paddle touches top or bottom of screen (only in 2p)
  if (mode_2p == true)
  {
    if (p2_paddle.getPosition().y > window.getSize().y -
                                    p2_paddle.getLocalBounds().height)
    {
      p2_paddle.setPosition(1010,window.getSize().y
                                 - p2_paddle.getLocalBounds().height);
      p2_idle = true;
    }
    else if (p2_paddle.getPosition().y < p2_paddle.getLocalBounds().height)
    {
      p2_paddle.setPosition(1010,(p2_paddle.getLocalBounds().height));
      p2_idle = true;
    }
  }
}


