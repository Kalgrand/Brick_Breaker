#include <iostream>
#include <SDL.h>
using namespace std;

bool quit = false;
SDL_Event event;
int ball_x = 10;
int ball_y = 10;
int ball_vel_x = 1;
int ball_vel_y = 1;
int background_w = 800;
int background_h = 600;
int background_min_w = 0;
int background_min_h = 0;
int floor_x = background_w / 2;
int floor_y = background_h - 30;

void EventHandler() {
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		quit = true;
	}
	else if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT && floor_x > 0) {
			floor_x = floor_x - 2;
		}
		if (event.key.keysym.sym == SDLK_RIGHT && floor_x < background_w - 60) {
			floor_x = floor_x + 2;
		}
	}
}

void moveBall() {
	ball_x = ball_x + ball_vel_x;
	ball_y = ball_y + ball_vel_y;
}

void ballCollision() {
	if (ball_x < background_min_w || ball_x > background_w - 30) {
		ball_vel_x = -ball_vel_x;
	}
	if (ball_y < background_min_h || ball_y > background_h - 30) {
		ball_vel_y = -ball_vel_y;
	}
}

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("The Game",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Rect background_rect = { 0, 0, 800, 600 };
	SDL_Surface* ball = SDL_LoadBMP("ball.bmp");
	SDL_Surface* background = SDL_LoadBMP("background.bmp");
	SDL_Surface* floor = SDL_LoadBMP("floor.bmp");
	SDL_Texture* ball_texture = SDL_CreateTextureFromSurface(renderer, ball);
	SDL_Texture* background_texture = SDL_CreateTextureFromSurface(renderer, background);
	SDL_Texture* floor_texture = SDL_CreateTextureFromSurface(renderer, floor);

	while (!quit) {
		EventHandler();
		SDL_Rect ball_rect = {ball_x, ball_y, 20, 30};
		SDL_Rect floor_rect = { floor_x, floor_y, 60, 30 };
		moveBall();
		ballCollision();
		SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);
		SDL_RenderCopy(renderer, ball_texture, NULL, &ball_rect);
		SDL_RenderCopy(renderer, floor_texture, NULL, &floor_rect);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_Delay(3);
	}

	SDL_Delay(6000);
	SDL_Quit();
	return 0;
}