#include <iostream>
#include <cstdlib>

#include "../state/state.hpp"
#include "./submission.hpp"

#define MINVALUE -200
#define MAXVALUE 200

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

int alphabetaMax(State* state, int alpha, int beta, int depth);
int alphabetaMin(State* state, int alpha, int beta, int depth);

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move submission::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  Move bestmove;
  int alpha = MINVALUE, beta = MAXVALUE;
  auto actions = state->legal_actions;
  for(auto it: actions){
    State* n_state = state->next_state(it);
    int score = alphabetaMin(n_state, alpha, beta, depth - 1);
    if(score > alpha){
      alpha = score;
      bestmove = it;
    }
  }
  return bestmove;
}

int alphabetaMax(State* state, int alpha, int beta, int depth){
  if(depth == 0) return state->evaluate();
  state->get_legal_actions();

  auto actions = state->legal_actions;
  for(auto it: actions){
    State* n_state = state->next_state(it);
    int score = alphabetaMin(n_state, alpha, beta, depth - 1);
    if( score >= beta )
      return beta;
    if( score > alpha )
      alpha = score;
  }
  return alpha;
}

int alphabetaMin(State* state, int alpha, int beta, int depth){
  if(depth == 0) return state->evaluate();
  state->get_legal_actions();

  auto actions = state->legal_actions;
  for(auto it: actions){
    State* n_state = state->next_state(it);
    int score = alphabetaMax(n_state, alpha, beta, depth - 1 );
    if( score <= alpha )
      return alpha;
    if( score < beta )
      beta = score;
  }
  return beta;
}