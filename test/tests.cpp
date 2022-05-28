#include <gtest/gtest.h>
#include "Automata.h"

//i would add some tests especially for automata but
//there is too much coding for creating states, acts and transitions map
TEST(COFFEEMACHINE_TASK, COINS_INSERTION) {
	CoffeeMachine coffeemachine = CoffeeMachine();
	coffeemachine.on();
	coffeemachine.coin(1);
	coffeemachine.coin(1);
	EXPECT_EQ(coffeemachine.getState(), State::ACCEPT);
}

TEST(COFFEEMACHINE_TASK, CANCEL_1) {
	CoffeeMachine coffeemachine = CoffeeMachine();
	coffeemachine.on();
	coffeemachine.coin(1);
	coffeemachine.cancel();
	EXPECT_EQ(coffeemachine.getState(), State::WAIT);
	
}

TEST(COFFEEMACHINE_TASK, CANCEL_2) {
	CoffeeMachine coffeemachine = CoffeeMachine();
	coffeemachine.on();
	coffeemachine.coin(100);
	coffeemachine.choice(Product::AMERICANO);
	coffeemachine.cancel();
	EXPECT_EQ(coffeemachine.getState(), State::WAIT);

}
TEST(COFFEEMACHINE_TASK, WRONG_CHOICE) {
	CoffeeMachine coffeemachine = CoffeeMachine();
	coffeemachine.on();
	coffeemachine.coin(1);
	coffeemachine.choice(Product::CAPPUCINO);
	EXPECT_EQ(coffeemachine.getState(), State::ACCEPT);
}
TEST(COFFEEMACHINE_TASK, RIGHT_CHOICE) {
	CoffeeMachine coffeemachine = CoffeeMachine();
	coffeemachine.on();
	coffeemachine.coin(100);
	coffeemachine.choice(Product::CAPPUCINO);
	EXPECT_EQ(coffeemachine.getState(), State::READY);
}

TEST(COFFEEMACHINE_TASK, FULL_COURSE) {
	CoffeeMachine coffeemachine = CoffeeMachine();
	coffeemachine.on();
	coffeemachine.coin(100);
	coffeemachine.choice(Product::CAPPUCINO);
	coffeemachine.cook();
	coffeemachine.finish();
	coffeemachine.off();
	EXPECT_EQ(coffeemachine.getState(), State::OFF);
}

TEST(COFFEEMACHINE_TASK, MENU_PRINT) {
	CoffeeMachine coffeemachine = CoffeeMachine();
	coffeemachine.on();
	coffeemachine.printMenu();
}
