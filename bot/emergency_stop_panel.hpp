#pragma once
#include "gui.hpp"

class EmergencyStopPanel : public wxPanel
{
public:
  EmergencyStopPanel(wxWindow *parent);

  // Getters for the stop duration values
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

private:
  wxTextCtrl *stopHourCtrl;
  wxTextCtrl *stopMinCtrl;
  wxTextCtrl *stopSecCtrl;
  wxTextCtrl *stopMsCtrl;
};
