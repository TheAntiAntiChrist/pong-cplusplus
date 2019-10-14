#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

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
};

bool checkCollision(paddle Pad, ball Ball) {
  if (Ball.x == Pad.x and (Ball.y >= Pad.y-35 and Ball.y <= Pad.y+35)) {
    return true;
  }
  else {
    return false;
  }
}

int main() {
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

    if (Ball.goingLeft) {
      Ball.x -= 5;
    }
    else {
      Ball.x += 5;
    }

    if (Ball.goingUp) {
      Ball.y += 8;
    }
    else {
      Ball.y -= 8;
    }

    if (Ball.y >= 590 or Ball.y <= 10) {
      Ball.goingUp = !Ball.goingUp;
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
