// KeyboardInput.cpp
#include "KeyboardInput.h"
#include "SignalSource.h"
#include <cmath>
#include <iostream>
#include <unordered_map>

KeyboardInput::KeyboardInput()
    : mEditMode(false), mSelectedChannel(0), mSelectedSignal(0), mExit(false) {
  SDL_Init(SDL_INIT_VIDEO); // Necessari per capturar teclat
  SDL_Window *window =
      SDL_CreateWindow("Synth Input", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 200, 100, SDL_WINDOW_SHOWN);
}

KeyboardInput::~KeyboardInput() { SDL_Quit(); }

void KeyboardInput::processInput(SignalSource &signalSource) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      mExit = true;
      break;
    case SDL_KEYDOWN:
      handleKeyDown(event.key.keysym.sym, signalSource);
      break;
    case SDL_KEYUP:
      handleKeyUp(event.key.keysym.sym, signalSource);
      break;
    default:
      // Ignora altres esdeveniments com el moviment del ratolí
      break;
    }
  }
}

void KeyboardInput::handleKeyDown(SDL_Keycode key, SignalSource &signalSource) {
  std::cout << "Key pressed: " << key << std::endl;
  if (key == SDLK_ESCAPE) {
    mExit = true;
    return;
  }
  if (key == SDLK_e) {
    mEditMode = !mEditMode;
    std::cout << (mEditMode ? "Edit mode ON" : "Edit mode OFF") << std::endl;
    return;
  }
  if (mEditMode) {
    if (key >= SDLK_0 && key <= SDLK_9) {
      mSelectedChannel = key - SDLK_0;
      signalSource.deactivateChannels();
      std::cout << "Selected channel: " << mSelectedChannel << std::endl;
      signalSource.getChannels()[mSelectedChannel]->activateChannel();
      return;
    }
    if (key == SDLK_q)
      mSelectedSignal = 0;
    if (key == SDLK_w)
      mSelectedSignal = 1;
    if (key == SDLK_e)
      mSelectedSignal = 2;
    if (key == SDLK_r)
      mSelectedSignal = 3;
    if (key == SDLK_UP) {
      // Augmentar freq
      signalSource.setChannelFrequency(
          mSelectedChannel, mSelectedSignal,
          signalSource.getChannels()[mSelectedChannel]->getSignalFrequency(
              mSelectedSignal) *
              1.05f);
    }
    if (key == SDLK_DOWN) {
      // Reduir freq
      signalSource.setChannelFrequency(
          mSelectedChannel, mSelectedSignal,
          signalSource.getChannels()[mSelectedChannel]->getSignalFrequency(
              mSelectedSignal) *
              0.95f);
    }
    if (key == SDLK_LEFT) {
      // Reduir volum
      signalSource.setChannelVolume(
          mSelectedChannel, mSelectedSignal,
          signalSource.getChannels()[mSelectedChannel]->getSignalAmplitude(
              mSelectedSignal) *
              0.9f);
    }
    if (key == SDLK_RIGHT) {
      // Augmentar volum
      signalSource.setChannelVolume(
          mSelectedChannel, mSelectedSignal,
          signalSource.getChannels()[mSelectedChannel]->getSignalAmplitude(
              mSelectedSignal) *
              1.1f);
    }
  } else {
    if (!mPressedKeys.contains(key)) {
      mPressedKeys.insert(key);
      int ch = (int)key % signalSource.getChannels().size();
      mSelectedChannel = ch;
      signalSource.getChannels()[ch]->activateChannel();
    }
  }
}

void KeyboardInput::handleKeyUp(SDL_Keycode key, SignalSource &signalSource) {
  mPressedKeys.erase(key);
  int ch = (int)key % signalSource.getChannels().size();
  if (!mEditMode) {
    signalSource.getChannels()[ch]->deactivateChannel();
  }
}

bool KeyboardInput::isEditMode() const { return mEditMode; }

int KeyboardInput::getSelectedChannel() const { return mSelectedChannel; }

bool KeyboardInput::shouldExit() const { return mExit; }
