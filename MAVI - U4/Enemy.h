#pragma once

#include <stdio.h>
#include <tchar.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Enemy {
	Texture textureEnemy;
	Sprite spriteEnemy;

	bool _estaVisible;

	sf::Clock _clock;
	float _tiempoApagado;

	bool movHor, movVer, movDiagRigth, movDiagLeft;

	sf::Vector2f tempPosition;
	sf::Vector2f velocity;

	float deltaTime = 1.0f / 60.0f;

	const float speed = 500.0f;

	void Move() {
		if (movHor) {
			tempPosition.x += speed * deltaTime;

			spriteEnemy.setPosition(tempPosition);

			if (tempPosition.x > 900) {
				Death();
			}
		}
		else if (movVer) {
			tempPosition.y -= speed * deltaTime;

			spriteEnemy.setPosition(tempPosition);

			if (tempPosition.y < -100) {
				Death();
			}
		}
		else if (movDiagLeft) {
			tempPosition.x -= speed * deltaTime;

			velocity.y += speed * deltaTime;

			tempPosition.y += (velocity.y * 5) * deltaTime;

			if (tempPosition.y > 550.0f) {
				tempPosition.y = 550.0f;
				velocity.y = -(velocity.y * 0.90f);
			}

			spriteEnemy.setPosition(tempPosition);

			if (tempPosition.x < -100) {
				Death();
			}
		}
		else if (movDiagRigth) {
			tempPosition.x += speed * deltaTime;

			velocity.y += speed * deltaTime;

			tempPosition.y += (velocity.y * 5) * deltaTime;

			if (tempPosition.y > 550.0f) {
				tempPosition.y = 550.0f;
				velocity.y = -(velocity.y * 0.90f);
			}

			spriteEnemy.setPosition(tempPosition);

			if (tempPosition.x > 900) {
				Death();
			}
		}
	}

	void SelectMovement() {
		int nRandom = rand() % 4;

		switch (nRandom) {
		case 0:
			movHor = true;
			movVer = false;
			movDiagRigth = false;
			movDiagLeft = false;
			break;
		case 1:
			movHor = false;
			movVer = true;
			movDiagRigth = false;
			movDiagLeft = false;
			break;
		case 2:
			movHor = false;
			movVer = false;
			movDiagRigth = true;
			movDiagLeft = false;
			break;
		case 3:
			movHor = false;
			movVer = false;
			movDiagRigth = false;
			movDiagLeft = true;
			break;
		default:
			break;
		}
	}

public:
	Enemy() {
		textureEnemy.loadFromFile("assets/target.png");
		spriteEnemy.setTexture(textureEnemy);
		spriteEnemy.setScale(0.15, 0.15);
		spriteEnemy.setOrigin(300, 300);

		_estaVisible = true;
		_tiempoApagado = 1.0f;

		movHor = false;
		movVer = false;
		movDiagRigth = false;
		movDiagLeft = false;

		tempPosition = Vector2f(0.0f, 0.0f);
		velocity = Vector2f(0.0f, 0.0f);
	}

	bool EstaActivo() {
		return _estaVisible;
	}

	bool CheckCollision(float x, float y) {
		FloatRect bounds = spriteEnemy.getGlobalBounds();
		return bounds.contains(x, y);
	}

	void Dibujar(RenderWindow* wnd) {
		wnd->draw(spriteEnemy);
	}

	void Death() {
		_estaVisible = false;
		_clock.restart();
	}

	void Actualizar(RenderWindow *wnd) {
		if (_estaVisible) {
			Move();
		}
		else {
			if (_clock.getElapsedTime().asSeconds() > _tiempoApagado) {
				_clock.restart();
				ResetMovement();
			}
		}
	}

	void ResetMovement() {
		SelectMovement();

		if (movHor) {
			_estaVisible = true;
			tempPosition = Vector2f(-100.0f, 300.0f);
			velocity = Vector2f(0.0f, 0.0f);
			spriteEnemy.setPosition(tempPosition);
		}
		else if (movVer) {
			_estaVisible = true;
			tempPosition = Vector2f(400.0f, 900.0f);
			velocity = Vector2f(0.0f, 0.0f);
			spriteEnemy.setPosition(tempPosition);
		}
		else if (movDiagLeft) {
			_estaVisible = true;
			tempPosition = Vector2f(900.0f, -100.0f);
			velocity = Vector2f(0.0f, 0.0f);
			spriteEnemy.setPosition(tempPosition);
		}
		else if (movDiagRigth) {
			_estaVisible = true;
			tempPosition = Vector2f(-100.0f, -100.0f);
			velocity = Vector2f(0.0f, 0.0f);
			spriteEnemy.setPosition(tempPosition);
		}
	}
};