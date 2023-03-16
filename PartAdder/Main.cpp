#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  if (argc != 3) {
    _fputts(_T("Two arguments are needed! \n"), stdout);
    return -1;
  }

  // start에서 end까지의 합 계산하여 반환
  int start = _ttoi(argv[1]);
  int end   = _ttoi(argv[2]);
  int total = 0;
  for (int i = start; i <= end; i++) { total += i; }
  return total;
}