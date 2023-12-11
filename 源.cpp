
#include<easyx.h>
#include<stdio.h>    //�ṩͼ�ο�ͷ�ļ�
#include<graphics.h> // ���� EasyX ͼ�ο�
#include<iostream>
#include<conio.h>   //_getch();
#pragma comment(lib,"Winmm.lib")
using namespace std;

//������ ����ɹ����г����밲װeasyx  ������

#define KEY_DOWN(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1 : 0)  //��ȡ����

const int WIDTH = 640, HEIGHT = 480,B_WIDTH=630,B_HEIGHT=300;  //���ڿ����


void on() {  //����״̬ ������
    clearcircle(320, 330, 29);
    rectangle(310, 320, 315, 342);
    rectangle(325, 320, 330, 342);

}
void off() {  //��ͣ״̬ ������
    clearcircle(320, 330, 29);
    POINT pts[] = { {313, 320}, {332, 331}, {313, 342} };
    polygon(pts, 3);
}

class window {  //����
public:
    window(int w, int h) :width(w), height(h) {

    }
    void setWindow() {
        //initgraph(width, height, EX_SHOWCONSOLE);    //�½�����
        initgraph(width, height);    //�½�����
        
        setbkcolor(WHITE);      //������ɫ
        cleardevice();  //������ȥ����ɫ
    }
    void setMainMenu() {  //���ò˵�
        setcolor(BLACK);
        rectangle(200, 200, 440, 250);  //��ѡ���
        rectangle(200, 260, 440, 310);
        rectangle(200, 320, 440, 370);
        rectangle(200, 380, 440, 430);
        settextcolor(BLUE);  //�ı�������ɫ
        settextstyle(100, 0, _T("����"));//my easyx
        outtextxy(140, 50, L"My Easyx");
        settextcolor(BLACK);
        settextstyle(30, 0, _T("����")); //��ѡ��
        outtextxy(255, 210, _T("Ball Game"));
        outtextxy(285, 270, _T("Music"));
        outtextxy(290, 330, _T("Help"));
        outtextxy(290, 390, _T("Exit"));
        
        
        
        settextstyle(20, 0, _T("΢���ź�")); //�ֺţ��ֿ�����
        outtextxy(450, 210, _T("alt+b"));   //��ݼ���ʾ
        outtextxy(450, 270, _T("alt+m"));
        outtextxy(450, 330, _T("alt+h"));
        outtextxy(450, 390, _T("esc"));
        outtextxy(20, 447, L"ѡ���ұ�Ϊ��Ͽ�ݼ�");
        outtextxy(550, 447, L"by IlightnNG");  //������
    }

    void setBallMenu() {
        cleardevice();
        rectangle(10, 10, B_WIDTH, B_HEIGHT);
        rectangle(148, 320, 191, 370);
        rectangle(200, 320, 440, 370);
        rectangle(200, 380, 440, 430);
        settextstyle(30, 0, _T("����"));
        outtextxy(155, 330, _T("��"));
        outtextxy(235, 330, _T("Change Speed"));
        outtextxy(290, 390, _T("Back"));
        settextstyle(20, 0, _T("΢���ź�"));
        outtextxy(450, 330, _T("alt+c"));
        outtextxy(450, 390, _T("alt+q"));
    }
    
    void setMusicMenu() {
        cleardevice();

        rectangle(120,70,240,250);  //��������
        rectangle(260,70,380,250);
        rectangle(400, 70, 520, 250);
        setcolor(RED);
        rectangle(115, 65, 245, 255);
        setcolor(BLACK);
        settextstyle(60, 0, _T("����"));
        outtextxy(152, 80, L"��");
        outtextxy(292, 80, L"��");
        outtextxy(432, 80, L"��");


        circle(320, 330, 30);   //��ͣ��
        off();

        POINT pts1[] = { {383, 320}, {402, 331}, {383, 342} }; //��
        polygon(pts1, 3);
        rectangle(402,320,407,342);
        POINT pts2[] = { {257, 320}, {238, 331}, {257, 342} }; //��
        polygon(pts2, 3);
        rectangle(233, 320, 238, 342);

        rectangle(200, 380, 440, 430);  //back
        settextstyle(30, 0, _T("����"));
        outtextxy(290, 20, _T("Music"));
        outtextxy(290, 390, _T("Back"));

        settextstyle(20, 0, _T("΢���ź�")); //��ݼ���ʾ
        outtextxy(450, 390, _T("alt+q"));
        outtextxy(420, 321, _T("+"));
        outtextxy(215, 321, _T("-"));
        outtextxy(20, 447, L"����\"-\"\"+\"ѡ��������ո񲥷���ͣ");


    }

