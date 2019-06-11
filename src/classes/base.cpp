#include "simpleui.h"

using namespace SimpleUI;

// Vec2

Vec2::Vec2(int x, int y) {
	X = static_cast<double>(x);
	Y = static_cast<double>(y);
}

Vec2::Vec2(double x, double y) {
	X = x;
	Y = y;
}

bool Vec2::operator==(const Vec2 compare) {
	return X == compare.X && Y == compare.Y;
}

Vec2 Vec2::operator+(const Vec2 add) {
	return Vec2(X + add.X, Y + add.Y);
}

Vec2 Vec2::operator-(const Vec2 sub) {
	return Vec2(X - sub.X, Y - sub.Y);
}

Vec2 Vec2::operator*(const Vec2 mul) {
	return Vec2(X * mul.X, Y * mul.Y);
}

Vec2 Vec2::operator*(const double mul) {
	return Vec2(X * mul, Y * mul);
}

Vec2 Vec2::operator/(const Vec2 div) {
	return Vec2(X / div.X, Y / div.Y);
}

Vec2 Vec2::operator/(const double div) {
	return Vec2(X / div, Y / div);
}

void Vec2::operator+=(const Vec2 add) {
	Vec2 result = operator+(add);
	X = result.X;
	Y = result.Y;
}

void Vec2::operator-=(const Vec2 sub) {
	Vec2 result = operator-(sub);
	X = result.X;
	Y = result.Y;
}

void Vec2::operator*=(const Vec2 mul) {
	Vec2 result = operator*(mul);
	X = result.X;
	Y = result.Y;
}

void Vec2::operator*=(const double mul) {
	Vec2 result = operator*(mul);
	X = result.X;
	Y = result.Y;
}

void Vec2::operator/=(const Vec2 div) {
	Vec2 result = operator/(div);
	X = result.X;
	Y = result.Y;
}

void Vec2::operator/=(const double div) {
	Vec2 result = operator/(div);
	X = result.X;
	Y = result.Y;
}

std::string Vec2::to_string() {
	return "X: " + SimpleUI::to_string(X) + ", Y: " + SimpleUI::to_string(Y);
}

// SizeType

SizeType::SizeType() {
	setScale(Vec2(1, 1));
	setOffset(Vec2(0, 0));
}

SizeType::SizeType(Vec2 scale, Vec2 offset) {
	setScale(scale);
	setOffset(offset);
}

void SizeType::setScale(Vec2 scale) {
	Scale = scale;
}

void SizeType::setOffset(Vec2 offset) {
	Offset = offset;
}

std::string SizeType::to_string() {
	return "Scale: {" + Scale.to_string() + "}, Offset: {" + Offset.to_string() + "}";
}

// ColourType

ColourType::ColourType(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	R = r, G = g, B = b, A = a;
	ColourInstances.insert(this); //Segfaults, no fukin idea why
}

std::string ColourType::to_string() {
	return "R: " + std::to_string(R) + ", G: " + std::to_string(G) + ", B: " + std::to_string(B) + ", A: " + std::to_string(A);
}

void ColourType::invert(bool invertAlpha) {
	R = 255 - R;
	G = 255 - G;
	B = 255 - B;
	if (invertAlpha) {
		A = 255 - A;
	}
}

void ColourType::greyScale() {
	int average = (R + G + B) / 3;
	R = average;
	G = average;
	B = average;
}
