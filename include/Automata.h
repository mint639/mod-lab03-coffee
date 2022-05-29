// Copyright 2022 UNN-IASR
#pragma once

#include <vector>
#include <map>
#include <utility>

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
    std::map<std::pair<State, Act>, State> transitions;
    State current_state;
 public:
    Automata(std::map<std::pair<State, Act>,
    State> transitions, State start_state);
    Automata() {}
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
    explicit CoffeeMachine(std::map<Product, int> menu);
    //standart menu
    CoffeeMachine();
 private:
    int cash;
    std::map<Product, int> menu;
    Product chosen_product;
    Automata<State, Act> engine;
    void create_engine();
};
