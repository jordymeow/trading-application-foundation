#include "stdafx.h"
#include "TAFServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int main(int argc, _TCHAR* argv[])
{
	try
	{
		boost::shared_ptr<TAFServer> server(new TAFServer());
		server->Run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << "Finished." << std::endl;
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	int b;
	std::cin >> b;

	return 0;
}

