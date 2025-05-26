#include "pch.h"
#include "MouseObject.h"

MOUSE_OBJ* StartMouseObject(int x, int y, int w, int h) 
{
    MOUSE_OBJ* Temp = (MOUSE_OBJ*)calloc(1, sizeof(MOUSE_OBJ));
    Temp->x = x;
    Temp->y = y;
    Temp->state = NONE; 
    Temp->wheelDelta = 0; 
    Temp->strWheel[0] = 0;
    Temp->w = w; Temp->h = h;
    Temp->hPen = CreatePen(PS_SOLID, 2, RGB(100, 100, 100));
    Temp->hBodyBrush = CreateSolidBrush(RGB(220, 220, 220));
    Temp->hHighlight = CreateSolidBrush(RGB(255, 255, 255));
    Temp->hWheelBrush = CreateSolidBrush(RGB(0, 160, 0));


    int btnMarginX = w / 10;         // �� �� ����
    int btnMarginY = h / 12;         // ���� ����
    int btnGapX = w / 32;            // �߰� ��ư�� �¿� ��ư ���� ����
    int btnHeight = h / 3;           // ��ư ���� ũ�� (��ü ��� 1/3)
    int btnWidth = (w - 2 * btnMarginX - btnGapX) / 2; // �¿� ��ư ��

    // ���� ��ư
    Temp->buttons[MouseBtn::LEFT].rect.left = -w / 2 + btnMarginX;
    Temp->buttons[MouseBtn::LEFT].rect.top = -h / 2 + btnMarginY;
    Temp->buttons[MouseBtn::LEFT].rect.right = Temp->buttons[MouseBtn::LEFT].rect.left + btnWidth;
    Temp->buttons[MouseBtn::LEFT].rect.bottom = Temp->buttons[MouseBtn::LEFT].rect.top + btnHeight;
    Temp->buttons[MouseBtn::LEFT].normalColor = RGB(230, 120, 120); Temp->buttons[MouseBtn::LEFT].downColor = RGB(200, 0, 0);
    Temp->hButtonBrushes[MouseBtn::LEFT][MouseBtn::NORMAL] = CreateSolidBrush(Temp->buttons[MouseBtn::LEFT].normalColor);
    Temp->hButtonBrushes[MouseBtn::LEFT][MouseBtn::DOWN] = CreateSolidBrush(Temp->buttons[MouseBtn::LEFT].downColor);

    // ������ ��ư
    Temp->buttons[MouseBtn::RIGHT].rect.right = w / 2 - btnMarginX;
    Temp->buttons[MouseBtn::RIGHT].rect.top = -h / 2 + btnMarginY;
    Temp->buttons[MouseBtn::RIGHT].rect.left = Temp->buttons[MouseBtn::RIGHT].rect.right - btnWidth;
    Temp->buttons[MouseBtn::RIGHT].rect.bottom = Temp->buttons[MouseBtn::RIGHT].rect.top + btnHeight;
    Temp->buttons[MouseBtn::RIGHT].normalColor = RGB(120, 150, 230); Temp->buttons[MouseBtn::RIGHT].downColor = RGB(0, 0, 180);
    Temp->hButtonBrushes[MouseBtn::RIGHT][MouseBtn::NORMAL] = CreateSolidBrush(Temp->buttons[MouseBtn::RIGHT].normalColor);
    Temp->hButtonBrushes[MouseBtn::RIGHT][MouseBtn::DOWN] = CreateSolidBrush(Temp->buttons[MouseBtn::RIGHT].downColor);

    // �߰� ��ư
    int midBtnWidth = w / 8;
    int midBtnHeight = btnHeight * 2 / 3;
    Temp->buttons[MouseBtn::MIDDLE].rect.left = -midBtnWidth / 2;
    Temp->buttons[MouseBtn::MIDDLE].rect.top = -h / 2 + btnMarginY + btnHeight / 4;
    Temp->buttons[MouseBtn::MIDDLE].rect.right = midBtnWidth / 2;
    Temp->buttons[MouseBtn::MIDDLE].rect.bottom = Temp->buttons[MouseBtn::MIDDLE].rect.top + midBtnHeight;
    Temp->buttons[MouseBtn::MIDDLE].normalColor = RGB(160, 230, 160); Temp->buttons[MouseBtn::MIDDLE].downColor = RGB(0, 160, 0);
    Temp->hButtonBrushes[MouseBtn::MIDDLE][MouseBtn::NORMAL] = CreateSolidBrush(Temp->buttons[MouseBtn::MIDDLE].normalColor);
    Temp->hButtonBrushes[MouseBtn::MIDDLE][MouseBtn::DOWN] = CreateSolidBrush(Temp->buttons[MouseBtn::MIDDLE].downColor);
    //��
    Temp->wheel_cx = 0;
    Temp->wheel_cy = -h / 2 + btnMarginY + midBtnHeight / 2;
    Temp->wheel_r = w / 12;

    for (int i = 0; i < 3; ++i) Temp->buttons[i].isDown = FALSE;


    Temp->Draw = Draw;
    Temp->Update = Update;
    Temp->SetWheel = SetWheel;
    Temp->Release = Release;

    Temp->handlers[NONE] = MouseOnNone;
    Temp->handlers[LBD] = MouseOnLBD;
    Temp->handlers[LBU] = MouseOnLBU;
    Temp->handlers[RBD] = MouseOnRBD;
    Temp->handlers[RBU] = MouseOnRBU;
    Temp->handlers[MBD] = MouseOnMBD;
    Temp->handlers[MBU] = MouseOnMBU;
    Temp->handlers[LDBLK] = MouseOnLDBLK;
    Temp->handlers[RDBLK] = MouseOnRDBLK;
    Temp->handlers[MDBLK] = MouseOnMDBLK;

    return Temp;
}

