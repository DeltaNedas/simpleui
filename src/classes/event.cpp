#include "simpleui.h"

using namespace SimpleUI;

// EventType

EventType::EventType(Frame* caller) {
	Caller = caller;
}

// Event callbacks

bool mousePressed = false;

void SimpleUI::updateEvents() {
	switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			mousePressed = true;
			break;
		case SDL_MOUSEBUTTONUP:
			for (Frame* frame : VisibleFrameInstances) {
				if (mousePressed) {
					EventCallback callback = frame->getEventCallbacks()[(int) EventEnum::MOUSE_CLICK];
					if (callback != NULL) {
						EventType callbackEvent(frame);
						callbackEvent.MouseButtonEvent = event.button;
						callback(callbackEvent);
					}
				}
			}
			mousePressed = false;
			break;
		case SDL_MOUSEMOTION:
			for (Frame* frame : VisibleFrameInstances) {
				EventCallback callback = frame->getEventCallbacks()[(int) EventEnum::MOUSE_MOVED];
				if (callback != NULL) {
					EventType callbackEvent(frame);
					callbackEvent.MouseMotionEvent = event.motion;
					callback(callbackEvent);
				}
			}
			break;
		case SDL_KEYDOWN:
			for (Frame* frame : VisibleFrameInstances) {
				EventCallback callback = frame->getEventCallbacks()[(int) EventEnum::KEY_DOWN];
				if (callback != NULL && event.key.repeat == 0) {
					EventType callbackEvent(frame);
					callbackEvent.KeyboardEvent = event.key;
					callback(callbackEvent);
				}
			}
			break;
		case SDL_KEYUP:
			for (Frame* frame : VisibleFrameInstances) {
				EventCallback callback = frame->getEventCallbacks()[(int) EventEnum::KEY_UP];
				if (callback != NULL && event.key.repeat == 0) {
					EventType callbackEvent(frame);
					callbackEvent.KeyboardEvent = event.key;
					callback(callbackEvent);
				}
			}
			break;
		/*case SDL_MOUSEWHEEL:
			for (Frame* frame : VisibleFrameInstances) {
				EventCallback callback = frame->getEventCallbacks()[(int) EventEnum::SCROLL];
				if (callback != NULL) {
					EventType callbackEvent(frame);
					callbackEvent.MouseWheelEvent = event.scroll;
					callback(callbackEvent);
				}
			}
			break;*/
	}
	for (Frame* frame : VisibleFrameInstances) {
		if (mousePressed) {
			EventCallback callback = frame->getEventCallbacks()[(int) EventEnum::MOUSE_DOWN];
			if (callback != NULL) {
				EventType callbackEvent(frame);
				callbackEvent.MouseButtonEvent = event.button;
				callback(callbackEvent);
			}
		} else {
			EventCallback callback = frame->getEventCallbacks()[(int) EventEnum::MOUSE_UP];
			if (callback != NULL) {
				EventType callbackEvent(frame);
				callbackEvent.MouseButtonEvent = event.button;
				callback(callbackEvent);
			}
		}
	}
}
