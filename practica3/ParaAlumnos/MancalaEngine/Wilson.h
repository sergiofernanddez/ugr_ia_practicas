/*
 * Wilson.h
 *
 *  Created on: 15 ene. 2018
 *      Author: sergio fernández
 */

#include "Bot.h"

#ifndef MANUPCBOT_H_
#define MANUPCBOT_H_

class Wilson:Bot {
private:
	int profundidad;
	Player current_player;
	Player oponent_player;

	vector<Move> movimientosPosibles(const GameState &estado);
public:
	Wilson();
	~Wilson();


	void initialize();
	string getName();
	int heuristics(const Player &jugador, const GameState &estado);
	int PodaAlfaBeta(const GameState &estado, int profundidad, Move &movimiento, int alfa, int beta);
	Move nextMove(const vector<Move> &adversary, const GameState &state);
};

#endif 
