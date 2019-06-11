#include "simpleui.h"

using namespace SimpleUI;

std::string getVersion() {
	return "@@VERSION@@";
}

std::set<Frame*> FrameInstances = {};
std::set<Frame*> VisibleFrameInstances = {};
std::set<TextType*> TextInstances = {};
std::set<ColourType*> ColourInstances = {};
std::set<TextureType*> TextureInstances = {};
std::set<AnimationType*> AnimationInstances = {};

bool SimpleUI_debug = false;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Surface* screenSurface = nullptr;
SDL_Event event;

Vec2 windowSize;
Vec2 cameraBounds;

void Camera::Move(int x, int y) {
	Move((double) x, (double) y);
}

void Camera::Move(double x, double y) {
	X -= x;
	Y -= y;
	if (X > cameraBounds.X) {
		X = cameraBounds.X;
	} else if (X < 0) {
		X = 0;
	}
	if (Y > cameraBounds.Y) {
		Y = cameraBounds.Y;
	} else if (Y < 0) {
		Y = 0;
	}
}

Camera camera;
