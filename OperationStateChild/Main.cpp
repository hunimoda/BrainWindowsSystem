#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
  float num1, num2;
  _fputts(_T("Return value test \n"), stdout);
  _tscanf(_T("%f %f"), &num1, &num2);

  if (num2 == 0) {
    exit(-1);  // or return -1;
  }

  _tprintf(_T("Operation result: %f \n"), num1 / num2);
  return 0;
}