void Draw(MOUSE_OBJ* mouse, HDC hdc) 
{
    int cx = mouse->x, cy = mouse->y, w = mouse->w, h = mouse->h;
    BOOL isLeftDown = (mouse->state == LBD || mouse->state == LDBLK);
    BOOL isRightDown = (mouse->state == RBD || mouse->state == RDBLK);
    BOOL isMiddleDown = (mouse->state == MBD || mouse->state == MDBLK);

    ((MOUSE_OBJ*)mouse)->buttons[MouseBtn::LEFT].isDown = isLeftDown;
    ((MOUSE_OBJ*)mouse)->buttons[MouseBtn::RIGHT].isDown = isRightDown;
    ((MOUSE_OBJ*)mouse)->buttons[MouseBtn::MIDDLE].isDown = isMiddleDown;

    HPEN oldPen = (HPEN)SelectObject(hdc, mouse->hPen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, mouse->hBodyBrush);
    Ellipse(hdc, cx - w / 2, cy - h / 2, cx + w / 2, cy + h / 2);

    for (int i = 0; i < 3; ++i) 
    {
        RECT r = mouse->buttons[i].rect;
        OffsetRect(&r, cx, cy);
        HBRUSH btnBrush = mouse->hButtonBrushes[i][mouse->buttons[i].isDown ? 1 : 0];
        SelectObject(hdc, btnBrush);
        if (i == 2) RoundRect(hdc, r.left, r.top, r.right, r.bottom, w / 14, h / 14);
        else Rectangle(hdc, r.left, r.top, r.right, r.bottom);
    }

    LPCWSTR strTemp = L"";
    switch (mouse->state) 
    {
    case LBD:   strTemp = L"���� ��ư ����";      break;  
    case LBU:   strTemp = L"���� ��ư ��";        break;
    case LDBLK: strTemp = L"���� ����Ŭ��";       break;
    case RBD:   strTemp = L"������ ��ư ����";    break; 
    case RBU:   strTemp = L"������ ��ư ��";      break;
    case RDBLK: strTemp = L"������ ����Ŭ��";     break;
    case MBD:   strTemp = L"�߰� ��ư ����";      break;  
    case MBU:   strTemp = L"�߰� ��ư ��";        break;    
    case MDBLK: strTemp = L"�߰� ����Ŭ��";       break;
    default:    strTemp = L"                 ";   break;
    }
    if (wcslen(strTemp) > 0)
    { 
        SetBkMode(hdc, TRANSPARENT); 
        SetTextAlign(hdc, TA_CENTER);
        TextOut(hdc, cx, mouse->h / 2, strTemp, wcslen(strTemp));
    }
    if (mouse->wheelDelta != 0) 
    { 
        SetBkMode(hdc, TRANSPARENT); 
        SetTextAlign(hdc, TA_CENTER);
        TextOut(hdc, cx, mouse->h / 2 + 20, mouse->strWheel, wcslen(mouse->strWheel)); 
    }
}

void Update(MOUSE_OBJ* mouse, MouseMSG state, LPARAM lParam)
{
    mouse->x = LOWORD(lParam);
    mouse->y = HIWORD(lParam);
    mouse->state = state;
}

void SetWheel(MOUSE_OBJ* mouse, WPARAM wParam)
{
    mouse->wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
    wsprintf(mouse->strWheel, L"Wheel: %3d", mouse->wheelDelta);
}

void Release(MOUSE_OBJ* mouse)
{
    DeleteObject(mouse->hPen);
    DeleteObject(mouse->hBodyBrush);
    DeleteObject(mouse->hHighlight);
    DeleteObject(mouse->hWheelBrush);
    for (int i = 0; i < 3; ++i) 
    {
        DeleteObject(mouse->hButtonBrushes[i][0]);
        DeleteObject(mouse->hButtonBrushes[i][1]);
    }
    free(mouse);
}

