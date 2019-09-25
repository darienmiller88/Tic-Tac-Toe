#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "TicTacToe.h"
#include "TitleScreen.h"
#include "StateManager.h"
using namespace sf;
using namespace std;

class Foo {
	public:
		constexpr Foo(int num) : num(num){}
		constexpr int getNum() const{
			return num;
		}
		void setNum(int num) {
			this->num = num;
		}
	private:
		int num;
};

template<int N>
void foo() {

}

int main() {
	//RenderWindow window(VideoMode(600, 600), "problem.exe", Style::Close | Style::Titlebar);
	StateManager m(600, 600, "window");

	m.runGame();
	// define a 100x100 square, red, with a 10x10 texture mapped on it
	/*window.setFramerateLimit(10);
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
		}


		window.clear();
		window.display();
	}*/
	//game.playGame();
}