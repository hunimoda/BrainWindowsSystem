#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void SoftwareException();

int _tmain(int argc, TCHAR *argv[]) {
  __try {
    SoftwareException();
  } __except (EXCEPTION_EXECUTE_HANDLER) {
    DWORD exptType = GetExceptionCode();
    _tprintf(_T("Recv exception code: 0x%X \n"), exptType);
  }
  _fputts(_T("End of main \n"), stdout);
  return 0;
}

void SoftwareException() {
  //                              |**|심각성
  //                              |..|*|MS/C
  //                              |..|.|*|예약
  //                              |..|.|.|************|환경 코드
  //                              |..|.|.|............|****************|예외 코드
  const DWORD DefinedException = 0b11'1'0'000000000000'0000000000001000;
  _tprintf(_T("Send exception code: 0x%X \n"), DefinedException);
  RaiseException(DefinedException, 0, NULL, NULL);
}