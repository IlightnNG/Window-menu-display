
#include<easyx.h>
#include<stdio.h>    //提供图形库头文件
#include<graphics.h> // 引用 EasyX 图形库
#include<iostream>
#include<conio.h>   //_getch();
#pragma comment(lib,"Winmm.lib")
using namespace std;

//！！！ 若想成功运行程序，请安装easyx  ！！！

#define KEY_DOWN(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1 : 0)  //读取键盘

const int WIDTH = 640, HEIGHT = 480,B_WIDTH=630,B_HEIGHT=300;  //窗口宽与高


void on() {  //播放状态 两条杠
    clearcircle(320, 330, 29);
    rectangle(310, 320, 315, 342);
    rectangle(325, 320, 330, 342);

}
void off() {  //暂停状态 三角形
    clearcircle(320, 330, 29);
    POINT pts[] = { {313, 320}, {332, 331}, {313, 342} };
    polygon(pts, 3);
}

class window {  //窗口
public:
    window(int w, int h) :width(w), height(h) {

    }
    void setWindow() {
        //initgraph(width, height, EX_SHOWCONSOLE);    //新建窗口
        initgraph(width, height);    //新建窗口
        
        setbkcolor(WHITE);      //窗口颜色
        cleardevice();  //清屏，去除黑色
    }
    void setMainMenu() {  //设置菜单
        setcolor(BLACK);
        rectangle(200, 200, 440, 250);  //各选项方框
        rectangle(200, 260, 440, 310);
        rectangle(200, 320, 440, 370);
        rectangle(200, 380, 440, 430);
        settextcolor(BLUE);  //文本字体颜色
        settextstyle(100, 0, _T("宋体"));//my easyx
        outtextxy(140, 50, L"My Easyx");
        settextcolor(BLACK);
        settextstyle(30, 0, _T("宋体")); //各选项
        outtextxy(255, 210, _T("Ball Game"));
        outtextxy(285, 270, _T("Music"));
        outtextxy(290, 330, _T("Help"));
        outtextxy(290, 390, _T("Exit"));
        
        
        
        settextstyle(20, 0, _T("微软雅黑")); //字号，字宽，字体
        outtextxy(450, 210, _T("alt+b"));   //快捷键提示
        outtextxy(450, 270, _T("alt+m"));
        outtextxy(450, 330, _T("alt+h"));
        outtextxy(450, 390, _T("esc"));
        outtextxy(20, 447, L"选项右边为组合快捷键");
        outtextxy(550, 447, L"by IlightnNG");  //制作者
    }

    void setBallMenu() {
        cleardevice();
        rectangle(10, 10, B_WIDTH, B_HEIGHT);
        rectangle(148, 320, 191, 370);
        rectangle(200, 320, 440, 370);
        rectangle(200, 380, 440, 430);
        settextstyle(30, 0, _T("宋体"));
        outtextxy(155, 330, _T("Ⅰ"));
        outtextxy(235, 330, _T("Change Speed"));
        outtextxy(290, 390, _T("Back"));
        settextstyle(20, 0, _T("微软雅黑"));
        outtextxy(450, 330, _T("alt+c"));
        outtextxy(450, 390, _T("alt+q"));
    }
    
    void setMusicMenu() {
        cleardevice();

        rectangle(120,70,240,250);  //三个方框
        rectangle(260,70,380,250);
        rectangle(400, 70, 520, 250);
        setcolor(RED);
        rectangle(115, 65, 245, 255);
        setcolor(BLACK);
        settextstyle(60, 0, _T("宋体"));
        outtextxy(152, 80, L"Ⅰ");
        outtextxy(292, 80, L"Ⅱ");
        outtextxy(432, 80, L"Ⅲ");


        circle(320, 330, 30);   //暂停键
        off();

        POINT pts1[] = { {383, 320}, {402, 331}, {383, 342} }; //右
        polygon(pts1, 3);
        rectangle(402,320,407,342);
        POINT pts2[] = { {257, 320}, {238, 331}, {257, 342} }; //左
        polygon(pts2, 3);
        rectangle(233, 320, 238, 342);

        rectangle(200, 380, 440, 430);  //back
        settextstyle(30, 0, _T("宋体"));
        outtextxy(290, 20, _T("Music"));
        outtextxy(290, 390, _T("Back"));

        settextstyle(20, 0, _T("微软雅黑")); //快捷键提示
        outtextxy(450, 390, _T("alt+q"));
        outtextxy(420, 321, _T("+"));
        outtextxy(215, 321, _T("-"));
        outtextxy(20, 447, L"按下\"-\"\"+\"选择歌曲，空格播放暂停");


    }

