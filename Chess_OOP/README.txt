//主要新增項目
我考慮到可能要做存讀檔功能，所以Player底下棋子除了King一定只有一個，其他都用vector存。

接下來因為點擊GUI只能回傳點到的位置(x,y)，為了根據這組(x,y)找到棋盤上面的棋子。

我在Board.h裡多存了bool ifHavePiece(是否有棋子在這格)、char player(棋子是哪方的)、string chessType(棋子種類)、int index(第幾個棋子，對應vector的index)，而每個棋子class也存了他們是第幾個index。

而我在GameManager.h裡放了8*8的board，在執行showCanMove與playerMove時應該就能順利取到棋子了

//我的一些小建議
因為我class的東西都用public，就不用額外寫函式去改值了

棋子類別目前只剩一個move函式，應該直接定義在.h檔就行，不應再另外寫.cpp了

//以下是目前程式大致流程
1.執行後main基本就沒用了，直接進到mainwindow.cpp，執行setBoard()(放上label並填色)、initIcon()(設置好所有圖案)

2.玩家點下new game，執行mainwindow裡的on_newGame_clicked()(設置圖案到GUI、設置所有棋子與棋盤資訊)

主要遊戲迴圈
3.玩家點擊GUI，執行mainwindow裡的labelClicked()(傳入哪個位置(x,y)被點擊。根據目前的clickTimes選擇執行showCanMove()(顯示棋子能移動的位置)或是playerMove()(移動棋子))

//以下是我的一些架構想法
1.因為GUI好像只能在mainwindow裡才動的到，所以showCanMove、playerMove都先把資訊更新在GameManager裡的board上，然後在mainwindow加個update去更新每次點擊後的棋盤。

2.因為GameManager的資料存法，每個棋子的.h檔取不到board。我在想直接把每個棋子走法寫在showCanMove裡。
