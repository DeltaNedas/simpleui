#include "simpleui.h"

using namespace SimpleUI;

// TextType

TextType::TextType() {
	TextInstances.insert(this);
}

TextType::TextType(FC_Font* font, std::string text) {
	setFont(font);
	setText(text);
	TextInstances.insert(this);
}

TextType::~TextType() {
	if (Font) {
		FC_FreeFont(Font);
	}
}

void TextType::setText(std::string text) {
	Text = text;
	updateSize();
}

void TextType::setFont(FC_Font* font) {
	Font = font;
}

void TextType::setColour(ColourType* colour) {
	Colour = colour;
	if (Font != NULL) {
		FC_SetDefaultColor(Font, FC_MakeColor(colour->R, colour->G, colour->B, colour->A));
	}
}

void TextType::setWrap(bool wrap) {
	Wrap = wrap;
}

void TextType::setScaleX(bool scaleX) {
	ScaleX = scaleX;
}

void TextType::setScaleY(bool scaleY) {
	ScaleY = scaleY;
}

void TextType::updateSize() {
	if (Font != NULL) {
		int w = FC_GetWidth(Font, Text);
		int h = FC_GetHeight(Font, Text);
		Size = Vec2(w, h);
	}
}

std::string TextType::getText() {
	return Text;
}

FC_Font* TextType::getFont() {
	return Font;
}

ColourType* TextType::getColour() {
	return Colour;
}

bool TextType::getWrap() {
	return Wrap;
}

bool TextType::getScaleX() {
	return ScaleX;
}

bool TextType::getScaleY() {
	return ScaleY;
}

Vec2 TextType::getSize() {
	return Size;
}