    void setHelpMenu(){
        cleardevice();
        settextstyle(30, 0, _T("宋体"));
        outtextxy(290, 20, _T("Help"));
        outtextxy(100, 100, L"1.选项右边为组合快捷键");
        outtextxy(100,180, L"2.请确保正确安装easyx");
        outtextxy(100, 260, L"3.请确保.mp3文件与cpp同目录");

        rectangle(200, 380, 440, 430);  //back
        outtextxy(290, 390, _T("Back"));
        settextstyle(20, 0, _T("微软雅黑")); //快捷键提示
        outtextxy(450, 390, _T("alt+q"));
    }

private:
    int width, height;
};

class ball {
public:
    ball(int r,COLORREF c, COLORREF fc) :r(r), c(c), fc(fc) {
        setcolor(c);   //填充球轮廓的颜色
        setfillcolor(fc);       //填充球内部的颜色
    }
    void start() {      //运动函数
        fillcircle(x, y, r); //绘制一个小球
        Sleep(30);
        clearcircle(x, y, r + 1);
        int k1 = 1, k2 = 1;
        int i=0;
        while (!(KEY_DOWN(18) && KEY_DOWN(81))) {  //按下返回键终止
            x = x + speed[i] * k1;       //设置变化坐标
            y = y + speed[i] * k2;
            if (x - r > 10 && x + r < B_WIDTH && y - r > 10 && y + r < B_HEIGHT) {
                setcolor(c);                      //绘制变化后的小球
                setfillcolor(fc);
                fillcircle(x, y, r);
                Sleep(30);
                clearcircle(x, y, r+1);          //擦除上一个小球
            }
            if (y + r >= B_HEIGHT || y - r <= 10) {            //遇壁反弹
                k2 = -k2;
            }
            if (x + r >= B_WIDTH || x - r <= 10) {
                k1 = -k1;
            }

            if (KEY_DOWN(18) && KEY_DOWN(67)) { //alt+c  改变速度
                i = (++i) % 3;
                settextstyle(30, 0, _T("宋体"));
                switch (i)
                {
                case 0:
                    outtextxy(155, 330, _T("Ⅰ"));
                    break;
                case 1:
                    outtextxy(155, 330, _T("Ⅱ"));
                    break;
                default:
                    outtextxy(155, 330, _T("Ⅲ"));
                    break;
                }
                Sleep(150);
            }
        }

    }

private:
    int x = 200, y = 200;  //球的初始坐标
    int r;      //球半径
    COLORREF c, fc;     //球轮廓颜色和填充颜色
    int speed[3] = {5,10,15};  //3种速度切换

};

void stopAll() {
    mciSendString(_T("stop bgm0"), NULL, 0, NULL);
    mciSendString(_T("stop bgm1"), NULL, 0, NULL);
    mciSendString(_T("stop bgm2"), NULL, 0, NULL);
}

void exRectangle(int i) {   // 删除框，并重新添加方框
    settextstyle(60, 0, _T("宋体"));
    switch (i)
    {
    case 0:
        clearrectangle(115, 65, 245, 255);
        rectangle(120, 70, 240, 250);  //三个方框
        outtextxy(152, 80, L"Ⅰ");
        break;
    case 1:
        clearrectangle(255, 65, 385, 255);
        rectangle(260, 70, 380, 250);
        outtextxy(292, 80, L"Ⅱ");
        break;
    case 2:
        clearrectangle(395, 65, 525, 255);
        rectangle(400, 70, 520, 250);
        outtextxy(432, 80, L"Ⅲ");
        break;
    default:
        break;
    }
}

void nextRectangle(int i) {  //添加新的框
    setcolor(RED);
    switch (i)
    {
    case 0:
        rectangle(115, 65, 245, 255);
        break;
    case 1:
        rectangle(255, 65, 385, 255);
        break;
    case 2:
        rectangle(395, 65, 525, 255);
        break;
    default:
        break;
    }
    setcolor(BLACK);
}

void chooseMusic() {
    int i = 0; 
    int flag = 0;
    bool ifNew[] = {true ,true,true};
    while (!(KEY_DOWN(18) && KEY_DOWN(81))) {
        if (KEY_DOWN(32) && flag == 0) {   //空格键 播放
            flag = 1;
            on();
            switch (i)
            {
            case 0:
                if (ifNew) {
                    mciSendString(_T("open ./0.mp3 alias bgm0"), NULL, 0, NULL);//播放音乐
                }
                mciSendString(_T("play bgm0 repeat"), NULL, 0, NULL);//循环播放
                while (KEY_DOWN(32));//防止在同一次按下时反复判定
                break;
            case 1:
                if (ifNew) {
                    mciSendString(_T("open ./1.mp3 alias bgm1"), NULL, 0, NULL);//播放音乐
                }
                mciSendString(_T("play bgm1 repeat "), NULL, 0, NULL);//循环播放
                while (KEY_DOWN(32)) ;//防止在同一次按下时反复判定
                break;
            case 2:
                if (ifNew) {
                    mciSendString(_T("open ./2.mp3 alias bgm2"), NULL, 0, NULL);//播放音乐
                }
                mciSendString(_T("play bgm2 repeat"), NULL, 0, NULL);//循环播放
                while (KEY_DOWN(32)) ;//防止在同一次按下时反复判定
                break;
            default:
                break;
            }
            ifNew[i] = false;  //防止多次打开同一个音乐
        }
        else if (KEY_DOWN(32) && flag == 1) {   //暂停
            flag = 0;
            off();
            stopAll();
            while (KEY_DOWN(32));
        }

        if (KEY_DOWN(187)) { //+  选择歌曲
            stopAll();
            off();
            exRectangle(i);
            flag = 0;
            i = (++i) % 3;
            nextRectangle(i);
            while (KEY_DOWN(187));
        }
        else if (KEY_DOWN(189)) {  //-
            stopAll();
            off();
            exRectangle(i);
            flag = 0;
            i = (i + 2) % 3;
            nextRectangle(i);
            while (KEY_DOWN(189));
        }

    }
}


