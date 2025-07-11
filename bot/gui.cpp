#include <wx/wx.h>
#include <wx/event.h>
#include "move.hpp"

class MyFrame : public wxFrame
{
public:
  enum
  {
    ID_HOTKEY_F12 = wxID_HIGHEST + 1,
    ID_HOTKEY_F10
  };
  MyFrame();
  void OnStartMoveLoop(wxCommandEvent &);
  void OnStopMoveLoop(wxCommandEvent &);
  void OnMoveTimer(wxTimerEvent &);
  void OnClick(wxCommandEvent &);
  void OnF12Hotkey(wxKeyEvent &);
  void OnF10Hotkey(wxKeyEvent &);
  void OnClose(wxCloseEvent &event);
  void StartClickLoop();
  void StopClickLoop();

private:
  wxTextCtrl *startXCtrl, *startYCtrl, *endXCtrl, *endYCtrl;
  wxTextCtrl *intervalMinCtrl, *intervalSecCtrl, *intervalMsCtrl;
  wxStaticText *moveStatusLabel;
  wxStaticText *clickStatusLabel;
  wxTimer moveTimer;
  bool isMoving = false;
  bool isClicking = false;
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Autoclicker GUI", wxDefaultPosition, wxSize(500, 500)), moveTimer(this)
{
  auto *panel = new wxPanel(this);
  auto *mainSizer = new wxBoxSizer(wxVERTICAL);

  startXCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  startYCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  endXCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  endYCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  intervalMinCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  intervalSecCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  intervalMsCtrl = new wxTextCtrl(panel, wxID_ANY, "0");

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
  auto *moveHotkeyLabel = new wxStaticText(panel, wxID_ANY, "Hotkey: F12 to Start/Stop Movement");
  wxFont moveHotkeyFont = fontBold;
  moveHotkeyFont.SetPointSize(9);
  moveHotkeyLabel->SetFont(moveHotkeyFont);
  moveSizer->Add(moveHotkeyLabel, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
  mainSizer->Add(moveSizer, 0, wxALL | wxEXPAND, 16);

  // Group: Click Interval (bottom)
  auto *intervalBox = new wxStaticBox(panel, wxID_ANY, "Click Interval");
  auto *intervalSizer = new wxStaticBoxSizer(intervalBox, wxVERTICAL);
  auto *intervalGrid = new wxFlexGridSizer(1, 6, 10, 10);
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
  clickStatusLabel = new wxStaticText(panel, wxID_ANY, "Click Status: Idle");
  wxFont clickStatusFont = fontBold;
  clickStatusFont.SetPointSize(11);
  clickStatusLabel->SetFont(clickStatusFont);
  intervalSizer->Add(clickStatusLabel, 0, wxALL | wxEXPAND, 6);
  auto *clickHotkeyLabel = new wxStaticText(panel, wxID_ANY, "Hotkey: F10 to Start/Stop Clicking");
  wxFont clickHotkeyFont = fontBold;
  clickHotkeyFont.SetPointSize(9);
  clickHotkeyLabel->SetFont(clickHotkeyFont);
  intervalSizer->Add(clickHotkeyLabel, 0, wxLEFT | wxRIGHT | wxBOTTOM, 6);
  mainSizer->Add(intervalSizer, 0, wxALL | wxEXPAND, 16);

  auto *quitBtn = new wxButton(panel, wxID_EXIT, "Quit");
  quitBtn->SetMinSize(wxSize(0, 40));
  mainSizer->Add(quitBtn, 0, wxALL | wxEXPAND, 16);
  quitBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent &)
                { Close(true); });

  panel->SetSizer(mainSizer);

  Bind(wxEVT_TIMER, &MyFrame::OnMoveTimer, this);

  // Register F12 as a hotkey
  RegisterHotKey(ID_HOTKEY_F12, wxMOD_NONE, WXK_F12);
  RegisterHotKey(ID_HOTKEY_F10, wxMOD_NONE, WXK_F10);
  Bind(wxEVT_HOTKEY, &MyFrame::OnF12Hotkey, this, ID_HOTKEY_F12);
  Bind(wxEVT_HOTKEY, &MyFrame::OnF10Hotkey, this, ID_HOTKEY_F10);
  Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnClose, this);
}

void MyFrame::OnStartMoveLoop(wxCommandEvent &)
{
  if (!isMoving)
  {
    isMoving = true;
    moveStatusLabel->SetLabel("Status: Movement Started");
    moveTimer.Start(1000);
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
  StartClickLoop();
}

// performClickLoop is now handled in StartClickLoop
void MyFrame::OnF10Hotkey(wxKeyEvent &)
{
  if (isClicking)
    StopClickLoop();
  else
    StartClickLoop();
}

void MyFrame::StartClickLoop()
{
  if (!isClicking)
  {
    isClicking = true;
    clickStatusLabel->SetLabel("Click Status: Clicking...");
    // Start click loop in a new thread to avoid blocking UI
    std::thread([this]()
                {
      long min = 0, sec = 0, ms = 0;
      intervalMinCtrl->GetValue().ToLong(&min);
      intervalSecCtrl->GetValue().ToLong(&sec);
      intervalMsCtrl->GetValue().ToLong(&ms);
      long interval = min * 60000 + sec * 1000 + ms;
      while (isClicking)
      {
        leftClick();
        wxMilliSleep(interval);
      }
      wxTheApp->CallAfter([this]() {
        isClicking = false;
        clickStatusLabel->SetLabel("Click Status: Idle");
      }); })
        .detach();
  }
}

void MyFrame::StopClickLoop()
{
  isClicking = false;
  clickStatusLabel->SetLabel("Click Status: Idle");
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
  UnregisterHotKey(MyFrame::ID_HOTKEY_F10);
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
