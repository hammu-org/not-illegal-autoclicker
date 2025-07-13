#include "gui.hpp"

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Not Illegal Autoclicker", wxDefaultPosition, wxSize(400, 600))
{
  SetMinSize(wxSize(400, 600));
  auto *panel = new wxPanel(this);
  auto *mainSizer = new wxBoxSizer(wxVERTICAL);

  intervalHourCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  intervalMinCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  intervalSecCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  intervalMsCtrl = new wxTextCtrl(panel, wxID_ANY, "0");

  // Emergency stop controls (default 2 minutes)
  stopHourCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  stopMinCtrl = new wxTextCtrl(panel, wxID_ANY, "2");
  stopSecCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  stopMsCtrl = new wxTextCtrl(panel, wxID_ANY, "0");

  wxFont fontBold(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

  // --- Emergency Stop Section ---
  auto *stopBox = new wxStaticBox(panel, wxID_ANY, "Emergency Stop (Max Duration)");
  auto *stopSizer = new wxStaticBoxSizer(stopBox, wxVERTICAL);
  auto *stopGrid = new wxFlexGridSizer(1, 8, 10, 10);
  auto *lblStopHour = new wxStaticText(panel, wxID_ANY, "hours");
  auto *lblStopMin = new wxStaticText(panel, wxID_ANY, "mins");
  auto *lblStopSec = new wxStaticText(panel, wxID_ANY, "secs");
  auto *lblStopMs = new wxStaticText(panel, wxID_ANY, "milliseconds");
  // Set minimum width for controls instead of wxEXPAND
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
  stopSizer->Add(stopGrid, 0, wxALL | wxEXPAND, 8);
  stopGrid->AddGrowableCol(0, 1);
  stopGrid->AddGrowableCol(2, 1);
  stopGrid->AddGrowableCol(4, 1);
  stopGrid->AddGrowableCol(6, 1);

  mainSizer->Add(stopSizer, 0, wxALL | wxEXPAND, 16);
  // --- End of Emergency Stop Section ---

  // --- Click Interval Section ---
  auto *intervalBox = new wxStaticBox(panel, wxID_ANY, "Click Interval");
  auto *intervalSizer = new wxStaticBoxSizer(intervalBox, wxVERTICAL);

  // Interval controls
  auto *intervalGrid = new wxFlexGridSizer(1, 8, 10, 10);
  auto *lblHour = new wxStaticText(panel, wxID_ANY, "hours");
  auto *lblMin = new wxStaticText(panel, wxID_ANY, "mins");
  auto *lblSec = new wxStaticText(panel, wxID_ANY, "secs");
  auto *lblMs = new wxStaticText(panel, wxID_ANY, "milliseconds");

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
  intervalSizer->Add(intervalGrid, 0, wxALL | wxEXPAND, 2);

  // Make the first input field column growable
  intervalGrid->AddGrowableCol(0, 1);
  intervalGrid->AddGrowableCol(2, 1);
  intervalGrid->AddGrowableCol(4, 1);
  intervalGrid->AddGrowableCol(6, 1);
  // --- End of Click Interval Section ---

  // --- Move the offset slider block here ---
  auto *offsetSizer = new wxBoxSizer(wxHORIZONTAL);
  offsetLabel = new wxStaticText(panel, wxID_ANY, "Random Offset +- 200ms");
  offsetSlider = new wxSlider(panel, wxID_ANY, 200, 0, 20000, wxDefaultPosition, wxSize(120, -1));

  // Add tooltips
  offsetLabel->SetToolTip(
      "Randomly adds or subtracts up to this ms to each click interval.\n"
      "e.g. 200ms = up to 200ms shorter or longer than your click interval\n"
      "(a total range of 400ms)");

  offsetSizer->Add(offsetLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
  offsetSizer->Add(offsetSlider, 1, wxALIGN_CENTER_VERTICAL);
  intervalSizer->Add(offsetSizer, 0, wxALL | wxEXPAND, 8);
  offsetSlider->Bind(wxEVT_SLIDER, [this](wxCommandEvent &evt)
                     {
    randomOffsetMs = offsetSlider->GetValue();
    offsetLabel->SetLabel(wxString::Format("Random Offset +- %dms", randomOffsetMs)); });
  // --- End of offset slider block ---

  // Divider before original position
  auto *origDivider = new wxStaticLine(panel, wxID_ANY);
  intervalSizer->Add(origDivider, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 8);

  auto *origTitle = new wxStaticText(panel, wxID_ANY, "TODO: Original");
  origTitle->SetToolTip(
      "Currently unused\n"
      "Returns back to original cursor right now.");
  intervalSizer->Add(origTitle, 0, wxLEFT, 8);
  auto *origGrid = new wxFlexGridSizer(2, 4, 10, 10);
  auto *lblOriginalX = new wxStaticText(panel, wxID_ANY, "X");
  originalXCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  auto *lblOriginalY = new wxStaticText(panel, wxID_ANY, "Y");
  originalYCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  originalXCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  originalYCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  origGrid->Add(lblOriginalX, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  origGrid->Add(originalXCtrl, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
  origGrid->Add(lblOriginalY, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  origGrid->Add(originalYCtrl, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
  intervalSizer->Add(origGrid, 0, wxALL | wxEXPAND, 8);

  // Target controls
  auto *targetTitle = new wxStaticText(panel, wxID_ANY, "Target");
  intervalSizer->Add(targetTitle, 0, wxLEFT, 8);
  auto *targetGrid = new wxFlexGridSizer(1, 4, 10, 10);
  auto *lblTargetX = new wxStaticText(panel, wxID_ANY, "X");
  targetXCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  auto *lblTargetY = new wxStaticText(panel, wxID_ANY, "Y");
  targetYCtrl = new wxTextCtrl(panel, wxID_ANY, "0");
  targetXCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  targetYCtrl->SetMinSize(wxSize(MIN_WIDTH_COL, -1));
  targetGrid->Add(lblTargetX, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  targetGrid->Add(targetXCtrl, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
  targetGrid->Add(lblTargetY, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
  targetGrid->Add(targetYCtrl, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
  intervalSizer->Add(targetGrid, 0, wxALL | wxEXPAND, 8);
  auto *cursorPosTitle = new wxStaticText(panel, wxID_ANY, "Current Cursor Position");
  cursorPosLabel = new wxStaticText(panel, wxID_ANY, "X: --  Y: --");
  intervalSizer->Add(cursorPosTitle, 0, wxALL | wxEXPAND, 8);
  intervalSizer->Add(cursorPosLabel, 0, wxALL | wxEXPAND, 8);

  // Add return click checkbox
  returnClickCheckBox = new wxCheckBox(panel, wxID_ANY, "Enable return click (click at original position after target)");
  returnClickCheckBox->SetValue(true); // Default enabled
  intervalSizer->Add(returnClickCheckBox, 0, wxALL, 8);

  // Divider before target position
  auto *divider = new wxStaticLine(panel, wxID_ANY);
  intervalSizer->Add(divider, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 8);

  clickStatusLabel = new wxStaticText(panel, wxID_ANY, "Click Status: Idle");
  wxFont clickStatusFont = fontBold;
  clickStatusFont.SetPointSize(11);
  clickStatusLabel->SetFont(clickStatusFont);
  intervalSizer->Add(clickStatusLabel, 0, wxALL | wxEXPAND, 6);

  // Show correct hotkey label depending on platform
#ifdef __WXMSW__
  auto *clickHotkeyLabel = new wxStaticText(panel, wxID_ANY, "Hotkey: F13 (Windows) to Start/Stop Clicking");
#else
  auto *clickHotkeyLabel = new wxStaticText(panel, wxID_ANY, "Hotkey: F12 (Mac) to Start/Stop Clicking");
#endif
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
  // --- Add Debug Button ---
  auto *debugBtn = new wxButton(panel, wxID_ANY, "System Info");
  debugBtn->SetMinSize(wxSize(0, 40));
  mainSizer->Add(debugBtn, 0, wxALL | wxEXPAND, 8);
  debugBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent &)
                 {
    wxString info;
    info << "wxWidgets version: " << wxVERSION_STRING << "\n";
    info << "Build: " << wxGetOsDescription() << "\n";
    info << "Build date: " << __DATE__ << " " << __TIME__ << "\n";
    info << "Working dir: " << wxGetCwd() << "\n";
    info << "User: " << wxGetUserName() << "\n";
    info << "Computer: " << wxGetHostName() << "\n";
    // Add your own screen bounds info
    ScreenRect bounds = getScreenBounds();
    info << wxString::Format("Screen bounds: left=%d top=%d right=%d bottom=%d\n", bounds.left, bounds.top, bounds.right, bounds.bottom);
    wxMessageBox(info, "System Info", wxOK | wxICON_INFORMATION, this); });

  /// Set the main sizer for the panel
  panel->SetSizer(mainSizer);
  // panel->SetMaxSize(wxSize(420, -1));

  // Register F13 on Windows, F12 on Mac/others for start/stop clicking
#ifdef __WXMSW__
  // On Windows, use VK_F13 (0x7C) and MOD_NOREPEAT
  RegisterHotKey(ID_HOTKEY_F12, MOD_NOREPEAT, 0x7C);
#else
  // On Mac and others, use WXK_F12 and no modifier
  RegisterHotKey(ID_HOTKEY_F12, wxMOD_NONE, WXK_F12);
#endif
  Bind(wxEVT_HOTKEY, &MyFrame::OnHotkey, this, ID_HOTKEY_F12);
  Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnClose, this);

  // Bind mouse left down event to update cursor position label
  panel->Bind(wxEVT_LEFT_DOWN, &MyFrame::OnMouseLeftDown, this);

  intervalSizer->SetMinSize(wxSize(0, 0)); // Let it shrink
  stopSizer->SetMinSize(wxSize(0, 0));     // Let it shrink
}

void MyFrame::OnClick(wxCommandEvent &)
{
  // Get and display cursor position on click
  wxPoint pos = wxGetMousePosition();
  cursorPosLabel->SetLabel(wxString::Format("X: %d  Y: %d", pos.x, pos.y));
  StartClickLoop();
}

void MyFrame::OnHotkey(wxKeyEvent &)
{
  // Get and display cursor position on hotkey
  wxPoint pos = wxGetMousePosition();
  cursorPosLabel->SetLabel(wxString::Format("X: %d  Y: %d", pos.x, pos.y));
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
      long hr = 0, min = 0, sec = 0, ms = 0;
      intervalHourCtrl->GetValue().ToLong(&hr);
      intervalMinCtrl->GetValue().ToLong(&min);
      intervalSecCtrl->GetValue().ToLong(&sec);
      intervalMsCtrl->GetValue().ToLong(&ms);
      long baseInterval = hr * 3600000 + min * 60000 + sec * 1000 + ms;
      if (baseInterval < 1) baseInterval = 1;

      // Emergency stop duration
      long stopHr = 0, stopMin = 2, stopSec = 0, stopMs = 0;
      stopHourCtrl->GetValue().ToLong(&stopHr);
      stopMinCtrl->GetValue().ToLong(&stopMin);
      stopSecCtrl->GetValue().ToLong(&stopSec);
      stopMsCtrl->GetValue().ToLong(&stopMs);
      long stopDuration = stopHr * 3600000 + stopMin * 60000 + stopSec * 1000 + stopMs;
      if (stopDuration < 1) stopDuration = 120000; // fallback to 2 min
      auto startTime = std::chrono::steady_clock::now();

      // Setup randomizer for 7user-selected offset in ms
      std::random_device rd;
      std::mt19937 gen(rd());
      int offsetRange = randomOffsetMs;
      std::uniform_int_distribution<int> dist(-offsetRange, offsetRange);

      while (isClicking)
      {
        // Emergency stop check
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
        if (elapsed >= stopDuration) {
          isClicking = false;
          break;
        }
        long targetX = 0, targetY = 0;
        targetXCtrl->GetValue().ToLong(&targetX);
        targetYCtrl->GetValue().ToLong(&targetY);

        // Get current mouse position
        MyPoint current = getCurrentMousePos();
        int origX = current.x;
        int origY = current.y;
        // int origX = randomOffset(current.x, 5);
        // int origY = randomOffset(current.y, 10);
        // Clamp to screen
        clampToScreen(origX, origY);

        // Move from original to target, aborts if isClicking is set false
        moveMouseSmooth(static_cast<int>(origX), static_cast<int>(origY), static_cast<int>(targetX), static_cast<int>(targetY), &isClicking);

        // Ensure mouse is at target before clicking
        wxTheApp->CallAfter([this, targetX, targetY]() {
          cursorPosLabel->SetLabel(wxString::Format("X: %ld  Y: %ld", targetX, targetY));
        });
        wxMilliSleep(15);
        leftClick();

        moveMouseSmoothReturn(static_cast<int>(targetX), static_cast<int>(targetY), static_cast<int>(origX), static_cast<int>(origY), &isClicking);
        if (returnClickCheckBox->IsChecked()) {
          wxMilliSleep(15);
          leftClick();
        }
        int randomized = baseInterval + dist(gen);
        if (randomized < 1) randomized = 1;
        wxMilliSleep(randomized);


        // Optionally, move back to original (if you want a round-trip loop)
        // moveMouseSmooth(static_cast<int>(targetX), static_cast<int>(targetY), static_cast<int>(origX), static_cast<int>(origY), &isClicking);
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

void MyFrame::OnClose(wxCloseEvent &event)
{
  UnregisterHotKey(MyFrame::ID_HOTKEY_F12);
  event.Skip();
}

void MyFrame::OnMouseLeftDown(wxMouseEvent &event)
{
  wxPoint pos = wxGetMousePosition();
  cursorPosLabel->SetLabel(wxString::Format("X: %d  Y: %d", pos.x, pos.y));
  event.Skip();
}
