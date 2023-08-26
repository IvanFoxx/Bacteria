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
  simulation_.InitRandomly();
}

int MainWindow::MainLoop() {
  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);
  float range = simulation_.GetField().GetRange();
  sf::RectangleShape scene;

  scene.setOutlineColor(sf::Color(125, 125, 125));
  scene.setFillColor(sf::Color(40, 40, 40));
  scene.setOutlineThickness(2);

  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      EventHandle(event);
      if (event.type == sf::Event::KeyReleased &&
          event.key.code == sf::Keyboard::Space) {
        fast_mode_ = !fast_mode_;
        window_.setFramerateLimit(fast_mode_ ? 2000 : 60);
      }
      if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Add) {
          time_speed_ += 0.2;
        } else if (event.key.code == sf::Keyboard::Subtract) {
          if (time_speed_ > 0.2) time_speed_ -= 0.2;
        }
      }
      if (event.type == sf::Event::Closed) window_.close();
    }

    window_.clear();

    scene.setSize(
        {transformer_.Scale(2 * range), transformer_.Scale(2 * range)});
    scene.setPosition(
        {transformer_.ScaleW(-range), transformer_.ScaleH(-range)});
    window_.draw(scene);

    RenderFood();
    RenderBactery();

    window_.display();

    simulation_.Run(delta_time_ / time_speed_);
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();
    delta_time_ =
        (std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
             .count()) /
        1000000.0;
  }

  return 0;
}
/*
if (core.get() == nullptr) {
  RenderFileMenu();
  return;
}

if (core->IsLoading()) {
  DrawText(std::to_string(core->GetProgress()), sf::Color::Red, 40,
           {width / 2.0f, height / 2.0f}, {0.5, 0.5});
  window.display();
  return;
}

DrawText(core->GetTimeDump(), sf::Color::White, 20);

if (console_e) DrawText(console.Text(), sf::Color::White, 20, {0, 400});

if (core->SlowDownWarning())
  DrawText("Slow down error", sf::Color::Red, 40, {width / 2.0f, height / 2.0f},
           {0.5, 1.35});

DrawText(std::to_string(core->GetSpeed()), sf::Color::Red, 20,
         {static_cast<float>(width), 0}, {1, 0});

RenderPlanets();

window.display();

    void DrawText(std::string txt, sf::Color color, size_t size,
                  sf::Vector2f position, sf::Vector2f relative_origin) {
*/
/*
sf::Text text(txt, mfont, size);
text.setFillColor(color);
text.setStyle(sf::Text::Bold);

 sf::FloatRect textRect = text.getLocalBounds();
 text.setOrigin(textRect.width * relative_origin.x,
                textRect.height * relative_origin.y);
 text.setPosition(position.x, position.y);
 window.draw(text);
*/
