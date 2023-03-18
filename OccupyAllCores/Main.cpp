#define _CRT_SECURE_NO_WARNINGS

#include <tchar.h>
#include <Windows.h>

#define MAX_PROCESS_COUNT 32

int _tmain(int argc, TCHAR *argv[]) {
  // 전달인자가 두 개인지 확인
  if (argc != 3) {
    _fputts(_T("Usage: OccupyAllCores.exe [CORE_COUNT] [PROCESS_COUNT] \n"),
            stderr);
    return 1;
  }

  // 전달인자를 자연수로 변환
  const int coreCount = _ttoi(argv[1]);
  const int processCount = _ttoi(argv[2]);
  if (coreCount <= 0 || processCount <= 0 || processCount > MAX_PROCESS_COUNT) {
    _ftprintf(stderr, _T("Invalid argument: '%s', '%s' \n"), argv[1], argv[2]);
    return 2;
  }

  HANDLE processHandles[MAX_PROCESS_COUNT] = { 0, };

  // processCount개의 자식 프로세스 생성
  for (int i = 0; i < processCount; i++) {
    STARTUPINFO si = { 0, };
    PROCESS_INFORMATION pi;
    TCHAR command[128] = _T("BusyWait.exe");
    si.cb = sizeof(si);

    // 프로세스 생성
    CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    CloseHandle(pi.hThread);
    processHandles[i] = pi.hProcess;

    // 사용 코어를 지정하고 우선순위를 최우선으로 높임
    SetProcessAffinityMask(pi.hProcess, 1 << (i % coreCount));
    SetPriorityClass(pi.hProcess, REALTIME_PRIORITY_CLASS);
  }

  // 모든 자식 프로세스 종료까지 기다림
  WaitForMultipleObjects(processCount, processHandles, true, INFINITE);
  for (int i = 0; i < processCount; i++) {
    CloseHandle(processHandles[i]);
  }
  _fputts(_T("\n"), stdout);
  _fputts(_T("All processes are terminated! \n"), stdout);

  return 0;
}