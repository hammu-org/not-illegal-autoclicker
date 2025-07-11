#include <wx/wx.h>
#include <wx/event.h>
#include "move.hpp"

class MyFrame : public wxFrame
{
public:
  enum
  {
    ID_HOTKEY_F12 = wxID_HIGHEST + 1
  };
  MyFrame();
  void OnStartMoveLoop(wxCommandEvent &);
  void OnStopMoveLoop(wxCommandEvent &);
  void OnMoveTimer(wxTimerEvent &);
  void OnClick(wxCommandEvent &);
  void performClickLoop(long interval);
  void OnF12Hotkey(wxKeyEvent &);
  void OnClose(wxCloseEvent &event);

private:
  wxTextCtrl *startXCtrl, *startYCtrl, *endXCtrl, *endYCtrl;
  wxTextCtrl *intervalMinCtrl, *intervalSecCtrl, *intervalMsCtrl;
  wxStaticText *moveStatusLabel;
  wxTimer moveTimer;
  bool isMoving = false;
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Autoclicker GUI", wxDefaultPosition, wxSize(500, 500)), moveTimer(this)
{
  auto *panel = new wxPanel(this);
  auto *mainSizer = new wxBoxSizer(wxVERTICAL);

  startXCtrl = new wxTextCtrl(panel, wxID_ANY);
  startYCtrl = new wxTextCtrl(panel, wxID_ANY);
  endXCtrl = new wxTextCtrl(panel, wxID_ANY);
  endYCtrl = new wxTextCtrl(panel, wxID_ANY);
  intervalMinCtrl = new wxTextCtrl(panel, wxID_ANY);
  intervalSecCtrl = new wxTextCtrl(panel, wxID_ANY);
  intervalMsCtrl = new wxTextCtrl(panel, wxID_ANY);

  wxFont fontBold(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

  // Group: Mouse Movement (top)
  auto *moveBox = new wxStaticBox(panel, wxID_ANY, "Mouse Movement");
  auto *moveSizer = new wxStaticBoxSizer(moveBox, wxVERTICAL);
  auto *moveGrid = new wxFlexGridSizer(2, 4, 12, 12); // 2 rows, 4 cols, more spacing
  auto *lblStartX = new wxStaticText(panel, wxID_ANY, "Start X:");
  lblStartX->SetFont(fontBold);
  auto *lblStartY = new wxStaticText(panel, wxID_ANY, "Start Y:");
  lblStartY->SetFont(fontBold);
  auto *lblEndX = new wxStaticText(panel, wxID_ANY, "End X:");
  lblEndX->SetFont(fontBold);
  auto *lblEndY = new wxStaticText(panel, wxID_ANY, "End Y:");
  lblEndY->SetFont(fontBold);
  moveGrid->Add(lblStartX, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
  moveGrid->Add(startXCtrl, 1, wxEXPAND | wxRIGHT, 12);
  moveGrid->Add(lblEndX, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
  moveGrid->Add(endXCtrl, 1, wxEXPAND);
  moveGrid->Add(lblStartY, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
  moveGrid->Add(startYCtrl, 1, wxEXPAND | wxRIGHT, 12);
  moveGrid->Add(lblEndY, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
  moveGrid->Add(endYCtrl, 1, wxEXPAND);
  moveGrid->AddGrowableCol(1);
  moveGrid->AddGrowableCol(3);
  moveSizer->Add(moveGrid, 1, wxALL | wxEXPAND, 12);
  moveStatusLabel = new wxStaticText(panel, wxID_ANY, "Status: Idle");
  wxFont statusFont = fontBold;
  statusFont.SetPointSize(11);
  moveStatusLabel->SetFont(statusFont);
  moveSizer->Add(moveStatusLabel, 0, wxALL | wxEXPAND, 6);
  auto *startMoveBtn = new wxButton(panel, wxID_ANY, "Start Movement");
  startMoveBtn->SetMinSize(wxSize(0, 40));
  moveSizer->Add(startMoveBtn, 0, wxALL | wxEXPAND, 10);
  auto *stopMoveBtn = new wxButton(panel, wxID_ANY, "Stop Movement");
  stopMoveBtn->SetMinSize(wxSize(0, 40));
  moveSizer->Add(stopMoveBtn, 0, wxALL | wxEXPAND, 10);
  mainSizer->Add(moveSizer, 0, wxALL | wxEXPAND, 16);

  // Group: Click Interval (bottom)
  auto *intervalBox = new wxStaticBox(panel, wxID_ANY, "Click Interval");
  auto *intervalSizer = new wxStaticBoxSizer(intervalBox, wxVERTICAL);
  auto *intervalGrid = new wxFlexGridSizer(1, 6, 10, 10); // 1 row, 6 cols
  auto *lblMin = new wxStaticText(panel, wxID_ANY, "Min:");
  lblMin->SetFont(fontBold);
  auto *lblSec = new wxStaticText(panel, wxID_ANY, "Sec:");
  lblSec->SetFont(fontBold);
  auto *lblMs = new wxStaticText(panel, wxID_ANY, "Ms:");
  lblMs->SetFont(fontBold);
  intervalGrid->Add(lblMin, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  intervalGrid->Add(intervalMinCtrl, 1, wxEXPAND | wxRIGHT, 8);
  intervalGrid->Add(lblSec, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  intervalGrid->Add(intervalSecCtrl, 1, wxEXPAND | wxRIGHT, 8);
  intervalGrid->Add(lblMs, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  intervalGrid->Add(intervalMsCtrl, 1, wxEXPAND);
  intervalGrid->AddGrowableCol(1, 1);
  intervalGrid->AddGrowableCol(3, 1);
  intervalGrid->AddGrowableCol(5, 1);
  intervalSizer->Add(intervalGrid, 0, wxALL | wxEXPAND, 12);
  auto *clickBtn = new wxButton(panel, wxID_ANY, "Start Clicking");
  clickBtn->SetMinSize(wxSize(0, 40));
  intervalSizer->Add(clickBtn, 0, wxALL | wxEXPAND, 10);
  mainSizer->Add(intervalSizer, 0, wxALL | wxEXPAND, 16);

  panel->SetSizer(mainSizer);

  startMoveBtn->Bind(wxEVT_BUTTON, &MyFrame::OnStartMoveLoop, this);
  stopMoveBtn->Bind(wxEVT_BUTTON, &MyFrame::OnStopMoveLoop, this);
  Bind(wxEVT_TIMER, &MyFrame::OnMoveTimer, this);
  clickBtn->Bind(wxEVT_BUTTON, &MyFrame::OnClick, this);

  // Register F12 as a hotkey
  RegisterHotKey(ID_HOTKEY_F12, wxMOD_NONE, WXK_F12);
  Bind(wxEVT_HOTKEY, &MyFrame::OnF12Hotkey, this);
  Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnClose, this);
}

void MyFrame::OnStartMoveLoop(wxCommandEvent &)
{
  if (!isMoving)
  {
    isMoving = true;
    moveStatusLabel->SetLabel("Status: Movement Started");
    moveTimer.Start(1000); // Move every 1 second (adjust as needed)
  }
}

void MyFrame::OnStopMoveLoop(wxCommandEvent &)
{
  if (isMoving)
  {
    isMoving = false;
    moveStatusLabel->SetLabel("Status: Idle");
    moveTimer.Stop();
  }
}

void MyFrame::OnMoveTimer(wxTimerEvent &)
{
  if (!isMoving)
    return;
  long startX, startY, endX, endY;
  startXCtrl->GetValue().ToLong(&startX);
  startYCtrl->GetValue().ToLong(&startY);
  endXCtrl->GetValue().ToLong(&endX);
  endYCtrl->GetValue().ToLong(&endY);
  moveMouseSmooth(static_cast<int>(startX), static_cast<int>(startY), static_cast<int>(endX), static_cast<int>(endY));
}

void MyFrame::OnClick(wxCommandEvent &)
{
  long min = 0, sec = 0, ms = 0;
  intervalMinCtrl->GetValue().ToLong(&min);
  intervalSecCtrl->GetValue().ToLong(&sec);
  intervalMsCtrl->GetValue().ToLong(&ms);
  long interval = min * 60000 + sec * 1000 + ms;
  performClickLoop(interval);
}

void MyFrame::performClickLoop(long interval)
{
  // Perform 10 clicks at the current mouse position, with the specified interval
  for (int i = 0; i < 10; ++i)
  {
    leftClick();
    wxMilliSleep(interval);
  }
}

void MyFrame::OnF12Hotkey(wxKeyEvent &)
{
  // Toggle movement loop
  wxCommandEvent dummyEvt;
  if (isMoving)
    OnStopMoveLoop(dummyEvt);
  else
    OnStartMoveLoop(dummyEvt);
}

void MyFrame::OnClose(wxCloseEvent &event)
{
  UnregisterHotKey(MyFrame::ID_HOTKEY_F12);
  event.Skip();
}

class MyApp : public wxApp
{
public:
  bool OnInit() override
  {
    auto *frame = new MyFrame();
    frame->Show();
    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
