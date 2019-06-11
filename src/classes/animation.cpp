#include "simpleui.h"

using namespace SimpleUI;

// AnimationType

AnimationType::AnimationType(std::vector<TextureType*> frames) {
	Frames = frames;
}

// Read header
/* void AnimationType::setFrames(std::vector<TextureType*> frames) {
	if (frames) {
		Frames = {};
	} else {
		Frames = frames;
	}
} */

std::vector<TextureType*> AnimationType::getFrames() {
	return Frames;
}

bool AnimationType::operator() () {
	return Frames.size() > 0;
}
