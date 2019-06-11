#include "simpleui.h"

using namespace SimpleUI;

std::string getVersion() {
	return "0.1.2";
}

std::set<Frame*> SimpleUI::FrameInstances = {};
std::set<Frame*> SimpleUI::VisibleFrameInstances = {};
std::set<TextType*> SimpleUI::TextInstances = {};
std::set<ColourType*> SimpleUI::ColourInstances = {};
std::set<TextureType*> SimpleUI::TextureInstances = {};
std::set<AnimationType*> SimpleUI::AnimationInstances = {};

SDL_Window* SimpleUI::window = nullptr;
SDL_Renderer* SimpleUI::renderer = nullptr;
SDL_Surface* SimpleUI::screenSurface = nullptr;
SDL_Event SimpleUI::event;

Vec2 SimpleUI::windowSize;
Vec2 SimpleUI::cameraBounds;

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

Camera SimpleUI::camera;
