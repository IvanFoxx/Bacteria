#include "mainwindow.hpp"

#include <chrono>

void MainWindow::EventHandle(sf::Event& e) {
  if (e.type == sf::Event::MouseWheelScrolled) {
    transformer_.ScaleCamera(e.mouseWheelScroll.delta);
  }
  if (e.type == sf::Event::MouseButtonPressed &&
      e.mouseButton.button == sf::Mouse::Left) {
    move_mode_ = true;
    last_x_ = e.mouseButton.x;
    last_y_ = e.mouseButton.y;
  }
  if (e.type == sf::Event::MouseButtonReleased &&
      e.mouseButton.button == sf::Mouse::Left)
    move_mode_ = false;
  if (e.type == sf::Event::MouseMoved && move_mode_) {
    transformer_.MoveCameraP(e.mouseMove.x - last_x_, e.mouseMove.y - last_y_);
    last_x_ = e.mouseMove.x;
    last_y_ = e.mouseMove.y;
  }
  if (e.type == sf::Event::MouseMoved) {
    last_x_ = e.mouseMove.x;
    last_y_ = e.mouseMove.y;
  }
  if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Space) {
    fast_mode_ = !fast_mode_;
    window_.setFramerateLimit(fast_mode_ ? 2000 : 60);
  }
  if (e.type == sf::Event::KeyReleased) {
    if (e.key.code == sf::Keyboard::Add) {
      time_speed_ += 0.2;
    } else if (e.key.code == sf::Keyboard::Subtract) {
      if (time_speed_ > 0.2) time_speed_ -= 0.2;
    }
  }
  if (e.type == sf::Event::Closed) window_.close();
}

void MainWindow::Render(std::vector<std::shared_ptr<Object>> objects) {
  for (auto&& object : objects) {
    float radius = transformer_.Scale(object->GetRadius());
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(radius, radius);
    sf::Vector2f after(transformer_.ScaleW(object->GetX()),
                       transformer_.ScaleH(object->GetY()));
    if (after.x + radius < 0.0 || after.x - radius > width_ ||
        after.y + radius < 0.0 || after.y - radius > height_)
      continue;
    shape.setPosition(after);
    window_.draw(shape);
  }
}

MainWindow::MainWindow(size_t width, size_t height)
    : transformer_(width, height),
      window_(sf::VideoMode(width, height), "Bacteries"),
      width_(width),
      height_(height) {
  window_.setFramerateLimit(60);
}

int MainWindow::MainLoop() {
  float range = simulation_.GetField().GetRange();
  sf::RectangleShape scene;
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  scene.setOutlineColor(sf::Color(125, 125, 125));
  scene.setFillColor(sf::Color(40, 40, 40));
  scene.setOutlineThickness(2);

  while (window_.isOpen()) {
    auto begin = std::chrono::steady_clock::now();

    sf::Event event;
    while (window_.pollEvent(event)) EventHandle(event);

    window_.clear();

    scene.setSize(
        {transformer_.Scale(2 * range), transformer_.Scale(2 * range)});
    scene.setPosition(transformer_.ScaleW(-range), transformer_.ScaleH(-range));

    window_.draw(scene);

    simulation_.Stop();

    for (const auto& object : simulation_.GetField().GetObjects()) {
      auto radius = object->GetRadius();
      auto x = object->GetX();
      auto y = object->GetY();

      shape.setRadius(transformer_.Scale(radius));
      shape.setPosition(transformer_.ScaleW(x), transformer_.ScaleH(y));
      shape.setOrigin(transformer_.Scale(radius), transformer_.Scale(radius));

      window_.draw(shape);
    }

    simulation_.Start(delta_time_);

    window_.display();

    auto end = std::chrono::steady_clock::now();
    delta_time_ =
        std::chrono::duration_cast<std::chrono::duration<float>>(end - begin)
            .count();
  }

  return 0;
}
