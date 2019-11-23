#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

Font font;
Text left_score_text;
int left_score;
Text right_score_text;
int right_score;

class paddle : public RectangleShape {
public:
  float x;
  float y;
  int width;
  int height;
};

class ball : public CircleShape {
public:
  float x;
  float y;
  float radius;
  bool goingLeft = true;
  bool goingUp = true;
  void reset ();
};

void ball::reset () {
  x = 400;
  y = 300;
  goingLeft = !goingLeft;
}

bool checkCollision(paddle Pad, ball Ball) {
  if ((Ball.x >= Pad.x-10 and Ball.x <= Pad.x+10) and (Ball.y >= Pad.y-35 and Ball.y <= Pad.y+35)) {
    return true;
  }
  else {
    return false;
  }
}

int main() {
  left_score = 0;
  right_score = 0;

  font.loadFromFile("libmonoreg.ttf");
  left_score_text.setFont(font);
  left_score_text.setCharacterSize(50);
  left_score_text.setFillColor(Color::Green);
  left_score_text.setPosition(100, 50);
  right_score_text.setFont(font);
  right_score_text.setCharacterSize(50);
  right_score_text.setFillColor(Color::Green);
  right_score_text.setPosition(700, 50);

  RenderWindow mainWin(VideoMode(800,600), "Pong");
  mainWin.setFramerateLimit(60);
  paddle leftPad;
  leftPad.setSize(Vector2f(10,60));
  leftPad.setFillColor(Color::Green);
  leftPad.x = 50;
  leftPad.y = 300;
  leftPad.setPosition(leftPad.x, leftPad.y);
  leftPad.setOrigin(5,30);

  paddle rightPad;
  rightPad.setSize(Vector2f(10,60));
  rightPad.setFillColor(Color::Green);
  rightPad.x = 750;
  rightPad.y = 300;
  rightPad.setPosition(rightPad.x, rightPad.y);
  rightPad.setOrigin(5,30);

  ball Ball;
  Ball.setRadius(10);
  Ball.setFillColor(Color::Green);
  Ball.x = 400;
  Ball.y = 300;
  Ball.setPosition(Ball.x, Ball.y);
  Ball.setOrigin(10, 10);

  while (mainWin.isOpen()) {
    Event event;
    while (mainWin.pollEvent(event)) {
      if (event.type == Event::Closed) {
        mainWin.close();
      }
    }
    mainWin.clear(Color::Black);
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {

    }

    if (Ball.goingLeft) { //If ball is going left, move the x coordinate left by 5 units, else move it right by 5 units.
      Ball.x -= 5;
    }
    else {
      Ball.x += 5;
    }

    if (Ball.goingUp) { //If ball is going up, move the y coordinate up by 8 units, else move it up by by 8units
      Ball.y += 8;
    }
    else {
      Ball.y -= 8;
    }

    if (Ball.y >= 590 or Ball.y <= 10) { //Check if ball hits the top or bottom edges.
      Ball.goingUp = !Ball.goingUp;
    }

    if (Ball.x >= 800) {
      left_score++;
      Ball.reset();
    }

    if (Ball.x <= 0) {
      right_score++;
      Ball.reset();
    }

    if (checkCollision(leftPad, Ball) or checkCollision(rightPad, Ball)) {
      Ball.goingLeft = !Ball.goingLeft;
    }

    if (Keyboard::isKeyPressed(Keyboard::S)) {
      leftPad.y += 8; //y coord inverted
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
      leftPad.y -= 8;
    }

    if (Keyboard::isKeyPressed(Keyboard::Down)) {
      rightPad.y += 8; //y coord inverted
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
      rightPad.y -= 8;
    }

    left_score_text.setString(to_string(left_score));
    mainWin.draw(left_score_text);
    right_score_text.setString(to_string(right_score));
    mainWin.draw(right_score_text);

    leftPad.setPosition(leftPad.x, leftPad.y);
    mainWin.draw(leftPad);

    rightPad.setPosition(rightPad.x, rightPad.y);
    mainWin.draw(rightPad);

    Ball.setPosition(Ball.x, Ball.y);
    mainWin.draw(Ball);

    mainWin.display();
  }

  return 0;
}
