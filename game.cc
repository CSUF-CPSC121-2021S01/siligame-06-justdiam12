#include "game.h"
#include <iostream>
#include "cpputils/graphics/image_event.h"

void Game::Init() {
  my_player_.SetX(375);
  my_player_.SetY(500);
  game_screen_.AddMouseEventListener(*this);
  game_screen_.AddAnimationEventListener(*this);
}

void Game::CreateOpponents() {
  for (int i = 0; i < 5; i++) {
    std::unique_ptr<Opponent> my_opponent =
        std::make_unique<Opponent>(100 * i, 20);
    opponents_.push_back(std::move(my_opponent));
  }
}

void Game::CreateOpponentProjectiles() {
  for (int i = 0; i < 5; i++) {
    std::unique_ptr<OpponentProjectile> my_opponent_projectile =
        std::make_unique<OpponentProjectile>(100 * i, 100);
    opponent_projectiles_.push_back(std::move(my_opponent_projectile));
  }
}

void Game::CreatePlayerProjectiles() {
  for (int i = 0; i < 5; i++) {
    std::unique_ptr<PlayerProjectile> my_projectile =
        std::make_unique<PlayerProjectile>(100 * i, 450);
    player_projectiles_.push_back(std::move(my_projectile));
  }
}

void Game::MoveGameElements() {
  for (int i = 0; i < opponents_.size(); i++) {
    if ((*opponents_[i]).GetIsActive()) {
      (*opponents_[i]).Move(game_screen_);
    }
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if ((*opponent_projectiles_[i]).GetIsActive()) {
      (*opponent_projectiles_[i]).Move(game_screen_);
    }
  }
  for (int i = 0; i < player_projectiles_.size(); i++) {
    if ((*player_projectiles_[i]).GetIsActive()) {
      (*player_projectiles_[i]).Move(game_screen_);
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponents_.size(); i++) {
    if ((*opponents_[i]).GetIsActive() && my_player_.GetIsActive() &&
        my_player_.IntersectsWith(opponents_[i].get())) {
      (*opponents_[i]).SetIsActive(false);
      my_player_.SetIsActive(false);
      has_lost_ = true;
    } else {
      for (int j = 0; j < player_projectiles_.size(); j++) {
        if ((*opponents_[i]).GetIsActive() &&
            (*player_projectiles_[j]).GetIsActive() &&
            (*player_projectiles_[j]).IntersectsWith(opponents_[i].get())) {
          (*opponents_[i]).SetIsActive(false);
          (*player_projectiles_[j]).SetIsActive(false);
          if (my_player_.GetIsActive()) {
            score_ += 1;
          }
        }
      }
    }
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if ((*opponent_projectiles_[i]).GetIsActive() && my_player_.GetIsActive() &&
        my_player_.IntersectsWith(opponent_projectiles_[i].get())) {
      (*opponent_projectiles_[i]).SetIsActive(false);
      my_player_.SetIsActive(false);
      has_lost_ = true;
    }
  }
}

void Game::UpdateScreen() {
  game_screen_.DrawRectangle(0, 0, game_screen_.GetWidth(),
                             game_screen_.GetHeight(),
                             graphics::Color(255, 255, 255));
  if (my_player_.GetIsActive()) {
    my_player_.Draw(game_screen_);
  }
  for (int i = 0; i < opponents_.size(); i++) {
    if ((*opponents_[i]).GetIsActive()) {
      (*opponents_[i]).Draw(game_screen_);
    }
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if ((*opponent_projectiles_[i]).GetIsActive()) {
      (*opponent_projectiles_[i]).Draw(game_screen_);
    }
  }
  for (int i = 0; i < player_projectiles_.size(); i++) {
    if ((*player_projectiles_[i]).GetIsActive()) {
      (*player_projectiles_[i]).Draw(game_screen_);
    }
  }
  score_str_ = "Score: ";
  score_str_ += std::to_string(score_);
  game_screen_.DrawText(10, 10, score_str_, 30, 0, 0, 0);
  if (has_lost_) {
    game_screen_.DrawText(350, 280, "Game Over", 40, 0, 0, 0);
  }
}

void Game::Start() { game_screen_.ShowUntilClosed(); }

void Game::OnMouseEvent(const graphics::MouseEvent& event) {
  if (event.GetMouseAction() == graphics::MouseAction::kMoved ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
    int new_x = event.GetX() - my_player_.GetWidth() / 2;
    int new_y = event.GetY() - my_player_.GetHeight() / 2;
    int old_x = my_player_.GetX();
    int old_y = my_player_.GetY();

    my_player_.SetX(new_x);
    my_player_.SetY(new_y);

    if (my_player_.IsOutOfBounds(game_screen_)) {
      my_player_.SetX(old_x);
      my_player_.SetY(old_y);
    }
  }
  if (event.GetMouseAction() == graphics::MouseAction::kDragged ||
      event.GetMouseAction() == graphics::MouseAction::kPressed) {
    int new_x = event.GetX() - my_player_.GetWidth() / 2;
    int new_y = event.GetY() - my_player_.GetHeight() / 2;
    std::unique_ptr<PlayerProjectile> player_proj =
        std::make_unique<PlayerProjectile>(new_x, new_y);
    player_projectiles_.push_back(std::move(player_proj));
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponents_.size(); i++) {
    std::unique_ptr<OpponentProjectile> opponent_proj_ =
        std::make_unique<OpponentProjectile>(0, 0);
    opponent_proj_ = opponents_[i]->LaunchProjectile();
    if (opponent_proj_) {
      opponent_projectiles_.push_back(std::move(opponent_proj_));
    }
  }
}

void Game::RemoveInactive() {
  for (int i = player_projectiles_.size() - 1; i >= 0; i--) {
    if (!(*player_projectiles_[i]).GetIsActive()) {
      player_projectiles_.erase(player_projectiles_.begin() + i);
    }
  }
  for (int i = opponent_projectiles_.size() - 1; i >= 0; i--) {
    if (!(*opponent_projectiles_[i]).GetIsActive()) {
      opponent_projectiles_.erase(opponent_projectiles_.begin() + i);
    }
  }
  for (int i = opponents_.size() - 1; i >= 0; i--) {
    if (!(*opponents_[i]).GetIsActive()) {
      opponents_.erase(opponents_.begin() + i);
    }
  }
}

void Game::OnAnimationStep() {
  if (opponents_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  game_screen_.Flush();
}
