#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <locale.h>
#include <Windows.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR ERROR_CMD[] = _T("'%s'(은)는 실행할 수 있는 프로그램이 아닙니다. \n");
TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");

int CmdReadTokenize();
int CmdProcessing(int);
TCHAR *StrLower(TCHAR *);

int _tmain(int argc, TCHAR *argv[]) {
  // 한글 입력을 가능케 하기 위해
  _tsetlocale(LC_ALL, _T("Korean"));

  // 매개변수 전달인자가 있는 경우의 처리를 위함
  if (argc > 2) {
    for (int i = 0; i < argc; i++) {
      _tcscpy(cmdTokenList[i - 1], argv[i]);
    }
    CmdProcessing(argc - 1);
  }

  DWORD isExit;
  while (1) {
    int tokenNum = CmdReadTokenize();
    if (tokenNum == 0) continue;

    isExit = CmdProcessing(tokenNum);
    if (isExit) {
      _fputts(_T("명령어 처리를 종료합니다. \n"), stdout);
      break;
    }
  }
  return 0;
}

/*******************************************************************************
 * 함수: int CmdReadTokenize()
 * 해설: CommandPrompt의 CmdProcessing 함수는 사용자의 선택을 입력 받는 기능과 선택에
       따른 명령어 처리 기능을 동시에 지니고 있다. 이에 사용자의 선택을 입력받는 기능을
       CmdReadTokenize 함수로 분리시켰다. 명령어가 main 함수를 통해 전달되는 경우에는
       사용자 입력이 불필요 하기 때문이다.
*******************************************************************************/
int CmdReadTokenize() {
  TCHAR currentDir[256];
  GetCurrentDirectory(256, currentDir);
  _tprintf(_T("%s>"), currentDir);

  _fgetts(cmdString, STR_LEN, stdin);
  cmdString[wcslen(cmdString) - 1] = '\0';

  TCHAR *token = _tcstok(cmdString, seps);
  int tokenNum = 0;
  while (token != NULL) {
    _tcscpy(cmdTokenList[tokenNum++], StrLower(token));
    token = _tcstok(NULL, seps);
  }
  return tokenNum;
}

/*******************************************************************************
 * 함수: TCHAR int CmdProcessing()
 * 기능: 명령어를 입력 받아서 해당 명령어에 지정되어 있는 기능을 수행한다. exit이 입력되면
       TRUE를 반환하고 이는 프로그램의 종료로 이어진다.
*******************************************************************************/
int CmdProcessing(int tokenNum) {
  BOOL isRun;
  STARTUPINFO si = { 0, };
  PROCESS_INFORMATION pi;

  TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
  TCHAR optString[STR_LEN] = { 0, };

  si.cb = sizeof(si);
  if (!_tcscmp(cmdTokenList[0], _T("exit"))) {
    return TRUE;
  } else if (!_tcscmp(cmdTokenList[0], _T("start"))) {
    if (tokenNum > 1) {
      for (int i = 0; i < tokenNum; i++) {
        _stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
      }
      _stprintf(cmdStringWithOptions, _T("%s %s"), _T("CommandPrompt.exe"),
                optString);
    } else {
      _stprintf(cmdStringWithOptions, _T("%s"), _T("CommandPrompt.exe"));
    }
    isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE,
                          CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
  } else if (!_tcscmp(cmdTokenList[0], _T("echo"))) {
    for (int i = 1; i < tokenNum; i++) {
      _stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
    }
    _tprintf(_T("%s \n"), optString);
  } else {
    _tcscpy(cmdStringWithOptions, cmdTokenList[0]);
    for (int i = 1; i < tokenNum; i++) {
      _stprintf(cmdStringWithOptions, _T("%s %s"), cmdStringWithOptions,
                cmdTokenList[i]);
    }
    isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, 0, NULL,
                          NULL, &si, &pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    if (!isRun) {
      _tprintf(ERROR_CMD, cmdTokenList[0]);
    }
  }
  return 0;
}

/*******************************************************************************
 * 함수: TCHAR *StrLower(TCHAR *pStr)
 * 기능: 문자열 내에 존재하는 모든 대문자를 소문자로 변경한다. 변경된 문자열의 포인터를
       반환한다.
*******************************************************************************/
TCHAR* StrLower(TCHAR* pStr) {
  TCHAR *ret = pStr;
  while (*pStr) {
    if (_istupper(*pStr)) {
      *pStr = _totlower(*pStr);
    }
    pStr++;
  }
  return ret;
}