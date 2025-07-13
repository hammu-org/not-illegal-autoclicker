#pragma once
#include <wx/wx.h>
#include <wx/event.h>
#include <wx/statline.h>
#include "move.hpp"
#include "utils.hpp"
#define MIN_WIDTH_COL 60

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
  wxTextCtrl *intervalHourCtrl, *intervalMinCtrl, *intervalSecCtrl, *intervalMsCtrl;
  wxTextCtrl *stopHourCtrl, *stopMinCtrl, *stopSecCtrl, *stopMsCtrl;
  wxTextCtrl *originalXCtrl, *originalYCtrl;
  wxTextCtrl *targetXCtrl, *targetYCtrl;
  wxStaticText *clickStatusLabel;
  wxStaticText *offsetLabel;
  wxSlider *offsetSlider;
  wxStaticText *cursorPosLabel;
  wxCheckBox *returnClickCheckBox;
  std::atomic<bool> isClicking{false};
  int randomOffsetMs = 200;
};