void main() {
    window win1(WIDTH,HEIGHT);
    win1.setWindow();
    win1.setMainMenu();
    HWND hwnd = GetHWnd();   //获取窗口句柄
    SetWindowText(hwnd, L"My Easyx "); //更改窗口标题
    
    bool flag = true;
    while (flag) {
        
        Sleep(10);
        if (KEY_DOWN(18)&&KEY_DOWN(66)) { //alt+b   1.ball game

            cleardevice();
            win1.setBallMenu();
            ball b1(15, BLACK, BLUE);
            b1.start();
            
            if (KEY_DOWN(18)&&KEY_DOWN(81)) {  //alt+q 返回
                cleardevice();
                win1.setMainMenu();
            }
        }

        if (KEY_DOWN(18) && KEY_DOWN(77)) {  //alt+m  2.music
            win1.setMusicMenu();
            chooseMusic();

            if (KEY_DOWN(18) && KEY_DOWN(81)) {  //alt+q 返回
                cleardevice();
                win1.setMainMenu();
                mciSendString(_T("close bgm0"), NULL, 0, NULL);  //关闭所有音乐
                mciSendString(_T("close bgm1"), NULL, 0, NULL);
                mciSendString(_T("close bgm2"), NULL, 0, NULL);
            }


        }
        if (KEY_DOWN(18) && KEY_DOWN(72)) { //alt+h  3.help
            win1.setHelpMenu();
            while (!(KEY_DOWN(18) && KEY_DOWN(81))) {};  //等待推出
            if (KEY_DOWN(18) && KEY_DOWN(81)) {  //alt+q 返回
                cleardevice();
                win1.setMainMenu();
            }
        }

        if (KEY_DOWN(27)) {
            MessageBox(hwnd,L"确认退出吗",L"退出",MB_OKCANCEL);  //弹出确认窗口
            closegraph();  //关闭窗口
            flag = false;
            
        }
        Sleep(10);
    };

   
          
}




/*
#include<Windows.h>

LRESULT CALLBACK WinSunProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)//通过判断消息进行消息响应
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);//销毁窗口并发送WM_DESTROY消息，但是程序没有退出
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//发出WM_QUIT消息，结束消息循环
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//对不感兴趣的消息进行缺省处理，必须有该代码，否则程序有问题
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	WNDCLASS wndcls; //创建一个窗体类
	wndcls.cbClsExtra = 0;//类的额外内存，默认为0即可
	wndcls.cbWndExtra = 0;//窗口的额外内存，默认为0即可
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//获取画刷句柄（将返回的HGDIOBJ进行强制类型转换）
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);//设置光标
	wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);//设置窗体左上角的图标
	wndcls.hInstance = hInstance;//设置窗体所属的应用程序实例
	wndcls.lpfnWndProc = WinSunProc;//设置窗体的回调函数，暂时没写，先设置为NULL，后面补上
	wndcls.lpszClassName = L"test";//设置窗体的类名
	wndcls.lpszMenuName = NULL;//设置窗体的菜单,没有，填NULL
	wndcls.style = CS_HREDRAW | CS_VREDRAW;//设置窗体风格为水平重画和垂直重画
	RegisterClass(&wndcls);//向操作系统注册窗体
	
	HWND hwnd = CreateWindow(L"test", L"我的第一个窗口",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	

	ShowWindow(hwnd, SW_SHOWNORMAL);//把窗体显示出来
	UpdateWindow(hwnd);//更新窗体

	MSG msg;
	//消息循环
	while (GetMessage(&msg, NULL, 0, 0))//如果消息不是WM_QUIT,返回非零值；如果消息是WM_QUIT，返回零
	{
		TranslateMessage(&msg);//翻译消息，如把WM_KEYDOWN和WM_KEYUP翻译成一个WM_CHAR消息
		DispatchMessage(&msg);//派发消息
	}
	
}
*/


