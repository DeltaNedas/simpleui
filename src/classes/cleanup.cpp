#include "simpleui.h"

using namespace SimpleUI;

// Cleaning up the frames to prevent memory leaks and stuff

void SimpleUI::cleanUpFrame(Frame* frame) {
	if (frame) {
		for (Frame* child : frame->getChildren()) {
			SimpleUI::cleanUpFrame(child);
			child->setParent();
		}
	}

	VisibleFrameInstances.erase(frame);
	FrameInstances.erase(frame);
}

int SimpleUI::cleanUpTexts() {
	int ret = 0;
	std::set<TextType*> texts = TextInstances;
	for (TextType* text : texts) {
		delete text;
		ret++;
	}
	return ret;
}

int SimpleUI::cleanUpColours() {
	int ret = 0;
	std::set<ColourType*> colours = ColourInstances;
	for (ColourType* colour : colours) {
		delete colour;
		ret++;
	}
	return ret;
}

int SimpleUI::cleanUpTextures() {
	int ret = 0;
	std::set<TextureType*> textures = TextureInstances;
	for (TextureType* texture : textures) {
		delete texture;
		ret++;
	}
	return ret;
}

int SimpleUI::cleanUpAnimations() {
	int ret = 0;
	std::set<AnimationType*> animations = AnimationInstances;
	for (AnimationType* animation : animations) {
		delete animation;
		ret++;
	}
	return ret;
}

int SimpleUI::cleanUpFrames() {
	int ret = 0;
	std::set<Frame*> frames = FrameInstances;
	for (Frame* frame : frames) {
		cleanUpFrame(frame);
		delete frame;
		ret++;
	}
	return ret;
}

void SimpleUI::cleanUpSimpleUI() {
	SimpleUI_Log("\t" + std::to_string(SimpleUI::cleanUpTexts()) + " text(s) cleaned up.", Level::DEBUG);
	SimpleUI_Log("\t" + std::to_string(SimpleUI::cleanUpColours()) + " colour(s) cleaned up.", Level::DEBUG);
	SimpleUI_Log("\t" + std::to_string(SimpleUI::cleanUpTextures()) + " texture(s) cleaned up.", Level::DEBUG);
	SimpleUI_Log("\t" + std::to_string(SimpleUI::cleanUpAnimations()) + " animation(s) cleaned up.", Level::DEBUG);
	SimpleUI_Log("\t" + std::to_string(SimpleUI::cleanUpFrames()) + " frame(s) cleaned up.", Level::DEBUG);
}
