#include "game_element.h"
#include "player.h"
#include "opponent.h"

#ifndef POWER_UP_H
#define POWER_UP_H

class PowerUp : public GameElement {
 public:
  void Draw(graphics::Image& screen) override;
 private:
}

#endif
