#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "controlDefine.h"

extern int COUNT;

class SnakeApp : public wxApp {
    public:
        virtual bool OnInit() {
            if (!wxApp::OnInit())
                return false;
            wxInitAllImageHandlers();
            SnakeMainFrame* mainFrame = new SnakeMainFrame(wxT("Snake"));
            (*mainFrame).Show();
            return true;
        };
        std::string SnakeAppName = "Snake";
};
wxIMPLEMENT_APP(SnakeApp);
wxDECLARE_APP(SnakeApp);

// ----------------------------
// Snake
// ----------------------------

inline void Snake::updateBody() {
    if ((*this).isDead)
        return;

    // FUNCTION : Change the node motion

    SnakeNode* pointerA = tail;
    while (pointerA != nullptr) {
        if ((*pointerA).next != nullptr) {
            if ((*pointerA).next->x - (*pointerA).x == 1)
                (*pointerA).motion = right;
            else if ((*pointerA).next->x - (*pointerA).x == -1)
                (*pointerA).motion = left;
            else if ((*pointerA).next->y - (*pointerA).y == -1)
                (*pointerA).motion = up;
            else if ((*pointerA).next->y - (*pointerA).y == 1)
                (*pointerA).motion = down;
        }
        pointerA = (*pointerA).next;
    }

    // FUNCTION : Move the node position

    SnakeNode* pointerB = tail;
    while (pointerB != nullptr) {
        switch ((*pointerB).motion) {
            case left:
                (*pointerB).x--;
                break;
            case right:
                (*pointerB).x++;
                break;
            case up:
                (*pointerB).y--;
                break;
            case down:
                (*pointerB).y++; 
        }
        pointerB = (*pointerB).next;
    }
}

inline void Snake::eatApple() {
    if ((*this).isDead)
        return;
    SnakeNode* newHead = new SnakeNode;
    (*head).next = newHead;
    (*newHead).next = nullptr;
    (*newHead).motion = (*head).motion;
    switch ((*head).motion) {
        case left:
            (*newHead).x = (*head).x - 1;
            (*newHead).y = (*head).y;
            break;
        case right:
            (*newHead).x = (*head).x + 1;
            (*newHead).y = (*head).y;
            break;
        case up:
            (*newHead).x = (*head).x;
            (*newHead).y = (*head).y - 1;
            break;
        case down:
            (*newHead).x = (*head).x;
            (*newHead).y = (*head).y + 1;
            break;
    }
    head = (*head).next;
}

void Snake::changeHeadMotion(SnakeMotion m) {
    if ((*this).isDead)
        return;
    if (abs(m - (*head).motion) == 1) {}
    else {
        (*head).motion = m;
    }
}

Snake::Snake(int xx, int yy, SnakeMotion m) {
    SnakeNode* tempTail = new SnakeNode;
    SnakeNode* tempHead = new SnakeNode;
    (*tempTail).motion = m;
    (*tempTail).next = tempHead;
    (*tempHead).motion = m;
    (*tempHead).next = nullptr;
    (*tempHead).x = xx;
    (*tempHead).y = yy;
    switch (m) {
        case left:
            (*tempTail).x = xx + 1;
            (*tempTail).y = yy;
            break;
        case right:
            (*tempTail).x = xx - 1;
            (*tempTail).y = yy;
            break;
        case up:
            (*tempTail).x = xx;
            (*tempTail).y = yy + 1;
            break;
        case down:
            (*tempTail).x = xx;
            (*tempTail).y = yy - 1;
            break;
    }
    tail = tempTail;
    head = tempHead;
}

// ----------------------------
// SnakeComputer
// ----------------------------



SnakeComputer::SnakeComputer(int xx, int yy, SnakeMotion m)
    : Snake(xx, yy, m) {};

// ----------------------------
// SnakeGamePanel
// ----------------------------

wxBEGIN_EVENT_TABLE(SnakeGamePanel, wxPanel)
    EVT_BUTTON(SNAKE_EASY, SnakeGamePanel::OnChooseEasy)
    EVT_BUTTON(SNAKE_MEDIUM, SnakeGamePanel::OnChooseMedium)
    EVT_BUTTON(SNAKE_HARD, SnakeGamePanel::OnChooseHard)
    EVT_TIMER(SNAKE_TIMER, SnakeGamePanel::OnTimerUpdated)
wxEND_EVENT_TABLE()

inline void SnakeGamePanel::OnChooseEasy(wxCommandEvent& event) {
    difficulty = easy;
    generateMap(difficulty);
}

inline void SnakeGamePanel::OnChooseMedium(wxCommandEvent& event) {
    difficulty = medium;
    generateMap(difficulty);
}

inline void SnakeGamePanel::OnChooseHard(wxCommandEvent& event) {
    difficulty = hard;
    generateMap(difficulty);
}

