#ifndef OPPONENT_H
#define OPPONENT_H

#include <vector>
#include "cpputils/graphics/image.h"
#include "game_element.h"

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : OpponentProjectile(0, 0) {}

  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  void Draw(graphics::Image& screen) override;

  void Move(const graphics::Image& screen) override;
};

class Opponent : public GameElement {
 public:
  Opponent() : Opponent(0, 0) {}

  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}

  std::unique_ptr<OpponentProjectile> LaunchProjectile();

  void Draw(graphics::Image& screen) override;

  void Move(const graphics::Image& screen) override;

 private:
  bool going_right_ = true;
  int launch_counter = 0;
};

#endif
