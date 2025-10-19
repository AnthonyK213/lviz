#ifdef _WIN32
#include <Windows.h>
#endif

#include "appl/application.h"

#ifdef _WIN32
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
#else
int main(int argc, char const *argv[])
#endif
{
  lviz::appl::Application app{"lviz"};
  app.Run();
  return 0;
}