inline void SnakeGamePanel::generateMap(int diff) {
    (*easyButton).Show(false);
    (*mediumButton).Show(false);
    (*hardButton).Show(false);
    wxClientDC clientdc(this);
    clientdc.SetClippingRegion(wxPoint(0, 0), wxSize(800, 600));
    wxBufferedDC dc(&clientdc);
    dc.SetPen(wxColor(0, 0, 0));

    // FUNCTION : Generate the wall of gamepanel

    for (int i = 0; i <= 41; i++)
        blockGroup[0][i].type = barrierBlock;
    for (int i = 0; i <= 41; i++)
        blockGroup[31][i].type = barrierBlock;
    for (int i = 1; i <= 30; i++)
        blockGroup[i][0].type = barrierBlock;
    for (int i = 1; i <= 30; i++)
        blockGroup[i][41].type = barrierBlock;

    for (int i = 1; i <= 30; i++) {
        for (int j = 1; j <= 40; j++)
            blockGroup[i][j].type = emptyBlock;
    }

    // FUNCTION : Generate the computer players

    switch (diff) {
        case easy:
            computersNum = 1;
            computerSnake = new SnakeComputer[computersNum];
            break;
        case medium:
            computersNum = 2;
            computerSnake = new SnakeComputer[computersNum];
            break;
        case hard:
            computersNum = 3;
            computerSnake = new SnakeComputer[computersNum];
            break;
    }
    srand(time(nullptr));
    for (int i = 1; i <= computersNum; i++) {
        int randomHeadX = rand() % 38 + 2;
        int randomHeadY = rand() % 28 + 2;
        int randomMotion = rand() % 5 + 1;
        while (blockGroup[randomHeadY][randomHeadX].type == computerBlock) {
            randomHeadX = rand() % 38 + 2;
            randomHeadY = rand() % 28 + 2;
        }
        while (randomMotion == 3)
            randomMotion = rand() % 5 + 1;
        computerSnake[i - 1] = SnakeComputer(randomHeadX, randomHeadY, SnakeMotion(randomMotion));
        SnakeNode* pointer = computerSnake[i - 1].tail;
        while (pointer != nullptr) {
            blockGroup[(*pointer).y][(*pointer).x].type = computerBlock;
            pointer = (*pointer).next;
        }
    }

    // FUNCTION : Generate the player

    int randomPlayerHeadX = rand() % 38 + 2;
    int randomPlayerHeadY = rand() % 28 + 2;
    while (blockGroup[randomPlayerHeadY][randomPlayerHeadX].type == computerBlock
        || blockGroup[randomPlayerHeadY][randomPlayerHeadX + 1].type == computerBlock) {
        randomPlayerHeadX = rand() % 38 + 2;
        randomPlayerHeadY = rand() % 28 + 2;
    }
    player = Snake(randomPlayerHeadX, randomPlayerHeadY, left);
    SnakeNode* pointer = player.tail;
    while (pointer != nullptr) {
        blockGroup[(*pointer).y][(*pointer).x].type = snakeBlock;
        pointer = (*pointer).next;
    }

    // FUNCTION : Generate the barriers

    for (int j = 1; j <= int(diff); j++) {
        int randomBarrierX = rand() % 38 + 2;
        int randomBarrierY = rand() % 28 + 2;
        while (blockGroup[randomBarrierY][randomBarrierX].type == snakeBlock
            || blockGroup[randomBarrierY][randomBarrierX].type == barrierBlock
            || blockGroup[randomBarrierY][randomBarrierX].type == computerBlock) {
            randomBarrierX = rand() % 38 + 2;
            randomBarrierY = rand() % 28 + 2;
        }
        blockGroup[randomBarrierY][randomBarrierX].type = barrierBlock;
    }

    // FUNCTION : Generate the apple

    int randomAppleX = rand() % 38 + 2;
    int randomAppleY = rand() % 28 + 2;
    while (blockGroup[randomAppleY][randomAppleX].type == snakeBlock
        || blockGroup[randomAppleY][randomAppleX].type == barrierBlock
        || blockGroup[randomAppleY][randomAppleX].type == computerBlock) {
        randomAppleX = rand() % 38 + 2;
        randomAppleY = rand() % 28 + 2;
    }
    targetApple.x = randomAppleX;
    targetApple.y = randomAppleY;
    targetApple.isEaten = false;
    blockGroup[targetApple.y][targetApple.x].type = appleBlock;

    // FUNCTION : Draw the map using different colors

    for (int i = 1; i <= 30; i++) {
        for (int j = 1; j <= 40; j++) {
            switch (blockGroup[i][j].type) {
                case emptyBlock:
                    dc.SetBrush(wxColor(0, 0, 0));
                    break;
                case snakeBlock:
                    dc.SetBrush(wxColor(91, 158, 232));
                    break;
                case computerBlock:
                    dc.SetBrush(wxColor(172, 132, 46));
                    break;
                case barrierBlock:
                    dc.SetBrush(wxColor(240, 240, 240));
                    break;
                case appleBlock:
                    dc.SetBrush(wxColor(108, 32, 34));
                    break;
            }
            blockGroup[i][j].rect.SetX(20 * (j - 1));
            blockGroup[i][j].rect.SetY(20 * (i - 1));
            blockGroup[i][j].rect.SetWidth(20);
            blockGroup[i][j].rect.SetHeight(20);
            dc.DrawRectangle(blockGroup[i][j].rect);
        }
    }
    (*timer).Start();
    (*mainFrame).enableMotionButtons();
}

