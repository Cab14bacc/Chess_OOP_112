//新增項目
GameManager裡新增char selectChessPlayer(被選中的棋子是哪方的)、string selectChessType(選中棋子類型)、int selectChessIndex(選中棋子在vector中的位置)

Board裡新增bool canMove(紀錄能否移動)

mainwindow新增void update(更新GUI顯示)

//以下是目前程式大致流程
1.執行後main基本就沒用了，直接進到mainwindow.cpp，執行setBoard()(放上label並填色)、initIcon()(設置好所有圖案)

2.玩家點下new game，執行mainwindow裡的on_newGame_clicked()(設置圖案到GUI、設置所有棋子與棋盤資訊)

主要遊戲迴圈
3.玩家點擊GUI，執行mainwindow裡的labelClicked()(傳入哪個位置(x,y)被點擊。根據目前的clickTimes選擇執行showCanMove()(顯示棋子能移動的位置)或是playerMove()(移動棋子))

4.clickTimes等於1，執行showCanMove。算出棋子可移動board位置、更新GameManager裡選中棋子資訊。

5.update函式更新GUI

6.clickTimes不等於1，執行playerMove。情況1:點擊合法，移動棋子。情況2:點擊非法，回復到選取前棋子狀態。

7.update函式更新GUI

//遊戲結束


//以下是待寫函式

mainwindow:

void update()//根據board訊息，更新GUI。可直接用label->setStyleSheet("QLabel{background-color:rgb(int r, int g, int b);}")這個函式直接把棋盤背景上色，當作可移動位置的提示。

GameManager:

void showCanMove(int row, int col)//根據傳入的位置，去board取得對應棋子資訊。計算可移動棋盤位置，並更新board選中棋子資訊。

void playerMove(int row, int col)//根據傳入位置與選中棋子資訊移動棋子，並將全部東西回復到選棋子狀態。

bool ifGameOver()//判斷遊戲是否結束(目前在判斷算法還有障礙，這邊就先只判斷雙方國王是否還在場上)

Board:

void computeTarget()//計算每格棋盤可被幾個棋子攻擊。

