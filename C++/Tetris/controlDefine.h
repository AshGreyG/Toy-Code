////////////////////////////////////////////////
//    Author : AshGrey
//    Time   : 2024.1.27
//    Blog   : https://www.ashgrey-sagiri.top
////////////////////////////////////////////////

#pragma once

#ifndef TETRIS_CONTROL_H
#define TETRIS_CONTROL_H

#include <wx/wx.h>
#include <wx/dcclient.h>

int SPEED = 1;
int COUNT = 0;
int SCORE = 0;

enum TetrisControl {
    TETRIS_GAMEPANEL = 1000,
    TETRIS_START     = 1001,
    TETRIS_TIMER     = 1002,
    TETRIS_LEFT      = 1003,
    TETRIS_RIGHT     = 1004,
    TETRIS_UP        = 1005,
    TETRIS_DOWN      = 1006,
    TETRIS_RESTART   = 1007,
    TETRIS_QUIT      = 1008,
    TETRIS_PAUSE     = 1009
};

struct Block {
    wxRect rect;
    int type;
};

struct Point {
    int x;
    int y;
};

class BlockModule {
    friend class TetrisGamePanel;
    friend class TetrisMainFrame;
    private:
        int type;
        bool isBlock[4][4];
        int x;
        int y;
    public:
        BlockModule() = default;
        BlockModule(const int t);
        BlockModule(const BlockModule& bm);
        BlockModule& operator = (const BlockModule& bm);
        ~BlockModule() = default;
};

class TetrisGamePanel;
class TetrisMainFrame;

class TetrisGamePanel : public wxPanel {
    private:
        BlockModule*    currentBlock    = new BlockModule(-1);
        BlockModule*    nextBlock       = new BlockModule(-1);
        wxTimer*        timer           = new wxTimer(this, TETRIS_TIMER);
        wxButton*       startButton     = new wxButton;
        wxButton*       restartButton   = new wxButton;
        wxButton*       quitButton      = new wxButton;

        TetrisMainFrame* mainFrame;
        Block blockGroup[24][12];
        bool firstGenerate = true;
        void OnStartGame(wxCommandEvent& event);
        void OnTimerUpdated(wxTimerEvent& event);
        void OnRestartGame(wxCommandEvent& event);
        void OnQuit(wxCommandEvent& event);
        wxDECLARE_EVENT_TABLE();
    public:
        TetrisGamePanel(wxWindow* parent);
        ~TetrisGamePanel() = default;

        void GenerateBlock();
        void ClearBlock();
        bool LoseCheck();
        bool DownCheck();
        bool LeftCheck();
        bool RightCheck();
        bool RotateCheck(int t);
        BlockModule& currentBlockCallback() { return *currentBlock; };
        BlockModule& nextBlockCallback() { return *nextBlock; };
        wxTimer& timerCallback() { return *timer; };
        void getMainFrame(TetrisMainFrame* frame) { mainFrame = frame; };
};

class TetrisMainFrame : public wxFrame {
    private:
        wxBoxSizer*       mainSizer        = new wxBoxSizer(wxHORIZONTAL);
        TetrisGamePanel*  gamePanel        = new TetrisGamePanel(this);
        wxPanel*          gameBarPanel     = new wxPanel;
        wxBoxSizer*       gameBarSizer     = new wxBoxSizer(wxVERTICAL);
        wxBitmapButton*   leftButton       = new wxBitmapButton;
        wxBitmapButton*   rightButton      = new wxBitmapButton;
        wxBitmapButton*   upButton         = new wxBitmapButton;
        wxBitmapButton*   downButton       = new wxBitmapButton;
        wxStaticText*     scoreShow        = new wxStaticText;
        wxPanel*          nextBlockShow    = new wxPanel;
        wxButton*         pauseButton      = new wxButton;
        wxButton*         quitButton       = new wxButton;
        void OnLeftMove(wxCommandEvent& event);
        void OnRightMove(wxCommandEvent& event);
        void OnDownSpeed(wxCommandEvent& event);
        void OnUpRotate(wxCommandEvent& event);
        void OnPause(wxCommandEvent& event);
        void OnQuit(wxCommandEvent& event);
        
        wxDECLARE_EVENT_TABLE();
    public:
        TetrisMainFrame(const wxString& title);
        ~TetrisMainFrame() = default;
        void scoreShowUpdate();
        void nextBlockUpdate();
};

#endif // !TETRIS_CONTROL_H