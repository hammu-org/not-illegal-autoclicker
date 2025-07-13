#include "emergency_stop_panel.hpp"

EmergencyStopPanel::EmergencyStopPanel(wxWindow *parent)
    : wxPanel(parent, wxID_ANY)
{
  auto *stopBox = new wxStaticBox(this, wxID_ANY, "Emergency Stop (Max Duration)");
  auto *stopSizer = new wxStaticBoxSizer(stopBox, wxVERTICAL);
  auto *stopGrid = new wxFlexGridSizer(1, 8, 10, 10);

  stopHourCtrl = new wxTextCtrl(this, wxID_ANY, "0");
  stopMinCtrl = new wxTextCtrl(this, wxID_ANY, "2");
  stopSecCtrl = new wxTextCtrl(this, wxID_ANY, "0");
  stopMsCtrl = new wxTextCtrl(this, wxID_ANY, "0");

  auto *lblStopHour = new wxStaticText(this, wxID_ANY, "hours");
  auto *lblStopMin = new wxStaticText(this, wxID_ANY, "mins");
  auto *lblStopSec = new wxStaticText(this, wxID_ANY, "secs");
  auto *lblStopMs = new wxStaticText(this, wxID_ANY, "milliseconds");

  stopHourCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  stopMinCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  stopSecCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  stopMsCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));

  stopGrid->Add(stopHourCtrl);
  stopGrid->Add(lblStopHour, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  stopGrid->Add(stopMinCtrl, 1, wxEXPAND | wxRIGHT, 2);
  stopGrid->Add(lblStopMin, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  stopGrid->Add(stopSecCtrl, 1, wxEXPAND | wxRIGHT, 2);
  stopGrid->Add(lblStopSec, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  stopGrid->Add(stopMsCtrl, 1, wxEXPAND | wxRIGHT, 2);
  stopGrid->Add(lblStopMs, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);

  stopGrid->AddGrowableCol(0, 1);
  stopGrid->AddGrowableCol(2, 1);
  stopGrid->AddGrowableCol(4, 1);
  stopGrid->AddGrowableCol(6, 1);

  stopSizer->Add(stopGrid, 0, wxALL | wxEXPAND, 8);
  this->SetSizer(stopSizer);
}

long EmergencyStopPanel::GetHours() const
{
  long val = 0;
  stopHourCtrl->GetValue().ToLong(&val);
  return val;
}
long EmergencyStopPanel::GetMinutes() const
{
  long val = 0;
  stopMinCtrl->GetValue().ToLong(&val);
  return val;
}
long EmergencyStopPanel::GetSeconds() const
{
  long val = 0;
  stopSecCtrl->GetValue().ToLong(&val);
  return val;
}
long EmergencyStopPanel::GetMilliseconds() const
{
  long val = 0;
  stopMsCtrl->GetValue().ToLong(&val);
  return val;
}
long EmergencyStopPanel::GetTotalMilliseconds() const
{
  return GetHours() * 3600000 + GetMinutes() * 60000 + GetSeconds() * 1000 + GetMilliseconds();
}
void EmergencyStopPanel::SetHours(long val)
{
  stopHourCtrl->SetValue(wxString::Format("%ld", val));
}
void EmergencyStopPanel::SetMinutes(long val)
{
  stopMinCtrl->SetValue(wxString::Format("%ld", val));
}
void EmergencyStopPanel::SetSeconds(long val)
{
  stopSecCtrl->SetValue(wxString::Format("%ld", val));
}
void EmergencyStopPanel::SetMilliseconds(long val)
{
  stopMsCtrl->SetValue(wxString::Format("%ld", val));
}
