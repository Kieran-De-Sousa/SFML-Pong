
#ifndef PONG_GAME_H
#define PONG_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);
  void mouseClicked(sf::Event event);

 private:
  void vectors(float dt, bool ball_reverse_x, bool ball_reverse_y);
  void ballSpawn();
  void collisionChecker ();

  sf::RenderWindow& window;
  //UI booleans
  bool start_menu = true;
  bool pause_menu = false;
  bool mode_ai = false;
  bool mode_2p = false;

  //Sprites
  sf::Sprite ball;
  sf::Texture ball_texture;
  sf::Sprite p1_paddle;
  sf::Texture p1_texture;
  sf::Sprite p2_paddle;
  sf::Texture p2_texture;

  //Text related
  sf::Font font;
  sf::Text start_text;
  sf::Text control_text;
  sf::Text quit_text;
  sf::Text pause_text;
  sf::Text mode_swap_text;
  sf::Text mode_ai_selected_text;
  sf::Text mode_2p_selected_text;
  sf::Text p1_score_text;
  sf::Text p2_score_text;
  sf::Text speed_ball_text;

  //Variables used for ball vectors
  int speed_ball = 300;
  int speed_paddle = 400;
  int ball_direction_x = 1.0f * speed_ball;
  int ball_direction_y = 1.0f * speed_ball;
  int ball_vector[2] = {ball_direction_x, ball_direction_y};
  bool ball_reverse_x = false;
  bool ball_reverse_y = false;

  //Paddle variables
  bool p1_y = true;
  bool p1_idle = true;
  int p1_score = 0;
  bool p2_y = true;
  bool p2_idle = true;
  int p2_score = 0;

};

#endif // PONG_GAME_H
