#include "simpleui.h"

using namespace SimpleUI;

// TextureType

TextureType::TextureType() {
	Path = "";
	setColour(new ColourType(255, 255, 255));
	setScale(Vec2(1, 1));
	TextureInstances.insert(this);
}

TextureType::TextureType(std::string path, Vec2 scale, bool clip, ColourType* colour) {
	setColour(colour);
	setClip(clip);
	setScale(scale);
	setPath(path);
	TextureInstances.insert(this);
}

TextureType::~TextureType() {
	if (Texture) {
		SDL_DestroyTexture(Texture);
	}
}

void TextureType::setPath(std::string path) {
	if (path.empty()) { //Empty, use Colour.
		SDL_ClearError();
		SDL_Surface* Surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);

		if (Surface == nullptr) {
			throw std::runtime_error("Failed to create surface: " + std::string(SDL_GetError()));
		}

		Texture = SDL_CreateTextureFromSurface(renderer, Surface);
		SDL_FillRect(Surface, NULL, SDL_MapRGBA(Surface->format, Colour->R, Colour->G, Colour->B, Colour->A));
		SDL_FreeSurface(Surface);
	} else {
		SDL_ClearError();
		SDL_Surface* Surface = IMG_Load(path.c_str());
		if (!Surface) {
			throw std::runtime_error("Image failed to load: " + std::string(IMG_GetError()));
		}

		if (Clip) {
			SDL_SetClipRect(Surface, NULL);
		}

		Texture = SDL_CreateTextureFromSurface(renderer, Surface);
		if (!Texture) {
			throw std::runtime_error("Failed to create texture: " + std::string(SDL_GetError()));
		}
		SDL_FreeSurface(Surface);
	}
	Path = path;
}

void TextureType::setScale(Vec2 scale) {
	if (scale.X == 0.0) scale.X = 1;
	if (scale.Y == 0.0) scale.Y = 1;
	Scale = scale;
	setPath(Path);
}

void TextureType::setClip(bool clip) {
	Clip = clip;
	setPath(Path);
}

void TextureType::setColour(ColourType* colour) {
	Colour = colour;
	setPath(Path);
}

SDL_Texture* TextureType::getTexture() {
	return Texture;
}

std::string TextureType::TextureType::getPath() {
	return Path;
}

Vec2 TextureType::getScale() {
	return Scale;
}

bool TextureType::getClip() {
	return Clip;
}

ColourType* TextureType::getColour() {
	return Colour;
}
