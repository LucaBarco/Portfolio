#if 0
#define UNICODE
#define _UNICODE
#endif
#ifndef UNICODE
#define TCHAR CHAR
#endif
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#define BUF_SIZE    1000
#define L         (30+1)

// struct mysU has only fileds of API Windows type
struct mys {
	DWORD id;      // also INT
	DWORD rn;      // also LONG
	TCHAR n[L];
	TCHAR s[L];
	DWORD mark;    // also INT
};

int _tmain(int argc, LPTSTR argv[])
{
	HANDLE hIn;
	DWORD i, end = 0, nRd, nWrt, n;
	TCHAR in, buffer[BUF_SIZE];
	struct mys myse, tmp;
	BOOL status;
	
	//OVERLAPPED ov = { 0,0,0,0,NULL };
	LARGE_INTEGER FilePos;
	PLARGE_INTEGER lpFilePos=(PLARGE_INTEGER) malloc(sizeof(LARGE_INTEGER));
	PLARGE_INTEGER lpFileSize = (PLARGE_INTEGER)malloc(sizeof(LARGE_INTEGER));
	if (argc != 2) {
		fprintf(stderr, "Usage: cp file1\n");
		Sleep(2000);
		return 1;
	}

	hIn = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hIn == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "Cannot open input file. Error: %x\n", GetLastError());
		Sleep(2000);
		return 2;
	}
	_tprintf(_T("-----MENU-----\n\tR n: read data for students n\n\tW n:update data for students n\n\tE: End\nInsert choice:"));
	_tscanf(_T("%c"), &in);
	while (in != 'E') {
		_tscanf(_T("%d%*c"), &n);
		switch (in) {
		case 'R':
			//set file pointer
			n = n - 1;
			FilePos.QuadPart = n * sizeof(struct mys);
			SetFilePointerEx(hIn, FilePos, lpFilePos, FILE_BEGIN);
			GetFileSizeEx(hIn, lpFileSize);
			if (FilePos.QuadPart<lpFileSize->QuadPart) {


				ReadFile(hIn, &tmp, sizeof(struct mys), &nRd, NULL);
				_tprintf(_T("%d %d %s %s %d\n"), tmp.id, tmp.rn, tmp.n, tmp.s, tmp.mark);
			}
			else {
				printf("id not present!\n");
			}
			break;

		case 'W':
			n = n - 1;
			//read data
			_tprintf(_T("Insert data: id rn name surname mark\n"));
			_tscanf(_T("%d %d %s %s %d"), &myse.id, &myse.rn, myse.n, myse.s, &myse.mark);
			//set file pointer
			FilePos.QuadPart = n * sizeof(struct mys);
			SetFilePointerEx(hIn, FilePos, lpFilePos, FILE_BEGIN);
			GetFileSizeEx(hIn, lpFileSize);
			if (FilePos.QuadPart < lpFileSize->QuadPart) {
				ReadFile(hIn, &tmp, sizeof(struct mys), &nRd, NULL);

				_tprintf(_T("--> RECORD TO CHANGE: %d %d %s %s %d\n"), tmp.id, tmp.rn, tmp.n, tmp.s, tmp.mark);
			}
			else {
				printf("---> WRITING NEW RECORD\n");
			}
			SetFilePointerEx(hIn, FilePos, lpFilePos, FILE_BEGIN);
			if (!WriteFile(hIn, &myse, sizeof(struct mys), &nWrt, NULL)) {
				_tprintf(_T("Error during record update!\n"));
			}
			else {
				_tprintf(_T("--> RECORD CHANGED : %d %d %s %s %d\n"), myse.id, myse.rn, myse.n, myse.s, myse.mark);
			}
			_tscanf(_T("%*c"));
			break;

		}

		_tprintf(_T("-----MENU-----\n\tR n: read data for students n\n\tW n:update data for students n\n\tE: End\nInsert choice:"));
		_tscanf(_T("%c"), &in);
	}
	return 0;
}