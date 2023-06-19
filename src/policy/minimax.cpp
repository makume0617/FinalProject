#include <iostream>
#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"

#define MINVALUE -200
#define MAXVALUE 200

int max(State *state, int depth);
int min(State *state, int depth);

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  int max = MINVALUE;
  Move bestmove;
  auto actions = state->legal_actions;
  for(auto it: actions){
    State* n_state = state->next_state(it);
    int score = min(n_state, depth - 1);
    if(score > max){
      max = score;
      bestmove = it;
    }
  }
  return bestmove;
}

int max(State *state, int depth){
    if(depth == 0) return state->evaluate();
    int max = MINVALUE;
    state->get_legal_actions();
    
    auto actions = state->legal_actions;
    for(auto it: actions){
        State* n_state = state->next_state(it);
        int score = min(n_state, depth - 1);
        if(score > max){
            max = score;
        }
    }
    return max;
}

int min(State *state, int depth){
    if (depth == 0) return state->evaluate();
    int min = MAXVALUE;
    state->get_legal_actions();

    auto actions = state->legal_actions;
    for(auto it: actions){
        State* n_state = state->next_state(it);
        int score = max(n_state, depth - 1);
        if(score < min){
            min = score;
        }
    }
    return min;
}