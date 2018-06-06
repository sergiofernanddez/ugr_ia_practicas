/*
 * Wilson.cpp
 *
 *  Created on: 20 may. 2018
 *      Author: Sergio Fernández
 */

#include "Wilson.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include<vector>
using namespace std;

int masinf=99999999;
int menosinf=-99999999;

Wilson::Wilson()
{
	// Inicializar las variables necesarias para ejecutar la partida
	profundidad = 9;
}

Wilson::~Wilson()
{
	// Liberar los recursos reservados (memoria, ficheros, etc.)
}

void Wilson::initialize()
{
}

string Wilson::getName()
{
	return "Wilson"; // Sustituir por el nombre del bot
}

int Wilson::heuristics(const Player &jugador, const GameState &estado)
{
	int puntos1 = 25;
	int puntos2 = estado.getScore(jugador);
	int heuristics;

	heuristics = puntos1 + puntos2;

	return heuristics;
}


int Wilson::PodaAlfaBeta(const GameState &estado, int prof, Move &movimiento, int alfa, int beta)
{
	if (prof == 0 || estado.isFinalState())
	{
		//Devuelve Heuristica
		int heuristica;
		heuristica = heuristics(current_player, estado) - heuristics(oponent_player, estado);
		
		return heuristica;
	}
	else
	{
		Move mov;
		int valor_nodo;
		vector<Move> lista_movimientos = movimientosPosibles(estado);
		int num_movimientos = lista_movimientos.size();
		int retorno;

		for(int i=0; i<num_movimientos; i++)
		{
			GameState hijo = estado.simulateMove(lista_movimientos[i]);
			valor_nodo = PodaAlfaBeta(hijo, prof-1, mov, alfa, beta);
			
			if(current_player == estado.getCurrentPlayer())
			{
				if(alfa < valor_nodo)
				{
					movimiento = lista_movimientos[i];
					alfa = valor_nodo;
				}
				
				if(alfa >= beta) break;
			}
			else if (oponent_player == estado.getCurrentPlayer())
			{
				if(beta > valor_nodo)
				{
					movimiento = lista_movimientos[i];
					beta = valor_nodo;
				}

				if(alfa>=beta) break;
			}
		}

		(current_player == estado.getCurrentPlayer()) ? retorno = alfa : retorno = beta;

		return retorno;
	}
}

Move Wilson::nextMove(const vector<Move> &adversary, const GameState &state)
{
	Move movimiento = M_NONE;
	
	int alfa = menosinf;
	int beta = masinf;

	current_player = state.getCurrentPlayer();
	if(current_player == J1)
		oponent_player = J2;
	else	
		oponent_player = J1;

	
	PodaAlfaBeta(state, profundidad, movimiento, alfa, beta);

	return movimiento;
}

vector<Move> Wilson::movimientosPosibles(const GameState &estado)
{
	vector<Move> movimientos_posibles;
	
	for(int i=1; i<7; i++)
	{
		if(estado.getSeedsAt(estado.getCurrentPlayer(), (Position)i) > 0)
      		movimientos_posibles.push_back((Move)i);
	}
	return movimientos_posibles;
}