    void setHelpMenu(){
        cleardevice();
        settextstyle(30, 0, _T("����"));
        outtextxy(290, 20, _T("Help"));
        outtextxy(100, 100, L"1.ѡ���ұ�Ϊ��Ͽ�ݼ�");
        outtextxy(100,180, L"2.��ȷ����ȷ��װeasyx");
        outtextxy(100, 260, L"3.��ȷ��.mp3�ļ���cppͬĿ¼");

        rectangle(200, 380, 440, 430);  //back
        outtextxy(290, 390, _T("Back"));
        settextstyle(20, 0, _T("΢���ź�")); //��ݼ���ʾ
        outtextxy(450, 390, _T("alt+q"));
    }

private:
    int width, height;
};

class ball {
public:
    ball(int r,COLORREF c, COLORREF fc) :r(r), c(c), fc(fc) {
        setcolor(c);   //�������������ɫ
        setfillcolor(fc);       //������ڲ�����ɫ
    }
    void start() {      //�˶�����
        fillcircle(x, y, r); //����һ��С��
        Sleep(30);
        clearcircle(x, y, r + 1);
        int k1 = 1, k2 = 1;
        int i=0;
        while (!(KEY_DOWN(18) && KEY_DOWN(81))) {  //���·��ؼ���ֹ
            x = x + speed[i] * k1;       //���ñ仯����
            y = y + speed[i] * k2;
            if (x - r > 10 && x + r < B_WIDTH && y - r > 10 && y + r < B_HEIGHT) {
                setcolor(c);                      //���Ʊ仯���С��
                setfillcolor(fc);
                fillcircle(x, y, r);
                Sleep(30);
                clearcircle(x, y, r+1);          //������һ��С��
            }
            if (y + r >= B_HEIGHT || y - r <= 10) {            //���ڷ���
                k2 = -k2;
            }
            if (x + r >= B_WIDTH || x - r <= 10) {
                k1 = -k1;
            }

            if (KEY_DOWN(18) && KEY_DOWN(67)) { //alt+c  �ı��ٶ�
                i = (++i) % 3;
                settextstyle(30, 0, _T("����"));
                switch (i)
                {
                case 0:
                    outtextxy(155, 330, _T("��"));
                    break;
                case 1:
                    outtextxy(155, 330, _T("��"));
                    break;
                default:
                    outtextxy(155, 330, _T("��"));
                    break;
                }
                Sleep(150);
            }
        }

    }

private:
    int x = 200, y = 200;  //��ĳ�ʼ����
    int r;      //��뾶
    COLORREF c, fc;     //��������ɫ�������ɫ
    int speed[3] = {5,10,15};  //3���ٶ��л�

};

void stopAll() {
    mciSendString(_T("stop bgm0"), NULL, 0, NULL);
    mciSendString(_T("stop bgm1"), NULL, 0, NULL);
    mciSendString(_T("stop bgm2"), NULL, 0, NULL);
}

void exRectangle(int i) {   // ɾ���򣬲�������ӷ���
    settextstyle(60, 0, _T("����"));
    switch (i)
    {
    case 0:
        clearrectangle(115, 65, 245, 255);
        rectangle(120, 70, 240, 250);  //��������
        outtextxy(152, 80, L"��");
        break;
    case 1:
        clearrectangle(255, 65, 385, 255);
        rectangle(260, 70, 380, 250);
        outtextxy(292, 80, L"��");
        break;
    case 2:
        clearrectangle(395, 65, 525, 255);
        rectangle(400, 70, 520, 250);
        outtextxy(432, 80, L"��");
        break;
    default:
        break;
    }
}

