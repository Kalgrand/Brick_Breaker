#include "funkcje.h"


int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("The Game",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Rect background_rect = { 0, 0, 800, 600 };
	InitializerBrick();
	ball = SDL_LoadBMP("ball.bmp");
	background = SDL_LoadBMP("background.bmp");
	floor1 = SDL_LoadBMP("floor.bmp");
	brick = SDL_LoadBMP("brick.bmp");
	brick2 = SDL_LoadBMP("brick2.bmp");
	brick3 = SDL_LoadBMP("brick3.bmp");
	ball_texture = SDL_CreateTextureFromSurface(renderer, ball);
	background_texture = SDL_CreateTextureFromSurface(renderer, background);
	floor_texture = SDL_CreateTextureFromSurface(renderer, floor1);
	brick_texture = SDL_CreateTextureFromSurface(renderer, brick);
	brick_texture2 = SDL_CreateTextureFromSurface(renderer, brick2);
	brick_texture3 = SDL_CreateTextureFromSurface(renderer, brick3);

	while (!quit) {
		EventHandler();
		ball_rect = {ball_x, ball_y, 20, 30};
		SDL_Rect floor_rect = { floor_x, floor_y, 60, 30 };
		moveBall();
		ballCollision();
		brickCollision();
		if (delete_brick_count == no_of_brick) {
			winning();
		}
		SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);
		SDL_RenderCopy(renderer, ball_texture, NULL, &ball_rect);
		SDL_RenderCopy(renderer, floor_texture, NULL, &floor_rect);
		SDL_RenderCopy(renderer, brick_texture, NULL, &brick_rect[0][0]);
		SDL_RenderCopy(renderer, brick_texture, NULL, &brick_rect[0][1]);
		SDL_RenderCopy(renderer, brick_texture, NULL, &brick_rect[0][2]);
		SDL_RenderCopy(renderer, brick_texture, NULL, &brick_rect[0][3]);
		SDL_RenderCopy(renderer, brick_texture, NULL, &brick_rect[0][4]);
		SDL_RenderCopy(renderer, brick_texture, NULL, &brick_rect[0][5]);
		SDL_RenderCopy(renderer, brick_texture, NULL, &brick_rect[0][6]);
		SDL_RenderCopy(renderer, brick_texture2, NULL, &brick_rect[1][0]);
		SDL_RenderCopy(renderer, brick_texture2, NULL, &brick_rect[1][1]);
		SDL_RenderCopy(renderer, brick_texture2, NULL, &brick_rect[1][2]);
		SDL_RenderCopy(renderer, brick_texture2, NULL, &brick_rect[1][3]);
		SDL_RenderCopy(renderer, brick_texture2, NULL, &brick_rect[1][4]);
		SDL_RenderCopy(renderer, brick_texture2, NULL, &brick_rect[1][5]);
		SDL_RenderCopy(renderer, brick_texture2, NULL, &brick_rect[1][6]);
		SDL_RenderCopy(renderer, brick_texture3, NULL, &brick_rect[2][0]);
		SDL_RenderCopy(renderer, brick_texture3, NULL, &brick_rect[2][1]);
		SDL_RenderCopy(renderer, brick_texture3, NULL, &brick_rect[2][2]);
		SDL_RenderCopy(renderer, brick_texture3, NULL, &brick_rect[2][3]);
		SDL_RenderCopy(renderer, brick_texture3, NULL, &brick_rect[2][4]);
		SDL_RenderCopy(renderer, brick_texture3, NULL, &brick_rect[2][5]);
		SDL_RenderCopy(renderer, brick_texture3, NULL, &brick_rect[2][6]);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_Delay(3);
	}

	Destroy();
	SDL_Quit();
	return 0;
}