#include <iostream>
#include "maze.h"
#include <SFML/Graphics.hpp>

using namespace std;

const sf::Vector2f tile_size(60.f, 60.f);
const sf::Vector2f wall_ratio(tile_size.x, 2.f);
const sf::RectangleShape empty_shape;

vector<sf::RectangleShape> get_walls(sf::RectangleShape cell, bool cell_walls[4]) {

    vector<sf::RectangleShape> walls;

    if (cell_walls[TOP]) {
        sf::RectangleShape top_wall(wall_ratio);
        top_wall.setFillColor(sf::Color::Black);
        top_wall.setPosition(cell.getPosition().x, cell.getPosition().y);
        walls.push_back(top_wall);
    } else {
        walls.push_back(empty_shape);
    }
        
    if (cell_walls[LEFT]) {
        sf::RectangleShape left_wall(wall_ratio);
        left_wall.setFillColor(sf::Color::Black);
        left_wall.rotate(90.f);
        left_wall.setPosition(cell.getPosition().x, cell.getPosition().y);
        walls.push_back(left_wall);
    } else {
        walls.push_back(empty_shape);
    }
    
    if (cell_walls[RIGHT]) {
        sf::RectangleShape right_wall(wall_ratio);
        right_wall.setFillColor(sf::Color::Black);
        right_wall.rotate(90.f);
        right_wall.setPosition(cell.getPosition().x + tile_size.x, cell.getPosition().y);
        walls.push_back(right_wall);
    } else {
        walls.push_back(empty_shape);
    }

    if (cell_walls[BOTTOM]) {
        sf::RectangleShape bottom_wall(wall_ratio);
        bottom_wall.setFillColor(sf::Color::Black);
        bottom_wall.setPosition(cell.getPosition().x, cell.getPosition().y + tile_size.y);
        walls.push_back(bottom_wall);
    } else {
        walls.push_back(empty_shape);
    }

    return walls;
}

void draw_cells(sf::RenderWindow& surface) {

    float rows = surface.getSize().y / tile_size.y;
    float cols = surface.getSize().x / tile_size.x;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            sf::RectangleShape cell(tile_size);
            cell.setFillColor(sf::Color::White);
            cell.setPosition(row * tile_size.y, col * tile_size.x);
            bool cell_walls[4] = {true, true, true, true}; //top, left, right, bottom
            vector<sf::RectangleShape> walls = get_walls(cell, cell_walls);
            surface.draw(cell);
            for (sf::RectangleShape wall : walls) {
                if (wall.getSize() != empty_shape.getSize()) {
                    surface.draw(wall);
                }
            }
        }
    }



}

int main() {

    sf::RenderWindow window(sf::VideoMode(600, 600), "MazeGame");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }

            if (e.type = sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Enter) {
                    cout << "DRAWING MAZE!" << endl;
                }
            }
        }

        draw_cells(window);

        window.display();
    }

    

}