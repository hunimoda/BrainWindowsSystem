#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  HANDLE hReadPipe, hWritePipe;
  TCHAR message[1024];

  if (argc == 1) {
    // 파이프 생성 매개변수 준비
    SECURITY_ATTRIBUTES sa;
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;
    sa.nLength = sizeof(sa);

    // 파이프 생성
    CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);

    // 자식 프로세스 생성 매개변수 준비
    PROCESS_INFORMATION pi;
    STARTUPINFO si = { 0, };
    si.cb = sizeof(si);
    TCHAR command[] = _T("");
    _stprintf(command, _T("AnonymousPipeBetweenProcess.exe %p %p"),
              hReadPipe, hWritePipe);

    // 자식 프로세스 생성
    CreateProcess(NULL, command, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL,
                  NULL, &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hReadPipe);

    // 파이프를 통해 문자열 송신
    DWORD bytesWritten;
    while (1) {
      _fputts(_T("send>"), stdout);
      _fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);

      if (!WriteFile(hWritePipe, message, sizeof(TCHAR) * _tcslen(message),
                     &bytesWritten, NULL)) {
        _fputts(_T("Cannot write! \n"), stderr);
        break;
      }
      if (!_tcsncmp(message, _T("exit"), 4)) break;
    }
    Sleep(3'000);
    CloseHandle(hWritePipe);
  } else if (argc == 3) {
    // 전달인자를 핸들로 변환
    _stscanf(argv[1], _T("%p"), &hReadPipe);
    _stscanf(argv[2], _T("%p"), &hWritePipe);
    CloseHandle(hWritePipe);

    // 파이프를 통해 문자열 수신
    DWORD bytesRead;
    while (1) {
      if (!ReadFile(hReadPipe, message, sizeof(message) - sizeof(TCHAR),
                    &bytesRead, NULL)) {
        _fputts(_T("Cannot read! \n"), stderr);
        break;
      }
      message[bytesRead / sizeof(TCHAR)] = NULL;
      if (!_tcsncmp(message, _T("exit"), 4)) break;

      _fputts(_T("recv>"), stdout);
      _fputts(message, stdout);
    }
    CloseHandle(hReadPipe);
  }
  return 0;
}