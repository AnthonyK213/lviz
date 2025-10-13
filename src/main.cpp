#include "appl/application.h"

int main(int argc, char const *argv[]) {
  auto app = std::make_unique<lviz::appl::Application>("lviz");
  app->Run();

  return 0;
}
