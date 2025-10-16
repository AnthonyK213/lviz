#ifdef WIN32
#include <Windows.h>
#endif

#include "appl/application.h"

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nShowCmd)
#else
int main(int argc, char const *argv[])
#endif
{
  lviz::appl::Application app{"lviz"};
  app.Run();
  return 0;
}
