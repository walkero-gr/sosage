#include <Sosage/Core/Asset_manager.h>
#include <Sosage/Core/Port.h>
#include <Sosage/Utils/error.h>
#include <Sosage/Engine.h>

#if defined(__amigaos4__) || defined(__morphos__)
#define VSTRING     "sosage 1.6.1 (09.01.2025)"
#define VERSTAG     "\0$VER: " VSTRING
#endif

#ifdef __amigaos4__
static const char *stack __attribute__((used)) = "$STACK:102400";
static const char *version __attribute__((used)) = VERSTAG;
#endif

#ifdef __morphos__
  unsigned long __stack = 1000000;
  UBYTE VString[] = VERSTAG;
#endif

int main (int argc, char** argv)
{
  Sosage::Engine sosage(argc, argv);

#ifdef SOSAGE_INSTALL_DATA_FOLDER
  if (sosage.run(Sosage::Core::File_IO::base_path() + SOSAGE_INSTALL_DATA_FOLDER))
  {
    return EXIT_SUCCESS;
  }
#endif
  return (sosage.run(SOSAGE_DATA_FOLDER) ? EXIT_SUCCESS : EXIT_FAILURE);
}

SOSAGE_PORT_MAIN

