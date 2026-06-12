#include <fstream>
#include <exception>

namespace seneca {
    //???

Filesystem::Filesystem(const char* filename, const std::string& root_name)
 std::ifstream file(filename);

}

m_root = new Directory(root_name);
m_current = m_root;

std::string record;

while (file) {
    std::getline(file, record);
    std::string path;

    size_t path_terminator = record.find_first_of('|');
    if (path_terminator == std::string::npos) {
        path = _trim(record);
    }
    else {
        //???
    }

  //????
  Filesystem::Filesystem(Filesystem&& src) no except {
    *this = std::move(src);
  }

  Filesystem& Filesystem::operator=(Filesystem&& src) noexcept {
    if (this != &src)
    {
        delete m_root;
        ///??
    }
  }
}