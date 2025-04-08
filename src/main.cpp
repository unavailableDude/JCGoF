/*
	main.cpp
	Created on: 13.03.2025
	by: Mohammad Ayad Ghanim	"full M.A.G"
*/


//C++
#include <iostream>
#include <stdint.h>
#include <vector>

//3rd party
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_keyboard.h"


const int SCRW = 2560;
const int SCRH = 1440;

const int WINW = 64;
const int WINH = 48;
const int PIXS = 8;
const int BOARDW = WINW;
const int BOARDH = WINH;


int main(int argc, char* argv[]){
	//initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cerr << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_Window* window1 = SDL_CreateWindow("Game of Life", 800, SCRH / 2 - (WINH / 2), WINW * PIXS, WINH * PIXS, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer1 = SDL_CreateRenderer(window1, -1, SDL_RENDERER_ACCELERATED);
	if(window1 == NULL){
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	if(renderer1 == NULL){
		std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	
	SDL_RenderSetScale(renderer1, PIXS, PIXS);
	bool board[BOARDW][BOARDH] = {false};
	//set the board to random values
	for(int i = 0; i < BOARDW; i++){
		for(int j = 0; j < BOARDH; j++){
			board[i][j] = rand() % 2 == 0;
		}
	}

	SDL_Event event;
	bool running = true;
	while(running){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE){
				running = false;
				SDL_DestroyWindow(window1);
				return 0;
			}
			else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					case SDLK_w:
						break;
					case SDLK_s:
						break;

					case SDLK_UP:
						break;
					case SDLK_DOWN:
						break;
				}
			}
			else if(event.type == SDL_KEYUP){
				switch(event.key.keysym.sym){
					case SDLK_w:
						break;
					case SDLK_s:
						break;

					case SDLK_UP:
						break;
					case SDLK_DOWN:
						break;
				}
			}
		}
		
		//update the game state here
		bool nextboard[BOARDW][BOARDH] = {false};
		for(int i = 0; i < BOARDW; i++){
			for(int j = 0; j < BOARDH; j++){
				int neighbors = 0;
				for(int x = -1; x <= 1; x++){
					for(int y = -1; y <= 1; y++){
						if(i - x < 0 || i - x >= BOARDW || j - y < 0 || j - y >= BOARDH){ continue; }	//skip the edges of the board
						if(x == 0 && y == 0){ continue; }												//skip the cell itself
						if(board[i - x][j - y]){ neighbors++; }											//count the neighbors
					}
				}
				
				if((neighbors == 2 || neighbors == 3) && board[i][j]){ nextboard[i][j] = true; }		//a live cell survives if it has 2 or 3 neighbors, it perishes other wise
				else if(neighbors == 3 && !board[i][j]){ nextboard[i][j] = true; }						//a dead cell comes alive if it has exactly 3 neighbors
				else{ nextboard[i][j] = false; }
			}
		}
		for(int i = 0; i < BOARDW; i++){
			for(int j = 0; j < BOARDH; j++){
				board[i][j] = nextboard[i][j];
			}
		}

		SDL_SetRenderDrawColor(renderer1, 40, 40, 40, 255);
		SDL_RenderClear(renderer1);

		SDL_SetRenderDrawColor(renderer1, 255, 255, 255, 255);
		for(int i = 0; i < BOARDW; i++){
			for(int j = 0; j < BOARDH; j++){
				if(board[i][j]){
					SDL_Rect rect = {i, j, 1, 1};
					SDL_RenderFillRect(renderer1, &rect);
				}
			}
		}

		SDL_RenderPresent(renderer1);
		SDL_Delay(33);
	}

	return 0;
}