inline void SnakeGamePanel::OnTimerUpdated(wxTimerEvent& event) {
    COUNT++;
    wxClientDC clientdc(this);
    clientdc.SetClippingRegion(wxPoint(0, 0), wxSize(800, 600));
    wxBufferedDC dc(&clientdc);
    dc.SetPen(wxColor(0, 0, 0));

    // FUNCTION : Clear the old snake bodies and the eaten apple

    for (int i = 1; i <= 30; i++) {
        for (int j = 1; j <= 40; j++) {
            if (blockGroup[i][j].type == snakeBlock
             || blockGroup[i][j].type == computerBlock
             || (targetApple.isEaten == true
             && blockGroup[i][j].type == appleBlock))
                blockGroup[i][j].type = emptyBlock;
        }
    }

    // FUNCTION : Regenerate the snake body

    for (int i = 1; i <= computersNum; i++) {
        SnakeNode* pointer = computerSnake[i - 1].tail;
        while (pointer != nullptr) {
            if (computerSnake[i - 1].isDead == false) {
                blockGroup[(*pointer).y][(*pointer).x].type = computerBlock;
            }
            else {
                blockGroup[(*pointer).y][(*pointer).x].type = emptyBlock;
            }
            pointer = (*pointer).next;
        }
    }

    SnakeNode* pointer = player.tail;
    while (pointer != nullptr) {
        if (player.isDead == false) {
            blockGroup[(*pointer).y][(*pointer).x].type = snakeBlock;
        }
        else {
            blockGroup[(*pointer).y][(*pointer).x].type = emptyBlock;
        }
        pointer = (*pointer).next;
    }

    for (int i = 1; i <= 30; i++) {
        for (int j = 1; j <= 40; j++) {
            switch (blockGroup[i][j].type) {
                case emptyBlock:
                    dc.SetBrush(wxColor(0, 0, 0));
                    break;
                case snakeBlock:
                    dc.SetBrush(wxColor(91, 158, 232));
                    break;
                case computerBlock:
                    dc.SetBrush(wxColor(172, 132, 46));
                    break;
                case barrierBlock:
                    dc.SetBrush(wxColor(240, 240, 240));
                    break;
                case appleBlock:
                    dc.SetBrush(wxColor(108, 32, 34));
                    break;
            }
            blockGroup[i][j].rect.SetX(20 * (j - 1));
            blockGroup[i][j].rect.SetY(20 * (i - 1));
            blockGroup[i][j].rect.SetWidth(20);
            blockGroup[i][j].rect.SetHeight(20);
            dc.DrawRectangle(blockGroup[i][j].rect);
        }
    }

    if (COUNT >= 20) {

        // FUNCTION : Update the snake body

        for (int i = 1; i <= computersNum; i++) {
            // computerSnake[i - 1].actionControl();
            computerSnake[i - 1].updateBody();
        }
        player.updateBody();

        // FUNCTION : Check the dead status

        for (int i = 1; i <= computersNum; i++) {
            if (blockGroup[computerSnake[i - 1].head->y][computerSnake[i - 1].head->x].type == computerBlock
             || blockGroup[computerSnake[i - 1].head->y][computerSnake[i - 1].head->x].type == snakeBlock
             || blockGroup[computerSnake[i - 1].head->y][computerSnake[i - 1].head->x].type == barrierBlock)
                computerSnake[i - 1].isDead = true;
        }
        if (blockGroup[player.head->y][player.head->x].type == computerBlock
         || blockGroup[player.head->y][player.head->x].type == snakeBlock
         || blockGroup[player.head->y][player.head->x].type == barrierBlock)
            player.isDead = true;
        
        // FUNCTION : Check if a snake eats the apple

        for (int i = 1; i <= computersNum; i++) {
            if (blockGroup[computerSnake[i - 1].head->y][computerSnake[i - 1].head->y].type == appleBlock) {
                computerSnake[i - 1].eatApple();
                targetApple.isEaten = true;
            }
        }
        if (blockGroup[player.head->y][player.head->x].type == appleBlock) {
            player.eatApple();
            targetApple.isEaten = true;
        }

        // FUNCTION : Regenerate the apple

        if (targetApple.isEaten == true) {
            int randomAppleX = rand() % 38 + 2;
            int randomAppleY = rand() % 28 + 2;
            while (blockGroup[randomAppleY][randomAppleX].type == snakeBlock
                || blockGroup[randomAppleY][randomAppleX].type == barrierBlock
                || blockGroup[randomAppleY][randomAppleX].type == computerBlock) {
                    randomAppleX = rand() % 38 + 2;
                    randomAppleY = rand() % 28 + 2;
            }
            targetApple.x = randomAppleX;
            targetApple.y = randomAppleY;
            targetApple.isEaten = false;
            blockGroup[targetApple.y][targetApple.x].type = appleBlock;
        }
        COUNT = 0;
    }
}

