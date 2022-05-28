#include "Automata.h"
using namespace std;
string product_to_str(Product product) {
	switch (product)
	{
	case Product::LATTE:
		return string("Latte");
	case Product::CAPPUCINO:
		return string("Cappucino");
	case Product::AMERICANO:
		return string("Americano");
	case Product::ESPRESSO:
		return string("Espresso");
	case Product::FLATWHITE:
		return string("Flatwhite");
	default:
		return string("Some unknown Coffee");
	}
}

State CoffeeMachine::getState() {
	return this->engine.getState();
}

CoffeeMachine::CoffeeMachine(map<Product, int> menu) {
	this->menu = menu;
	create_engine();
}

CoffeeMachine::CoffeeMachine() {
	menu[Product::AMERICANO] = 60;
	menu[Product::CAPPUCINO] = 80;
	menu[Product::FLATWHITE] = 120;
	menu[Product::ESPRESSO] = 60;
	menu[Product::LATTE] = 120;
	create_engine();
}

void CoffeeMachine::create_engine() {
	map<pair<State, Act>, State> transitions;
	transitions[pair<State, Act>(State::OFF, Act::ON)] = State::WAIT;
	transitions[pair<State, Act>(State::WAIT, Act::OFFACT)] = State::OFF;
	transitions[pair<State, Act>(State::WAIT, Act::COIN)] = State::ACCEPT;
	transitions[pair<State, Act>(State::ACCEPT, Act::CANCEL)] = State::WAIT;
	transitions[pair<State, Act>(State::ACCEPT, Act::COIN)] = State::ACCEPT;
	transitions[pair<State, Act>(State::ACCEPT, Act::TRUECHECK)] = State::READY;
	transitions[pair<State, Act>(State::ACCEPT, Act::FALSECHECK)] = State::ACCEPT;
	transitions[pair<State, Act>(State::READY, Act::CANCEL)] = State::WAIT;
	transitions[pair<State, Act>(State::READY, Act::COOKACT)] = State::COOK;
	transitions[pair<State, Act>(State::COOK, Act::FINISH)] = State::WAIT;
	engine = Automata<State, Act>(transitions, State::OFF);
}

void CoffeeMachine::on() {
	this->engine.do_transition(Act::ON);
	printf("Ready to work");
}

void CoffeeMachine::off() {
	this->engine.do_transition(Act::OFFACT);
	printf("\nWork complete");
}

void CoffeeMachine::coin(int value) {
	this->cash = value;
	for (int i = 0; i < value; i++) {
		this->engine.do_transition(Act::COIN);
	}
}

void CoffeeMachine::choice(Product product) {
	if (cash < menu[product]) {
		printf("\nNot enough money for chosen product. You need %s", to_string(menu[product] - cash).c_str());
		this->engine.do_transition(Act::FALSECHECK);
	}
	else {
		chosen_product = product;
		printf("\nTake your spare");
		this->engine.do_transition(Act::TRUECHECK);
	}
}

void CoffeeMachine::cancel(){
	printf("\n...the sound of falling coins...\nPlease, take your money back");
	this->engine.do_transition(Act::CANCEL);
}

void CoffeeMachine::cook() {
	printf("\nGetting your coffee ready...");
	this->engine.do_transition(Act::COOKACT);
}

void CoffeeMachine::finish() {
	this->engine.do_transition(Act::FINISH);
}

void CoffeeMachine::printMenu() {
	for (auto it = menu.begin(); it != menu.end(); it++) {
		printf("%s : %d", product_to_str(it->first).c_str(), it->second);
	}
}

template<typename State, typename Act>
Automata<State, Act>::Automata(map<pair<State, Act>, State> transitions, State start_state) {
	this->transitions = transitions;
	this->current_state = start_state;
}

template<typename State, typename Act>
void Automata<State, Act>::do_transition(Act act) {
	if (this->transitions.find(pair<State, Act>(this->getState(), act)) == this->transitions.end())
	{
		throw std::invalid_argument("Recieved wrong trasition call");
	}
	else {
		this->current_state = transitions[pair<State, Act>(this->getState(), act)];
	}
}


template<typename State, typename Act>
State Automata<State, Act>::getState() {
	return this->current_state;
}
