#pragma once

class EmergencyStopPanel;
#include <wx/wx.h>
#include <wx/event.h>
#include <wx/statline.h>
#include "move.hpp"
#include "utils.hpp"
#define MIN_WIDTH_COL 60

class IntervalPanel;
class MyFrame : public wxFrame
{
public:
  enum
  {
    ID_HOTKEY_F12 = wxID_HIGHEST + 1
  };
  MyFrame();
  void OnMouseLeftDown(wxMouseEvent &event);
  void OnClick(wxCommandEvent &);
  void OnHotkey(wxKeyEvent &);
  void OnClose(wxCloseEvent &event);
  void StartClickLoop();
  void StopClickLoop();

private:
  IntervalPanel *intervalPanel = nullptr;
  std::atomic<bool> isClicking{false};
  int randomOffsetMs = 200;
  EmergencyStopPanel *emergencyStopPanel = nullptr;
};