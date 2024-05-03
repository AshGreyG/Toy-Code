#pragma once
#ifndef SNAKE_CONTROL_H
#define SNAKE_CONTROL_H

#include <wx/wx.h>

int COUNT = 0;

enum SnakeControl {
    SNAKE_EASY      = 1000,
    SNAKE_MEDIUM    = 1001,
    SNAKE_HARD      = 1002,
    SNAKE_TIMER     = 1003,
    SNAKE_LEFT      = 1004,
    SNAKE_RIGHT     = 1005,
    SNAKE_UP        = 1006,
    SNAKE_DOWN      = 1007
};

enum GameDifficulty {
    easy    = 10,
    medium  = 20,
    hard    = 30
};

enum BlockType {
    emptyBlock      = 1,
    snakeBlock      = 2,
    computerBlock   = 3,
    barrierBlock    = 4,
    appleBlock      = 5
};

enum SnakeMotion {
    left  = 1,
    right = 2,
    up    = 4,
    down  = 5
};

struct Block {
    BlockType type;
    wxRect rect;
};

struct SnakeNode {
    int x;
    int y;
    SnakeMotion motion;
    struct SnakeNode* next;
};

struct Apple {
    int x;
    int y;
    bool isEaten;
};

class Snake {
    friend class SnakeGamePanel;
    private:
        SnakeNode* tail;
        SnakeNode* head;
    public:
        bool isDead = false;
        void updateBody();
        void eatApple();
        void changeHeadMotion(SnakeMotion m);
        Snake(int xx, int yy, SnakeMotion m);
        Snake() = default;
        virtual ~Snake() = default;
};

class SnakeComputer : public Snake {
    public:
        void actionControl();
        SnakeComputer(int xx, int yy, SnakeMotion m);
        SnakeComputer() = default;
};

class SnakeGamePanel;
class SnakeMainFrame;

class SnakeGamePanel : public wxPanel {
    private:
        GameDifficulty difficulty;
        int computersNum;
        Block blockGroup[32][42];
        SnakeComputer* computerSnake = nullptr;
        Snake player;
        Apple targetApple;

        wxButton*       easyButton    = new wxButton;
        wxButton*       mediumButton  = new wxButton;
        wxButton*       hardButton    = new wxButton;
        wxTimer*        timer         = new wxTimer(this, SNAKE_TIMER);
        SnakeMainFrame* mainFrame;

        void generateMap(int diff);
        void OnChooseEasy(wxCommandEvent& event);
        void OnChooseMedium(wxCommandEvent& event);
        void OnChooseHard(wxCommandEvent& event);
        void OnTimerUpdated(wxTimerEvent& event);
        wxDECLARE_EVENT_TABLE();
    public:
        void getMainframe(SnakeMainFrame* m) { mainFrame = m; };
        void controlPlayerSnake(SnakeMotion m) { player.changeHeadMotion(m); };
        SnakeGamePanel(wxWindow* parent);
        ~SnakeGamePanel() = default;
};

class SnakeMainFrame : public wxFrame {
    private:
        SnakeGamePanel* gamePanel   = new SnakeGamePanel(this);
        wxBitmapButton* leftButton  = new wxBitmapButton;
        wxBitmapButton* rightButton = new wxBitmapButton;
        wxBitmapButton* upButton    = new wxBitmapButton;
        wxBitmapButton* downButton  = new wxBitmapButton;

        void OnPressLeft(wxCommandEvent& event);
        void OnPressRight(wxCommandEvent& event);
        void OnPressUp(wxCommandEvent& event);
        void OnPressDown(wxCommandEvent& event);
        wxDECLARE_EVENT_TABLE();
    public:
        void disableMotionButtons();
        void enableMotionButtons();
        SnakeMainFrame(const wxString& title);
        ~SnakeMainFrame() = default;
};

#endif
