#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[]) {
  HANDLE hMailslot;
  TCHAR messageBox[50];
  DWORD bytesRead;

  // mailslot 생성
  hMailslot = CreateMailslot(SLOT_NAME, 0,MAILSLOT_WAIT_FOREVER, NULL);
  if (hMailslot == INVALID_HANDLE_VALUE) {
    _fputts(_T("Unable to create mailslot! \n"), stdout);
    return 1;
  }

  // 메시지 수신
  _fputts(_T("********** Message ********** \n"), stdout);
  while (1) {
    if (!ReadFile(hMailslot, messageBox, sizeof(messageBox), &bytesRead, NULL)) {
      _fputts(_T("Unable to read!"), stdout);
      CloseHandle(hMailslot);
      return 1;
    }
    if (!_tcsncmp(messageBox, _T("exit"), 4)) {
      _fputts(_T("Good bye! \n"), stdout);
      break;
    }
    messageBox[bytesRead / sizeof(TCHAR)] = '\0';
    _fputts(messageBox, stdout);
  }
  CloseHandle(hMailslot);
  return 0;
}