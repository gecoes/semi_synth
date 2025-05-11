// KeyboardInput.h
#ifndef SDLKEYBOARDINPUT_H
#define SDLKEYBOARDINPUT_H

#include "InputSource.h"
#include <SDL2/SDL.h>
#include <set>

class KeyboardInput : public InputSource {
public:
  KeyboardInput();
  ~KeyboardInput() override;

  void processInput(SignalSource &signalSource) override;
  bool isEditMode() const override;
  int getSelectedChannel() const override;
  bool shouldExit() const;

private:
  void handleKeyDown(SDL_Keycode key, SignalSource &signalSource);
  void handleKeyUp(SDL_Keycode key, SignalSource &signalSource);

  bool mEditMode;
  int mSelectedChannel;
  int mSelectedSignal;
  bool mExit;
  std::set<SDL_Keycode> mPressedKeys;
};

#endif // SDLKEYBOARDINPUT_H
