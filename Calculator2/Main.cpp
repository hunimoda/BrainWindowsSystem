#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

enum { DIV = 1, MUL, ADD, MIN, ELSE, EXIT };

DWORD ShowMenu();
void Divide(double, double);
void Multiple(double, double);
void Add(double, double);
void Min(double, double);

int _tmain(int argc, TCHAR* argv[]) {
  STARTUPINFO si = { 0, };
  PROCESS_INFORMATION pi;
  si.cb = sizeof(si);

  TCHAR command[] = _T("C:\\Windows\\System32\\calc.exe");

  DWORD sel;
  double num1, num2;
  while (true) {
    sel = ShowMenu();
    if (sel == EXIT) return 0;
    if (sel != ELSE) {
      _fputts(_T("Input num1, num2: "), stdout);
      _tscanf(_T("%lf %lf"), &num1, &num2);
    }
    switch (sel) {
      case DIV: Divide(num1, num2); break;
      case MUL: Multiple(num1, num2); break;
      case ADD: Add(num1, num2); break;
      case MIN: Min(num1, num2); break;
      case ELSE:
        ZeroMemory(&pi, sizeof(pi));
        CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        break;
    }
  }
  return 0;
}

DWORD ShowMenu() {
  DWORD sel;
  _fputts(_T("----- Menu ----- \n"), stdout);
  _tprintf(_T("%d) Divide \n"), DIV);
  _tprintf(_T("%d) Multiple \n"), MUL);
  _tprintf(_T("%d) Add \n"), ADD);
  _tprintf(_T("%d) Minus \n"), MIN);
  _tprintf(_T("%d) Any other operations \n"), ELSE);
  _tprintf(_T("%d) Exit \n"), EXIT);
  _fputts(_T("SELECTION >> "), stdout);
  _tscanf(_T("%d"), &sel);
  return sel;
}

void Divide(double a, double b) {
  _tprintf(_T("%f ÷ %f = %f \n"), a, b, a / b);
}

void Multiple(double a, double b) {
  _tprintf(_T("%f × %f = %f \n"), a, b, a * b);
}

void Add(double a, double b) {
  _tprintf(_T("%f + %f = %f \n"), a, b, a + b);
}

void Min(double a, double b) {
  _tprintf(_T("%f - %f = %f \n"), a, b, a - b);
}