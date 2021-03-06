#include <stdio.h>
#include <direct.h>
#include <string>

#include <SDKDDKVer.h>
#include <Windows.h>
#undef GetCurrentDirectory

int APIENTRY wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ) {
	auto GetCurrentDirectory = [ ]( ) -> std::string {
		char FilePath[ FILENAME_MAX ] = "\0";
		_getcwd( FilePath, sizeof( FilePath ) );
		return std::string( FilePath );
	};

	auto StartProcess = [ ]( std::string ExePath, HANDLE &CreatedProcHandle ) -> bool {
		STARTUPINFOA si;
		PROCESS_INFORMATION pi;

		ZeroMemory( &si, sizeof( si ) );
		ZeroMemory( &pi, sizeof( pi ) );
		si.cb = sizeof( si );

		bool Created = CreateProcessA( ExePath.data( ), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi ) > 0;
		CreatedProcHandle = pi.hProcess;

		return Created;
	};

	std::string gta_sa = GetCurrentDirectory( ) + "\\gta_sa.exe";

	HANDLE Game = NULL;
	if ( StartProcess( gta_sa, Game ) ) {
		if ( WaitForSingleObject( Game, INFINITE ) == WAIT_OBJECT_0 )
			return 0;
	} else
		MessageBox( NULL, L"Failed to start gta_sa.exe", L"Error", MB_ICONERROR | MB_OK );

	return 0;
}