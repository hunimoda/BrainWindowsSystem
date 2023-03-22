#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

enum { DIV = 1, MUL, ADD, MIN, EXIT };

DWORD ShowMenu();
BOOL Calculator();

int _tmain(int argc, TCHAR *argv[]) {
  BOOL state;
  do {
    state = Calculator();
  } while (state);
  return 0;
}

DWORD ShowMenu() {
  DWORD sel;
  _fputts(_T("----- Menu ----- \n"), stdout);
  _fputts(_T("1) Divide \n"), stdout);
  _fputts(_T("2) Multiply \n"), stdout);
  _fputts(_T("3) Add \n"), stdout);
  _fputts(_T("4) Minus \n"), stdout);
  _fputts(_T("5) Exit \n"), stdout);
  _fputts(_T("---------------- \n"), stdout);
  _fputts(_T("SELECT>>"), stdout);
  _tscanf(_T("%d"), &sel);
  return sel;
}

BOOL Calculator() {
  DWORD sel = ShowMenu();
  if (sel == EXIT) return FALSE;

  int num1, num2;
  _fputts(_T("Input num1, num2: "), stdout);
  _tscanf(_T("%d %d"), &num1, &num2);

  __try {
    switch (sel) {
      case DIV:
        _tprintf(_T("%d ÷ %d = %d \n\n"), num1, num2, num1 / num2);
        break;

      case MUL:
        _tprintf(_T("%d × %d = %d \n\n"), num1, num2, num1 * num2);
        break;

      case ADD:
        _tprintf(_T("%d + %d = %d \n\n"), num1, num2, num1 + num2);
        break;

      case MIN:
        _tprintf(_T("%d - %d = %d \n\n"), num1, num2, num1 - num2);
        break;
    }
  } __except (EXCEPTION_EXECUTE_HANDLER) {
    _fputts(_T("Wrong number inserted. Try again! \n\n"), stdout);
  }
  return TRUE;
}