#include "appl/application.h"

int main(int argc, char const *argv[]) {
  lviz::appl::Application app{"lviz"};
  app.Run();
  return 0;
}
