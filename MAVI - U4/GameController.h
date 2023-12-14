#pragma once
#pragma warning(disable : 4996)

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

#include "PlayerCrosshair.h"
#include "Enemy.h"

using namespace sf;

class GameController {

	RenderWindow *_wnd;
	PlayerCrosshair *_playerCrosshair;
	Enemy *_enemigo;

	Text puntaje;
	Font font;
	int _puntos;
	void actualizarPuntaje() {
		if (_puntos < 5) {
			puntaje.setString(std::to_string(_puntos));
		}
		else {
			puntaje.setString("GANASTE! \n\nPreciona ESC para salir.");
		}
		
	}
	
public:
	GameController() {
		_wnd = new RenderWindow(VideoMode(800, 600, 32), "MAVI - Unidad 6");
		_wnd->setMouseCursorVisible(false);
		_wnd->setFramerateLimit(60);

		_playerCrosshair = new PlayerCrosshair();

		_enemigo = new Enemy;

		_puntos = 0;

		font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

		puntaje.setPosition(0, 0);
		puntaje.setFont(font);
		puntaje.setColor(Color::White);
		puntaje.setCharacterSize(50.0f);
		actualizarPuntaje();

		_enemigo->ResetMovement();
	}

	void MainLoop() {
		while (_wnd->isOpen()) {
			ProcesarEventos();
			Actualizar();
			Dibujar();
		}
	}

	void ProcesarEventos() {
		Event evt;
		while (_wnd->pollEvent(evt)) {

			switch (evt.type)
			{
			case Event::Closed:
				_wnd->close();
				break;

			case Event::MouseButtonPressed:
				if (evt.mouseButton.button == Mouse::Button::Left) {
					Disparar();
				}
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape) == true)
				_wnd->close();
		}
	}

	void Actualizar() {
		_playerCrosshair->Posicionar(Mouse::getPosition(*_wnd));
		
		_enemigo->Actualizar(_wnd);
	}

	void Disparar() {
		if (_enemigo->CheckCollision(_playerCrosshair->GetPosition().x, _playerCrosshair->GetPosition().y)) {
			_enemigo->Death();
			_puntos++;
		}


		actualizarPuntaje();
	}

	void Dibujar() {
		_wnd->clear();

		for (int i = 0; i < 5; i++)
		{
			if (_enemigo->EstaActivo()) {
				_enemigo->Dibujar(_wnd);
			}
		}

		_playerCrosshair->Dibujar(_wnd);

		_wnd->draw(puntaje);
		
		_wnd->display();
	}

	~GameController() {
		delete _enemigo;
		delete _playerCrosshair;
		delete _wnd;
	}
};
