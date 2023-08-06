#include "mainwindow.hpp"

void MainWindow::EventHandle(sf::Event &e) {
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

void MainWindow::RenderFood() {}

void MainWindow::RenderBactery() {}

MainWindow::MainWindow(size_t width, size_t height)
    : transformer_(width, height),
      window_(sf::VideoMode(width, height), "Bacteries"),
      width_(width),
      height_(height) {
  window_.setFramerateLimit(60);
}

int MainWindow::MainLoop() {
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);
  float range = simulation_.GetField().GetRange();
  sf::RectangleShape scene;

  scene.setFillColor(sf::Color(125, 125, 125));

  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      EventHandle(event);
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
  }

  return 0;
}

/*
planets = std::move(core->LoadState());

  for (auto&& p : planets) {
    auto pos = p.GetPositionV();
    number radius = std::max<number>(1.0, transformer.Scale(p.GetRadius()));
    sf::CircleShape shape(radius, std::min<number>(radius + 4, 30));
     shape.setOrigin(radius, radius);
     sf::Vector2f after(transformer.ScaleW(pos.x),
 transformer.ScaleH(pos.y)); if (after.x < 0.0 || after.x > width || after.y
 < 0.0 || after.y > height) continue; shape.setPosition(after);
     window.draw(shape);
     auto radius_transform = [=]() -> number {
       if (radius > 15) return radius;
       return 15;
     };
     if (text_e)
       DrawText(p.name, sf::Color::Red, radius_transform(),
                {after.x, after.y - (float)radius}, {0.5, 1.35});
   }
 }
*/

/*
if (core.get() == nullptr) {
  RenderFileMenu();
  return;
}

 std::string time_dump;

 sf::Event e;
 while (window.pollEvent(e)) {
   if (!console_e) {
     EventHandle(e);
     if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::T)
       text_e = !text_e;
   } else {
     if (e.type == sf::Event::KeyPressed && console_e == true &&
         key_map.count(e.key.code) == 1)
       console.PushLetter(key_map.at(e.key.code));
     if (e.type == sf::Event::KeyPressed && console_e == true &&
         e.key.code == sf::Keyboard::Backspace)
       console.BackSpace();
   }
   if (e.type == sf::Event::KeyPressed &&
       e.key.code == sf::Keyboard::Enter) {
     if (console_e) console.Enter();
     console_e = !console_e;
   }
   if (e.type == sf::Event::Closed) window.close();
 }

 window.clear();

 if (core->IsLoading()) {
   DrawText(std::to_string(core->GetProgress()), sf::Color::Red, 40,
            {width / 2.0f, height / 2.0f}, {0.5, 0.5});
   window.display();
   return;
 }

 DrawText(core->GetTimeDump(), sf::Color::White, 20);

 if (console_e) DrawText(console.Text(), sf::Color::White, 20, {0, 400});

 if (core->SlowDownWarning())
   DrawText("Slow down error", sf::Color::Red, 40,
            {width / 2.0f, height / 2.0f}, {0.5, 1.35});

 DrawText(std::to_string(core->GetSpeed()), sf::Color::Red, 20,
          {static_cast<float>(width), 0}, {1, 0});

 RenderPlanets();

 window.display();
*/

void DrawText(std::string txt, sf::Color color, size_t size,
              sf::Vector2f position, sf::Vector2f relative_origin) {
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
}
