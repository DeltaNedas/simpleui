#include "simpleui.h"

using namespace SimpleUI;

// Frame

Frame::Frame() {
	EventCallbacks.resize(10);
	setPivot(SizeType(Vec2(0.5, 0.5), Vec2(0, 0)));
	setSize(SizeType(Vec2(0.5, 0.5), Vec2(0, 0)));
	setPosition(SizeType(Vec2(0.25, 0.25), Vec2(0, 0)));

	FrameInstances.insert(this);
}

void Frame::setSize(SizeType size) {
	Size = size;
	int totalX = Size.Offset.X;
	int totalY = Size.Offset.Y;

	if (Size.Scale.X > 0.0 || Size.Scale.Y > 0.0) {
		if (Parent == NULL) {
			if (window) {
				totalX += static_cast<int>(windowSize.X * Size.Scale.X);
				totalY += static_cast<int>(windowSize.Y * Size.Scale.Y);
			} else {
				throw std::runtime_error("SDL Window must be created before scaling with it.");
			}
		} else {
			Vec2 parentSize = Parent->getAbsoluteSize();
			int parentX = parentSize.X;
			int parentY = parentSize.Y;

			totalX += static_cast<int>(parentX * Size.Scale.X);
			totalY += static_cast<int>(parentY * Size.Scale.Y);
		}
	}
	AbsoluteSize = Vec2(totalX, totalY);
}

void Frame::setPosition(SizeType position) {
	Position = position;
	int totalX = Position.Offset.X - 2;
	int totalY = Position.Offset.Y - 2;

	if (Position.Scale.X > 0.0 || Position.Scale.Y > 0.0) {
		if (Parent == NULL) {
			int screenX = 0;
			int screenY = 0;

			if (window) {
				SDL_GetWindowSize(window, &screenX, &screenY);
				totalX += static_cast<int>(screenX * Position.Scale.X);
				totalY += static_cast<int>(screenY * Position.Scale.Y);
			} else {
				SimpleUI_Log("SDL Window must be created before scaling with it.", Level::WARN);
			}
		} else {
			Vec2 parentSize = Parent->getAbsoluteSize();
			Vec2 parentPosition = Parent->getAbsolutePosition();
			int parentX = parentSize.X;
			int parentY = parentSize.Y;
			totalX += parentPosition.X;
			totalY += parentPosition.Y;

			totalX += static_cast<int>(parentX * Position.Scale.X);
			totalY += static_cast<int>(parentY * Position.Scale.Y);
		}
	}

	AbsolutePosition = Vec2(totalX, totalY);
}

void Frame::setVisible(bool visible, bool recursive) {
	Visible = visible;
	if (visible) {
		VisibleFrameInstances.insert(this);
	} else {
		VisibleFrameInstances.erase(this);
	}
	setParent(Parent);
	if (recursive) {
		for (Frame* frame : Children) {
			frame->setVisible(visible, true);
		}
	}
}

void Frame::setAnchored(bool anchored, bool recursive) {
	Anchored = anchored;
	if (recursive) {
		for (Frame* frame : Children) {
			frame->setAnchored(anchored, true);
		}
	}
}

void Frame::setParent(Frame* parent) {
	if (parent == this) {
		throw std::runtime_error("Frame cannot be its own parent.");
	}
	if (Parent != NULL) {
		Parent->Children.erase(this);
	}
	if (parent != NULL) {
		parent->Children.insert(this);
	}
	setPosition(Position);
	setSize(Size);
	Parent = parent;
}

void Frame::setTexture(TextureType* texture) {
	Texture = texture;
}

void Frame::setText(TextType* text) {
	Text = text;
}

void Frame::setEventCallback(EventEnum enumEvent, EventCallback eventCallback) {
	EventCallbacks.at((int) enumEvent) = eventCallback;
}

void Frame::setAnimation(AnimationType* animation) {
	Animation = animation;
}

void Frame::setAnimationFrame(unsigned int frame) {
	CurrentFrame = (unsigned int) std::clamp((int) frame, 0, (int) Animation->getFrames().size());
}

void Frame::setPivot(SizeType pivot) {
	Pivot = pivot;

	int totalX = Pivot.Offset.X;
	int totalY = Pivot.Offset.Y;

	if (Size.Scale.X > 0.0 || Size.Scale.Y > 0.0) {
		if (Parent == NULL) {
			totalX += static_cast<int>(AbsoluteSize.X * Pivot.Scale.X);
			totalY += static_cast<int>(AbsoluteSize.Y * Pivot.Scale.Y);
		} else {
			Vec2 parentPivot = Parent->getAbsolutePivot();
			int parentX = parentPivot.X;
			int parentY = parentPivot.Y;
			
			totalX += static_cast<int>(parentX * Pivot.Scale.X);
			totalY += static_cast<int>(parentY * Pivot.Scale.Y);
		}
	}

	AbsolutePivot = Vec2(totalX, totalY);
}

void Frame::setRotation(double rotation) {
	Rotation = rotation;
}


void Frame::toggleVisible(bool recursive) {
	if (Visible) {
		setVisible(false, recursive);
	} else {
		setVisible(true, recursive);
	}
}

void Frame::toggleAnchored(bool recursive) {
	Anchored = Anchored ? false : true;
	if (recursive) {
		for (Frame* frame : Children) {
			frame->toggleAnchored(true);
		}
	}
}

bool Frame::isPointInBounds(Vec2 point, bool absolute) {
	if (absolute) {
		Vec2 cameraPos = Vec2(camera.X, camera.Y);
		Vec2 pos = AbsolutePosition + cameraPos;
		Vec2 size = AbsoluteSize + AbsolutePosition + cameraPos;
		return (pos.X < point.X) && (pos.Y < point.Y) && (size.X > point.X) && (size.Y > point.Y);
	}
	Vec2 size = AbsoluteSize;
	return (size.X > point.X) && (size.Y > point.Y);
}

bool Frame::isPointInBounds(int pointX, int pointY, bool absolute) {
	return isPointInBounds(Vec2(pointX, pointY), absolute);
}

void Frame::nextAnimationFrame() {
	if (CurrentFrame < Animation->getFrames().size()) {
		CurrentFrame++;
	} else {
		CurrentFrame = 0;
	}
}

void Frame::prevAnimationFrame() {
	if (CurrentFrame > 0) {
		CurrentFrame--;
	} else {
		CurrentFrame = Animation->getFrames().size();
	}
}


SizeType Frame::getSize() {
	return Size;
}

SizeType Frame::getPosition() {
	return Position;
}

Vec2 Frame::getAbsoluteSize() {
	return AbsoluteSize;
}

Vec2 Frame::getAbsolutePosition() {
	return AbsolutePosition;
}

bool Frame::getVisible() {
	return Visible;
}

bool Frame::getAnchored() {
	return Anchored;
}

Frame* Frame::getParent() {
	return Parent;
}

std::set<Frame*> Frame::getChildren() {
	return Children;
}

TextureType* Frame::getTexture() {
	return Texture;
}

TextType* Frame::getText() {
	return Text;
}

std::set<EventEnum> Frame::getEventTypes() {
	return EventTypes;
}

std::vector<EventCallback> Frame::getEventCallbacks() {
	return EventCallbacks;
}

AnimationType* Frame::getAnimation() {
	return Animation;
}

unsigned int Frame::getAnimationFrame() {
	return CurrentFrame;
}

SizeType Frame::getPivot() {
	return Pivot;
}

Vec2 Frame::getAbsolutePivot() {
	return AbsolutePivot;
}

double Frame::getRotation() {
	return Rotation;
}
