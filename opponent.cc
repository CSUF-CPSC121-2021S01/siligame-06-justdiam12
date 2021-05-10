#include "opponent.h"
#include <vector>
#include "cpputils/graphics/image.h"

void OpponentProjectile::Draw(graphics::Image& screen) {
  graphics::Color eAmmo(255, 0, 0);
  screen.DrawLine((GetX() + 2), (GetY() + 1), (GetX() + 2), (GetY() + 3),
                  eAmmo);
}

void Opponent::Draw(graphics::Image& screen) {
  graphics::Color black(0, 0, 0);
  graphics::Color grey(75, 75, 70);
  screen.DrawLine((GetX() + 19), (GetY() + 12), (GetX() + 28), (GetY() + 12),
                  grey);
  screen.DrawLine((GetX() + 17), (GetY() + 13), (GetX() + 30), (GetY() + 13),
                  grey);
  screen.DrawRectangle((GetX() + 16), (GetY() + 14), 16, 2, grey);
  screen.DrawLine((GetX() + 15), (GetY() + 16), (GetX() + 32), (GetY() + 16),
                  grey);
  screen.DrawRectangle((GetX() + 15), (GetY() + 17), 5, 9, grey);
  screen.DrawRectangle((GetX() + 28), (GetY() + 17), 5, 9, grey);
  screen.DrawRectangle((GetX() + 20), (GetY() + 17), 2, 2, black);
  screen.DrawRectangle((GetX() + 26), (GetY() + 17), 2, 2, black);
  screen.DrawRectangle((GetX() + 22), (GetY() + 17), 4, 2, grey);
  screen.DrawRectangle((GetX() + 20), (GetY() + 19), 8, 3, grey);
  screen.DrawRectangle((GetX() + 20), (GetY() + 22), 3, 3, grey);
  screen.DrawRectangle((GetX() + 25), (GetY() + 22), 3, 3, grey);
  screen.DrawRectangle((GetX() + 23), (GetY() + 22), 2, 3, black);
  screen.DrawLine((GetX() + 20), (GetY() + 25), (GetX() + 27), (GetY() + 25),
                  grey);
  screen.DrawRectangle((GetX() + 16), (GetY() + 26), 16, 2, grey);
  screen.DrawLine((GetX() + 17), (GetY() + 28), (GetX() + 20), (GetY() + 28),
                  grey);
  screen.DrawLine((GetX() + 21), (GetY() + 28), (GetX() + 26), (GetY() + 28),
                  black);
  screen.DrawLine((GetX() + 27), (GetY() + 28), (GetX() + 30), (GetY() + 28),
                  grey);
  screen.DrawLine((GetX() + 19), (GetY() + 29), (GetX() + 21), (GetY() + 29),
                  grey);
  screen.DrawLine((GetX() + 22), (GetY() + 29), (GetX() + 25), (GetY() + 29),
                  black);
  screen.DrawLine((GetX() + 26), (GetY() + 29), (GetX() + 28), (GetY() + 29),
                  grey);
  screen.DrawRectangle((GetX() + 19), (GetY() + 30), 10, 2, grey);
  screen.DrawLine((GetX() + 20), (GetY() + 32), (GetX() + 27), (GetY() + 32),
                  grey);
}

void Opponent::Move(const graphics::Image& screen) {
  if (going_right_ && GetX() + GetWidth() >= screen.GetWidth()) {
    going_right_ = false;
  } else if (!going_right_ && GetX() <= 0) {
    going_right_ = true;
  }
  int offset = going_right_ ? 1 : -1;

  SetX(GetX() + offset * 5);
  SetY(GetY() + 2);

  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}

void OpponentProjectile::Move(const graphics::Image& screen) {
  SetY(GetY() + 3);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  launch_counter += 1;
  if (launch_counter % 20 == 0) {
    std::unique_ptr<OpponentProjectile> new_launch =
        std::make_unique<OpponentProjectile>(GetX(), GetY());
    return std::move(new_launch);
  } else {
    return nullptr;
  }
}