SnakeGamePanel::SnakeGamePanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(800, 600)) {
    (*easyButton).Create(this, SNAKE_EASY,
                         wxT("EASY"), wxPoint(350, 100), wxSize(100, 50));
    (*mediumButton).Create(this, SNAKE_MEDIUM,
                           wxT("MEDIUM"), wxPoint(350, 200), wxSize(100, 50));
    (*hardButton).Create(this, SNAKE_HARD,
                         wxT("HARD"), wxPoint(350, 300), wxSize(100, 50));
}

// ----------------------------
// SnakeMainFrame
// ----------------------------

wxBEGIN_EVENT_TABLE(SnakeMainFrame, wxFrame)
    EVT_BUTTON(SNAKE_LEFT, SnakeMainFrame::OnPressLeft)
    EVT_BUTTON(SNAKE_RIGHT, SnakeMainFrame::OnPressRight)
    EVT_BUTTON(SNAKE_UP, SnakeMainFrame::OnPressUp)
    EVT_BUTTON(SNAKE_DOWN, SnakeMainFrame::OnPressDown)
wxEND_EVENT_TABLE()

inline void SnakeMainFrame::OnPressLeft(wxCommandEvent& event) {
    (*gamePanel).controlPlayerSnake(left);
}

inline void SnakeMainFrame::OnPressRight(wxCommandEvent& event) {
    (*gamePanel).controlPlayerSnake(right);
}

inline void SnakeMainFrame::OnPressUp(wxCommandEvent& event) {
    (*gamePanel).controlPlayerSnake(up);
}

inline void SnakeMainFrame::OnPressDown(wxCommandEvent& event) {
    (*gamePanel).controlPlayerSnake(down);
}

void SnakeMainFrame::disableMotionButtons() {
    (*leftButton).Disable();
    (*rightButton).Disable();
    (*upButton).Disable();
    (*downButton).Disable();
}

void SnakeMainFrame::enableMotionButtons() {
    (*leftButton).Enable();
    (*rightButton).Enable();
    (*upButton).Enable();
    (*downButton).Enable();
}

SnakeMainFrame::SnakeMainFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 600)) {
    (*this).Center();
    (*this).SetBackgroundColour(wxColor(60, 60, 60));
    (*gamePanel).getMainframe(this);
    (*gamePanel).SetBackgroundColour(wxColor(0, 0, 0));
    wxImage leftImage, rightImage, upImgae, downImgae;
    leftImage.LoadFile(wxT("resource/left.png"), wxBITMAP_TYPE_ANY);
    leftImage.Rescale(25, 25);
    wxBitmap* leftBitmap = new wxBitmap(leftImage);
    (*leftButton).Create(this, SNAKE_LEFT,
                         *leftBitmap,
                         wxPoint(850, 300), wxSize(50, 50));
    rightImage.LoadFile(wxT("resource/right.png"), wxBITMAP_TYPE_ANY);
    rightImage.Rescale(25, 25);
    wxBitmap* rightBitmap = new wxBitmap(rightImage);
    (*rightButton).Create(this, SNAKE_RIGHT,
                          *rightBitmap,
                          wxPoint(900, 300), wxSize(50, 50));
    upImgae.LoadFile(wxT("resource/up.png"), wxBITMAP_TYPE_ANY);
    upImgae.Rescale(25, 25);
    wxBitmap* upBitmap = new wxBitmap(upImgae);
    (*upButton).Create(this, SNAKE_UP, 
                       *upBitmap,
                       wxPoint(875, 250), wxSize(50, 50));
    downImgae.LoadFile(wxT("resource/down.png"), wxBITMAP_TYPE_ANY);
    downImgae.Rescale(25, 25);
    wxBitmap* downBitmap = new wxBitmap(downImgae);
    (*downButton).Create(this, SNAKE_DOWN,
                         *downBitmap,
                         wxPoint(875, 350), wxSize(50, 50));
    (*this).disableMotionButtons();
}