void nextRectangle(int i) {  //����µĿ�
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
        if (KEY_DOWN(32) && flag == 0) {   //�ո�� ����
            flag = 1;
            on();
            switch (i)
            {
            case 0:
                if (ifNew) {
                    mciSendString(_T("open ./0.mp3 alias bgm0"), NULL, 0, NULL);//��������
                }
                mciSendString(_T("play bgm0 repeat"), NULL, 0, NULL);//ѭ������
                while (KEY_DOWN(32));//��ֹ��ͬһ�ΰ���ʱ�����ж�
                break;
            case 1:
                if (ifNew) {
                    mciSendString(_T("open ./1.mp3 alias bgm1"), NULL, 0, NULL);//��������
                }
                mciSendString(_T("play bgm1 repeat "), NULL, 0, NULL);//ѭ������
                while (KEY_DOWN(32)) ;//��ֹ��ͬһ�ΰ���ʱ�����ж�
                break;
            case 2:
                if (ifNew) {
                    mciSendString(_T("open ./2.mp3 alias bgm2"), NULL, 0, NULL);//��������
                }
                mciSendString(_T("play bgm2 repeat"), NULL, 0, NULL);//ѭ������
                while (KEY_DOWN(32)) ;//��ֹ��ͬһ�ΰ���ʱ�����ж�
                break;
            default:
                break;
            }
            ifNew[i] = false;  //��ֹ��δ�ͬһ������
        }
        else if (KEY_DOWN(32) && flag == 1) {   //��ͣ
            flag = 0;
            off();
            stopAll();
            while (KEY_DOWN(32));
        }

        if (KEY_DOWN(187)) { //+  ѡ�����
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
    HWND hwnd = GetHWnd();   //��ȡ���ھ��
    SetWindowText(hwnd, L"My Easyx "); //���Ĵ��ڱ���
    
    bool flag = true;
    while (flag) {
        
        Sleep(10);
        if (KEY_DOWN(18)&&KEY_DOWN(66)) { //alt+b   1.ball game

            cleardevice();
            win1.setBallMenu();
            ball b1(15, BLACK, BLUE);
            b1.start();
            
            if (KEY_DOWN(18)&&KEY_DOWN(81)) {  //alt+q ����
                cleardevice();
                win1.setMainMenu();
            }
        }

        if (KEY_DOWN(18) && KEY_DOWN(77)) {  //alt+m  2.music
            win1.setMusicMenu();
            chooseMusic();

            if (KEY_DOWN(18) && KEY_DOWN(81)) {  //alt+q ����
                cleardevice();
                win1.setMainMenu();
                mciSendString(_T("close bgm0"), NULL, 0, NULL);  //�ر���������
                mciSendString(_T("close bgm1"), NULL, 0, NULL);
                mciSendString(_T("close bgm2"), NULL, 0, NULL);
            }


        }
        if (KEY_DOWN(18) && KEY_DOWN(72)) { //alt+h  3.help
            win1.setHelpMenu();
            while (!(KEY_DOWN(18) && KEY_DOWN(81))) {};  //�ȴ��Ƴ�
            if (KEY_DOWN(18) && KEY_DOWN(81)) {  //alt+q ����
                cleardevice();
                win1.setMainMenu();
            }
        }

        if (KEY_DOWN(27)) {
            MessageBox(hwnd,L"ȷ���˳���",L"�˳�",MB_OKCANCEL);  //����ȷ�ϴ���
            closegraph();  //�رմ���
            flag = false;
            
        }
        Sleep(10);
    };

   
          
}




/*
#include<Windows.h>

LRESULT CALLBACK WinSunProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)//ͨ���ж���Ϣ������Ϣ��Ӧ
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);//���ٴ��ڲ�����WM_DESTROY��Ϣ�����ǳ���û���˳�
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//����WM_QUIT��Ϣ��������Ϣѭ��
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//�Բ�����Ȥ����Ϣ����ȱʡ���������иô��룬�������������
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	WNDCLASS wndcls; //����һ��������
	wndcls.cbClsExtra = 0;//��Ķ����ڴ棬Ĭ��Ϊ0����
	wndcls.cbWndExtra = 0;//���ڵĶ����ڴ棬Ĭ��Ϊ0����
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//��ȡ��ˢ����������ص�HGDIOBJ����ǿ������ת����
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);//���ù��
	wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);//���ô������Ͻǵ�ͼ��
	wndcls.hInstance = hInstance;//���ô���������Ӧ�ó���ʵ��
	wndcls.lpfnWndProc = WinSunProc;//���ô���Ļص���������ʱûд��������ΪNULL�����油��
	wndcls.lpszClassName = L"test";//���ô��������
	wndcls.lpszMenuName = NULL;//���ô���Ĳ˵�,û�У���NULL
	wndcls.style = CS_HREDRAW | CS_VREDRAW;//���ô�����Ϊˮƽ�ػ��ʹ�ֱ�ػ�
	RegisterClass(&wndcls);//�����ϵͳע�ᴰ��
	
	HWND hwnd = CreateWindow(L"test", L"�ҵĵ�һ������",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	

	ShowWindow(hwnd, SW_SHOWNORMAL);//�Ѵ�����ʾ����
	UpdateWindow(hwnd);//���´���

	MSG msg;
	//��Ϣѭ��
	while (GetMessage(&msg, NULL, 0, 0))//�����Ϣ����WM_QUIT,���ط���ֵ�������Ϣ��WM_QUIT��������
	{
		TranslateMessage(&msg);//������Ϣ�����WM_KEYDOWN��WM_KEYUP�����һ��WM_CHAR��Ϣ
		DispatchMessage(&msg);//�ɷ���Ϣ
	}
	
}
*/


