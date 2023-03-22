#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

enum { DIV = 1, MUL, ADD, MIN, EXIT };

DWORD ShowMenu();
BOOL Calculator();
DWORD FilterFunction(DWORD exptType);

void Divide(int, int);
void Multiply(int, int);
void Add(int, int);
void Min(int, int);

int num1, num2;

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
  _fputts(_T("Select>"), stdout);
  _tscanf(_T("%d"), &sel);
  return sel;
}

BOOL Calculator() {
  DWORD sel = ShowMenu();
  if (sel == EXIT) return FALSE;

  _fputts(_T("Input num1, num2: "), stdout);
  _tscanf(_T("%d %d"), &num1, &num2);

  __try {
    switch (sel) {
      case DIV: Divide(num1, num2);   break;
      case MUL: Multiply(num1, num2); break;
      case ADD: Add(num1, num2);      break;
      case MIN: Min(num1, num2);      break;
    }
  } __except (FilterFunction(GetExceptionCode())) {
    _fputts(_T("__except \n\n"), stderr);
  }
  return TRUE;
}

DWORD FilterFunction(DWORD exptType) {
  switch (exptType) {
    case EXCEPTION_ACCESS_VIOLATION:
      _fputts(_T("Access violation \n\n"), stderr);
      return EXCEPTION_EXECUTE_HANDLER;

    case EXCEPTION_INT_DIVIDE_BY_ZERO:
      _fputts(_T("Wrong number inserted. \n"), stderr);
      _fputts(_T("Input second number again: "), stderr);
      _tscanf(_T("%d"), &num2);
      return EXCEPTION_CONTINUE_EXECUTION;

    default:
      return EXCEPTION_EXECUTE_HANDLER;
  }
}

void Divide(int a, int b) { _tprintf(_T("%d ÷ %d = %d \n\n"), a, b, a / b); }

void Multiply(int a, int b) { _tprintf(_T("%d × %d = %d \n\n"), a, b, a * b); }

void Add(int a, int b) { _tprintf(_T("%d + %d = %d \n\n"), a, b, a + b); }

void Min(int a, int b) { _tprintf(_T("%d - %d = %d \n\n"), a, b, a - b); }
