#include "interval_panel.hpp"
#define MIN_WIDTH_COL 60
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/checkbox.h>
#include <wx/statline.h>

IntervalPanel::IntervalPanel(wxWindow *parent)
    : wxPanel(parent, wxID_ANY)
{
  auto *intervalBox = new wxStaticBox(this, wxID_ANY, "Click Interval");
  auto *intervalSizer = new wxStaticBoxSizer(intervalBox, wxVERTICAL);
  auto *intervalGrid = new wxFlexGridSizer(1, 8, 10, 10);

  intervalHourCtrl = new wxTextCtrl(this, wxID_ANY, "0");
  intervalMinCtrl = new wxTextCtrl(this, wxID_ANY, "0");
  intervalSecCtrl = new wxTextCtrl(this, wxID_ANY, "0");
  intervalMsCtrl = new wxTextCtrl(this, wxID_ANY, "0");

  auto *lblHour = new wxStaticText(this, wxID_ANY, "hours");
  auto *lblMin = new wxStaticText(this, wxID_ANY, "mins");
  auto *lblSec = new wxStaticText(this, wxID_ANY, "secs");
  auto *lblMs = new wxStaticText(this, wxID_ANY, "milliseconds");

  intervalHourCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  intervalMinCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  intervalSecCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  intervalMsCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));

  intervalGrid->Add(intervalHourCtrl, 1, wxEXPAND | wxRIGHT, 2);
  intervalGrid->Add(lblHour, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  intervalGrid->Add(intervalMinCtrl, 1, wxEXPAND | wxRIGHT, 2);
  intervalGrid->Add(lblMin, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  intervalGrid->Add(intervalSecCtrl, 1, wxEXPAND | wxRIGHT, 2);
  intervalGrid->Add(lblSec, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  intervalGrid->Add(intervalMsCtrl, 1, wxEXPAND | wxRIGHT, 2);
  intervalGrid->Add(lblMs, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);

  intervalGrid->AddGrowableCol(0, 1);
  intervalGrid->AddGrowableCol(2, 1);
  intervalGrid->AddGrowableCol(4, 1);
  intervalGrid->AddGrowableCol(6, 1);

  intervalSizer->Add(intervalGrid, 0, wxALL | wxEXPAND, 2);

  // --- Offset slider ---
  auto *offsetSizer = new wxBoxSizer(wxHORIZONTAL);
  auto *offsetLabel = new wxStaticText(this, wxID_ANY, "Random Offset +- 200ms");
  offsetSlider = new wxSlider(this, wxID_ANY, 200, 0, 20000, wxDefaultPosition, wxSize(120, -1));
  offsetLabel->SetToolTip(
      "Randomly adds or subtracts up to this ms to each click interval.\n"
      "e.g. 200ms = up to 200ms shorter or longer than your click interval\n"
      "(a total range of 400ms)");
  offsetSizer->Add(offsetLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
  offsetSizer->Add(offsetSlider, 1, wxALIGN_CENTER_VERTICAL);
  intervalSizer->Add(offsetSizer, 0, wxALL | wxEXPAND, 8);
  offsetSlider->Bind(wxEVT_SLIDER, [this, offsetLabel](wxCommandEvent &evt)
                     { offsetLabel->SetLabel(wxString::Format("Random Offset +- %dms", offsetSlider->GetValue())); });

  // --- Divider before original position ---
  auto *origDivider = new wxStaticLine(this, wxID_ANY);
  intervalSizer->Add(origDivider, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 8);

  // --- Original position controls ---
  auto *origTitle = new wxStaticText(this, wxID_ANY, "TODO: Original");
  origTitle->SetToolTip(
      "Currently unused\n"
      "Returns back to original cursor right now.");
  intervalSizer->Add(origTitle, 0, wxLEFT, 8);
  auto *origGrid = new wxFlexGridSizer(2, 4, 10, 10);
  auto *lblOriginalX = new wxStaticText(this, wxID_ANY, "X");
  originalXCtrl = new wxTextCtrl(this, wxID_ANY, "0");
  auto *lblOriginalY = new wxStaticText(this, wxID_ANY, "Y");
  originalYCtrl = new wxTextCtrl(this, wxID_ANY, "0");
  originalXCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  originalYCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  origGrid->Add(lblOriginalX, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  origGrid->Add(originalXCtrl, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
  origGrid->Add(lblOriginalY, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  origGrid->Add(originalYCtrl, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
  intervalSizer->Add(origGrid, 0, wxALL | wxEXPAND, 8);

  // --- Target controls ---
  auto *targetTitle = new wxStaticText(this, wxID_ANY, "Target");
  intervalSizer->Add(targetTitle, 0, wxLEFT, 8);
  auto *targetGrid = new wxFlexGridSizer(1, 4, 10, 10);
  auto *lblTargetX = new wxStaticText(this, wxID_ANY, "X");
  targetXCtrl = new wxTextCtrl(this, wxID_ANY, "0");
  auto *lblTargetY = new wxStaticText(this, wxID_ANY, "Y");
  targetYCtrl = new wxTextCtrl(this, wxID_ANY, "0");
  targetXCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  targetYCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  targetGrid->Add(lblTargetX, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  targetGrid->Add(targetXCtrl, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
  targetGrid->Add(lblTargetY, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  targetGrid->Add(targetYCtrl, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
  intervalSizer->Add(targetGrid, 0, wxALL | wxEXPAND, 8);

  // --- Cursor position label ---
  auto *cursorPosTitle = new wxStaticText(this, wxID_ANY, "Current Cursor Position");
  cursorPosLabel = new wxStaticText(this, wxID_ANY, "X: --  Y: --");
  intervalSizer->Add(cursorPosTitle, 0, wxALL | wxEXPAND, 8);
  intervalSizer->Add(cursorPosLabel, 0, wxALL | wxEXPAND, 8);

  // --- Return click checkbox ---
  returnClickCheckBox = new wxCheckBox(this, wxID_ANY, "Enable return click (click at original position after target)");
  returnClickCheckBox->SetValue(true);
  intervalSizer->Add(returnClickCheckBox, 0, wxALL, 8);

  // --- Divider before target position ---
  auto *divider = new wxStaticLine(this, wxID_ANY);
  intervalSizer->Add(divider, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 8);

  // --- Click status label ---
  clickStatusLabel = new wxStaticText(this, wxID_ANY, "Click Status: Idle");
  wxFont clickStatusFont = wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
  clickStatusFont.SetPointSize(11);
  clickStatusLabel->SetFont(clickStatusFont);
  intervalSizer->Add(clickStatusLabel, 0, wxALL | wxEXPAND, 6);

  // --- Hotkey label ---
#ifdef __WXMSW__
  auto *clickHotkeyLabel = new wxStaticText(this, wxID_ANY, "Hotkey: F13 (Windows) to Start/Stop Clicking");
#else
  auto *clickHotkeyLabel = new wxStaticText(this, wxID_ANY, "Hotkey: F12 (Mac) to Start/Stop Clicking");
#endif
  wxFont clickHotkeyFont = wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
  clickHotkeyFont.SetPointSize(9);
  clickHotkeyLabel->SetFont(clickHotkeyFont);
  intervalSizer->Add(clickHotkeyLabel, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);

  this->SetSizer(intervalSizer);
}

// --- Target/original fields ---
void IntervalPanel::GetTarget(long &x, long &y) const
{
  targetXCtrl->GetValue().ToLong(&x);
  targetYCtrl->GetValue().ToLong(&y);
}
void IntervalPanel::SetTarget(long x, long y)
{
  targetXCtrl->SetValue(wxString::Format("%ld", x));
  targetYCtrl->SetValue(wxString::Format("%ld", y));
}
void IntervalPanel::GetOriginal(long &x, long &y) const
{
  originalXCtrl->GetValue().ToLong(&x);
  originalYCtrl->GetValue().ToLong(&y);
}
void IntervalPanel::SetOriginal(long x, long y)
{
  originalXCtrl->SetValue(wxString::Format("%ld", x));
  originalYCtrl->SetValue(wxString::Format("%ld", y));
}

// --- Cursor position label ---
void IntervalPanel::SetCursorPosLabel(const wxString &text)
{
  cursorPosLabel->SetLabel(text);
}
wxString IntervalPanel::GetCursorPosLabel() const
{
  return cursorPosLabel->GetLabel();
}

// --- Click status label ---
void IntervalPanel::SetClickStatusLabel(const wxString &text)
{
  clickStatusLabel->SetLabel(text);
}
wxString IntervalPanel::GetClickStatusLabel() const
{
  return clickStatusLabel->GetLabel();
}

// --- Return click checkbox ---
bool IntervalPanel::IsReturnClickEnabled() const
{
  return returnClickCheckBox->IsChecked();
}
void IntervalPanel::SetReturnClickEnabled(bool enabled)
{
  returnClickCheckBox->SetValue(enabled);
}

// --- Offset slider ---
int IntervalPanel::GetRandomOffsetMs() const
{
  return offsetSlider->GetValue();
}
void IntervalPanel::SetRandomOffsetMs(int ms)
{
  offsetSlider->SetValue(ms);
}

long IntervalPanel::GetHours() const
{
  long val = 0;
  intervalHourCtrl->GetValue().ToLong(&val);
  return val;
}
long IntervalPanel::GetMinutes() const
{
  long val = 0;
  intervalMinCtrl->GetValue().ToLong(&val);
  return val;
}
long IntervalPanel::GetSeconds() const
{
  long val = 0;
  intervalSecCtrl->GetValue().ToLong(&val);
  return val;
}
long IntervalPanel::GetMilliseconds() const
{
  long val = 0;
  intervalMsCtrl->GetValue().ToLong(&val);
  return val;
}
long IntervalPanel::GetTotalMilliseconds() const
{
  return GetHours() * 3600000 + GetMinutes() * 60000 + GetSeconds() * 1000 + GetMilliseconds();
}
void IntervalPanel::SetHours(long val)
{
  intervalHourCtrl->SetValue(wxString::Format("%ld", val));
}
void IntervalPanel::SetMinutes(long val)
{
  intervalMinCtrl->SetValue(wxString::Format("%ld", val));
}
void IntervalPanel::SetSeconds(long val)
{
  intervalSecCtrl->SetValue(wxString::Format("%ld", val));
}
void IntervalPanel::SetMilliseconds(long val)
{
  intervalMsCtrl->SetValue(wxString::Format("%ld", val));
}
