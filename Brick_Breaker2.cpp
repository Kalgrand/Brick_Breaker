#include <iostream>
#include <SDL.h>
using namespace std;

bool quit = false;
SDL_Event event;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* ball;
SDL_Surface* background;
SDL_Surface* floor1;
SDL_Surface* brick;
SDL_Surface* brick2;
SDL_Surface* brick3;
SDL_Texture* ball_texture;
SDL_Texture* background_texture;
SDL_Texture* floor_texture;
SDL_Texture* brick_texture;
SDL_Texture* brick_texture2;
SDL_Texture* brick_texture3;
SDL_Rect brick_rect[3][7];
SDL_Rect ball_rect;
int ball_x = 200;
int ball_y = 200;
int ball_vel_x = 1;
int ball_vel_y = 1;
int background_w = 800;
int background_h = 600;
int brick_w = 80;
int brick_h = 35;
int background_min_w = 0;
int background_min_h = 0;
int floor_x = background_w / 2;
int floor_y = background_h - 30;
int delete_brick_count = 0;
int no_of_brick = 21;

void InitializerBrick() {
	brick_rect[0][0] = { 50, 50, brick_w, brick_h };
	brick_rect[0][1] = { 150, 50, brick_w, brick_h };
	brick_rect[0][2] = { 250, 50, brick_w, brick_h };
	brick_rect[0][3] = { 350, 50, brick_w, brick_h };
	brick_rect[0][4] = { 450, 50, brick_w, brick_h };
	brick_rect[0][5] = { 550, 50, brick_w, brick_h };
	brick_rect[0][6] = { 650, 50, brick_w, brick_h };
	brick_rect[1][0] = { 50, 100, brick_w, brick_h };
	brick_rect[1][1] = { 150, 100, brick_w, brick_h };
	brick_rect[1][2] = { 250, 100, brick_w, brick_h };
	brick_rect[1][3] = { 350, 100, brick_w, brick_h };
	brick_rect[1][4] = { 450, 100, brick_w, brick_h };
	brick_rect[1][5] = { 550, 100, brick_w, brick_h };
	brick_rect[1][6] = { 650, 100, brick_w, brick_h };
	brick_rect[2][0] = { 50, 150, brick_w, brick_h };
	brick_rect[2][1] = { 150, 150, brick_w, brick_h };
	brick_rect[2][2] = { 250, 150, brick_w, brick_h };
	brick_rect[2][3] = { 350, 150, brick_w, brick_h };
	brick_rect[2][4] = { 450, 150, brick_w, brick_h };
	brick_rect[2][5] = { 550, 150, brick_w, brick_h };
	brick_rect[2][6] = { 650, 150, brick_w, brick_h };
}

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
	int ballscaling = 20;
	if (ball_y + ballscaling >= floor_y && ball_y + ballscaling <= floor_y + 30 &&
		ball_x + ballscaling >= floor_x && ball_x + ballscaling <= floor_x + 60) {
		ball_vel_y =- ball_vel_y;
	}
}

bool brickCollisionDetect(SDL_Rect rect1, SDL_Rect rect2) {
	if (rect1.x > rect2.x + rect2.w) {
		return false;
	}
	if (rect1.x + rect1.w < rect2.x) {
		return false;
	}
	if (rect1.y > rect2.y + rect2.h) {
		return false;
	}
	if (rect1.y + rect2.h < rect2.y) {
		return false;
	}
	return true;
}

void brickCollision() {
	bool a;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			a = brickCollisionDetect(brick_rect[i][j], ball_rect);
			if (a == true) {
				brick_rect[i][j].x = 3000;
				ball_vel_y = -ball_vel_y;
				delete_brick_count++;
			}
			a = false;
		}
	}
}

void Destroy() {
	SDL_DestroyTexture(floor_texture);
	SDL_DestroyTexture(brick_texture);
	SDL_DestroyTexture(brick_texture2);
	SDL_DestroyTexture(brick_texture3);
	SDL_DestroyTexture(background_texture);
	SDL_DestroyTexture(ball_texture);
	SDL_FreeSurface(floor1);
	SDL_FreeSurface(brick);
	SDL_FreeSurface(brick2);
	SDL_FreeSurface(brick3);
	SDL_FreeSurface(background);
	SDL_FreeSurface(ball);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void winning() {
	SDL_Surface* win = SDL_LoadBMP("win.bmp");
	SDL_Texture* win_texture = SDL_CreateTextureFromSurface(renderer, win);
	SDL_Rect win_rect = { 250, 200, 350, 350 };
	SDL_RenderCopy(renderer, win_texture, NULL, &win_rect);
	SDL_RenderPresent(renderer);
	SDL_Delay(10000);
	Destroy();
	SDL_Quit();
}

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