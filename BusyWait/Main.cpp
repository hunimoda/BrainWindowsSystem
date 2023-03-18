#include <tchar.h>
#include <Windows.h>
#include <time.h>

#define TIMEOUT 30'000

int _tmain(int argc, TCHAR *argv[]) {
  _tprintf(_T("Create process    (pid) %5d, using core #(%d) \n"),
           GetProcessId(GetCurrentProcess()), GetCurrentProcessorNumber());

  // Busy waiting
  const clock_t startTime = clock();
  while (1) {
    clock_t elapsedTime = clock() - startTime;
    if (elapsedTime > TIMEOUT) {
      break;
    }
  }

  _tprintf(_T("Terminate process (pid)%5d \n"),
           GetProcessId(GetCurrentProcess()));
  return 0;
}
