/*----------------------------------------------------------------------------*
 * FILE INFORMATION                                                           *
 *----------------------------------------------------------------------------*
 * PROJECT  PLAIN-TOOLCHAIN-X86-64                                            *
 * FILENAME helloworld-gui.c                                                  *
 * CONTENT  Main function                                                     *
 *----------------------------------------------------------------------------*
 * Based on original code from:                                               *
 * http://www.paulgriffiths.net/program/c/srcs/winhellosrc.html               *
 *----------------------------------------------------------------------------*/

/*============================================================================*/
/* HEADERS                                                                    */
/*============================================================================*/

#include <windows.h>

/*============================================================================*/
/* CALLBACKS                                                                  */
/*============================================================================*/

static int HandlePaint (HWND WindowHandle)
{
  char   LabelText[] = "Hello World!";
  size_t LabelLength = sizeof(LabelText);
  
  PAINTSTRUCT PaintStruct;
  HDC         DeviceContext;
  RECT        ClientRect;
  RECT        LabelRect;
  
  GetClientRect(WindowHandle, &ClientRect);

  DeviceContext = BeginPaint(WindowHandle, &PaintStruct);
  
  if (DrawTextEx(DeviceContext, LabelText, LabelLength, &LabelRect, DT_CALCRECT, 0))
  {
    int LabelWidth  = (LabelRect.right  - LabelRect.left);
    int LabelHeight = (LabelRect.bottom - LabelRect.top);

    LabelRect.left   = (ClientRect.right  - LabelWidth)  / 2;
    LabelRect.top    = (ClientRect.bottom - LabelHeight) / 2;
    LabelRect.right  = (LabelRect.left + LabelWidth);
    LabelRect.bottom = (LabelRect.top  + LabelHeight);
    
    DrawTextEx(DeviceContext, LabelText, LabelLength, &LabelRect, 0, 0);
  }
  
  EndPaint(WindowHandle, &PaintStruct);

  return 0;
}

static LRESULT CALLBACK WindowProcedureCallback (HWND   WindowHandle,
                                                 UINT   Message,
                                                 WPARAM wParam,
                                                 LPARAM lParam)
{
  LRESULT ReturnValue;
  
  switch (Message)
  {
  case WM_PAINT:
    ReturnValue = HandlePaint(WindowHandle);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    ReturnValue = 0;
    break;

  default:
    ReturnValue = DefWindowProc(WindowHandle, Message, wParam, lParam);
  }
  
  return ReturnValue;
}

/*============================================================================*/
/* MAIN FUNCTION                                                              */
/*============================================================================*/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     szCmdLine,
                    int       iCmdShow)
{
  static char ApplicationName[] = "HelloWorld";
  HWND        WindowHandle;
  MSG         Message;
  WNDCLASSEX  WindowClass;

  /* Fill in WNDCLASSEX struct members */
  WindowClass.cbSize         = sizeof(WindowClass);
  WindowClass.style          = CS_HREDRAW | CS_VREDRAW;
  WindowClass.lpfnWndProc    = WindowProcedureCallback;
  WindowClass.cbClsExtra     = 0;
  WindowClass.cbWndExtra     = 0;
  WindowClass.hInstance      = hInstance;
  WindowClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
  WindowClass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);
  WindowClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
  WindowClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
  WindowClass.lpszClassName  = ApplicationName;
  WindowClass.lpszMenuName   = NULL;
  
  /* Register a new window class with Windows */
  RegisterClassEx(&WindowClass);

  /* Create a window based on our new class */
  WindowHandle = CreateWindow(ApplicationName,
                              "Hello world!",
                              WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT,
                              CW_USEDEFAULT,
                              CW_USEDEFAULT,
                              CW_USEDEFAULT,
                              NULL, NULL, hInstance, NULL);

  /* Show and update our window */
  ShowWindow(WindowHandle, iCmdShow);
  UpdateWindow(WindowHandle);

  /* Event loop */
  while (GetMessage(&Message, NULL, 0, 0) == TRUE)
  {
    TranslateMessage(&Message);
    DispatchMessage(&Message);
  }

  /*  Exit with status specified in WM_QUIT message */
  return Message.wParam;
}
