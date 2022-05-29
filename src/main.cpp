// Copyright 2022 UNN-IASR
#include <iostream>
#include "Automata.h"

int main(int argc, char* argv[]) {
    CoffeeMachine coffeemachine = CoffeeMachine();
    coffeemachine.on();
    coffeemachine.printMenu();
    coffeemachine.coin(100);
    coffeemachine.choice(Product::AMERICANO);
    coffeemachine.cook();
    coffeemachine.finish();
    coffeemachine.off();
    return 0;
}
