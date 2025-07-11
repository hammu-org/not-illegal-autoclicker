#ifdef _WIN32
#include <windows.h>

void moveMouse(int x, int y)
{
  SetCursorPos(x, y);
}

void leftClick()
{
  INPUT input = {0};
  input.type = INPUT_MOUSE;
  input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
  SendInput(1, &input, sizeof(INPUT));
  input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
  SendInput(1, &input, sizeof(INPUT));
}
#else
#include <ApplicationServices/ApplicationServices.h>

void moveMouse(int x, int y)
{
  CGEventRef move = CGEventCreateMouseEvent(
      NULL, kCGEventMouseMoved,
      CGPointMake(x, y),
      kCGMouseButtonLeft);
  CGEventPost(kCGHIDEventTap, move);
  CFRelease(move);
}

void leftClick()
{
  CGPoint current = CGEventGetLocation(CGEventCreate(NULL));
  CGEventRef click_down = CGEventCreateMouseEvent(
      NULL, kCGEventLeftMouseDown, current, kCGMouseButtonLeft);
  CGEventRef click_up = CGEventCreateMouseEvent(
      NULL, kCGEventLeftMouseUp, current, kCGMouseButtonLeft);
  CGEventPost(kCGHIDEventTap, click_down);
  CGEventPost(kCGHIDEventTap, click_up);
  CFRelease(click_down);
  CFRelease(click_up);
}
#endif
