#include "player.h"
#include <vector>
#include "cpputils/graphics/image.h"

void PlayerProjectile::Draw(graphics::Image &screen) {
  graphics::Color pAmmo(0, 255, 0);
  screen.DrawLine((GetX() + 2), (GetY() + 1), (GetX() + 2), (GetY() + 3),
                  pAmmo);
}

void Player::Draw(graphics::Image &screen) {
  graphics::Color black(0, 0, 0);
  graphics::Color army(19, 82, 4);
  graphics::Color green(32, 111, 14);
  screen.DrawRectangle((GetX() + 12), (GetY() + 12), 5, 20, black);
  screen.DrawRectangle((GetX() + 27), (GetY() + 12), 5, 20, black);
  screen.DrawRectangle((GetX() + 17), (GetY() + 15), 3, 14, green);
  screen.DrawRectangle((GetX() + 24), (GetY() + 15), 3, 14, green);
  screen.DrawRectangle((GetX() + 20), (GetY() + 11), 4, 19, army);
  screen.DrawRectangle((GetX() + 21), (GetY() + 8), 2, 3, army);
}

void PlayerProjectile::Move(const graphics::Image &screen) {
  SetY(GetY() - 3);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}
