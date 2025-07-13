#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/statbox.h>

class IntervalPanel : public wxPanel
{
public:
  IntervalPanel(wxWindow *parent);

  // Getters for the interval values
  long GetHours() const;
  long GetMinutes() const;
  long GetSeconds() const;
  long GetMilliseconds() const;
  long GetTotalMilliseconds() const;

  // Setters (optional)
  void SetHours(long val);
  void SetMinutes(long val);
  void SetSeconds(long val);
  void SetMilliseconds(long val);

  // Target/original fields
  void GetTarget(long &x, long &y) const;
  void SetTarget(long x, long y);
  void GetOriginal(long &x, long &y) const;
  void SetOriginal(long x, long y);

  // Cursor position label
  void SetCursorPosLabel(const wxString &text);
  wxString GetCursorPosLabel() const;

  // Click status label
  void SetClickStatusLabel(const wxString &text);
  wxString GetClickStatusLabel() const;

  // Return click checkbox
  bool IsReturnClickEnabled() const;
  void SetReturnClickEnabled(bool enabled);

  // Offset slider
  int GetRandomOffsetMs() const;
  void SetRandomOffsetMs(int ms);

private:
  wxTextCtrl *intervalHourCtrl;
  wxTextCtrl *intervalMinCtrl;
  wxTextCtrl *intervalSecCtrl;
  wxTextCtrl *intervalMsCtrl;
  wxTextCtrl *originalXCtrl;
  wxTextCtrl *originalYCtrl;
  wxTextCtrl *targetXCtrl;
  wxTextCtrl *targetYCtrl;
  wxStaticText *cursorPosLabel;
  wxStaticText *clickStatusLabel;
  wxCheckBox *returnClickCheckBox;
  wxSlider *offsetSlider;
};
