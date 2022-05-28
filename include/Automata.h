#include <vector>
#include <map>
using namespace std;
enum class State {
	OFF,
	WAIT,
	ACCEPT,
	READY,
	COOK
};

enum class Act {
	ON,
	OFFACT,
	COIN,
	FALSECHECK,
	TRUECHECK,
	CANCEL,
	COOKACT,
	FINISH
};

enum class Product {
	LATTE,
	CAPPUCINO,
	ESPRESSO,
	AMERICANO,
	FLATWHITE
};


//Finite State Machine implementation
template<typename State, typename Act>
class Automata {
	map<pair<State, Act>, State> transitions;
	State current_state;
public:
	Automata(map<pair<State, Act>, State> transitions, State start_state);
	Automata(){};
	void do_transition(Act act);
	State getState();
};

class CoffeeMachine {
public:
	void on();
	void off();
	void coin(int);
	void printMenu();
	void choice(Product);
	void cancel();
	void cook();
	void finish();
	State getState();
	CoffeeMachine(map<Product, int> menu);
	//standart menu
	CoffeeMachine();
private:
	int cash;
	map<Product, int> menu;
	Product chosen_product;
	Automata<State, Act> engine;
	void create_engine();
};
