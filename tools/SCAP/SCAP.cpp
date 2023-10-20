#include <Sosage/Utils/asset_packager.h>

int main (int argc, char** argv)
{
  if (argc < 3)
  {
    std::cerr << "Usage: " << argv[0] << " [input_folder] [output_folder]" << std::endl;
    std::cerr << "Usage: " << argv[0] << " [input_folder] [output_folder] -d to decompress" << std::endl;
    return EXIT_SUCCESS;
  }

  std::string root = argv[1];
  std::string out = argv[2];
  if (argc == 4)
    Sosage::SCAP::decompile_package (root, out);
  else
    Sosage::SCAP::compile_package (root, out);

  return EXIT_SUCCESS;
}
