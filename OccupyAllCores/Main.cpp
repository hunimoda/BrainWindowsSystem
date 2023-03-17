#include <tchar.h>
#include <Windows.h>
#include <time.h>

#define PROCESS_COUNT 1000
#define WAIT_TIME 3

clock_t startTime;

void BusyWait();

int _tmain(int argc, TCHAR *argv[]) {
  if (argc == 1) {
    for (int i = 0; i < PROCESS_COUNT - 1; i++) {
      STARTUPINFO si = { 0, };
      PROCESS_INFORMATION pi;
      si.cb = sizeof(si);

      TCHAR command[] = _T("OccupyAllCores.exe --child");
      CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
      CloseHandle(pi.hProcess);
      CloseHandle(pi.hThread);
    }
  }

  SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

  startTime = clock();
  BusyWait();

  return 0;
}

void BusyWait() {
  while (1) {
    if (clock() - startTime > WAIT_TIME * 1'000) {
      return;
    }
  }
}