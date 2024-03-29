/*
 * main.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: A.Melachuri
 */

#include <SFML/Graphics.hpp>
#include "GrassTile.h"
#include "Textures.h"
#include "Chunk.h"
#include "World.h"
#include "Player.h"
#include "GameState.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void init() {
	if (!Textures::forestSheet.loadFromFile("assets/forest_tiles.png")) {
		// https://opengameart.org/content/forest-tiles
		cout << "Couldn't load assets/forest_tiles.png" << endl;
	}
	if (!Textures::roguelikeSheet.loadFromFile(
			"assets/roguelikeSheet_transparent.png")) {
		//https://opengameart.org/content/roguelikerpg-pack-1700-tiles
		cout << "Couldn't load assets/roguelikeSheet_transparent.png" << endl;
	}
}

void shutDown(sf::RenderWindow &window){
	window.close();
}

int main() {
	int width = 1080, height = 720;
	sf::RenderWindow window(sf::VideoMode(width, height), "Sprite", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	sf::View view = window.getView();
	cout << "before init" << endl;
	init();
//	cout << "before world create" << endl;
	World world;
	GameState state;
	state.status=GameState::PLAYING;
//	cout << "after world create" << endl;
	Player player(Vector2f(world.rooms.at(0).centerx*48, world.rooms.at(0).centery*48), &world);
//	cout << "Player created. "<<endl;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				cout << "window" << endl;
				shutDown(window);
			}
			if (event.type == sf::Event::KeyPressed)
			{
			    if (event.key.code == sf::Keyboard::Space)
			    {
			        state.update();
			    }
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))shutDown(window);


		if(state.status==GameState::PLAYING)player.update();
//		cout << state.status << endl;
//		cout << "Player updated. "<<endl;
		view.setCenter(player.getPosition().x + 48,
				player.getPosition().y + 48);
		window.setView(view);

		window.clear();
//		cout << "before world render" << endl;
		world.renderWorld(window,window.getSize().x, window.getSize().y);
//		cout << "after world render" << endl;
		window.draw(player.sprite, player.getTransform());
		window.display();
	}

	return 0;
}

