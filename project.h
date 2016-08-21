#include <string>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost;


namespace Projector
{
    // A class representing a C++ project.
    class Project
    {
    public:
        Project();
        Project(string name);
        ~Project();
        string get_name();
        string get_path();
    private:
        string name;
        filesystem::path directory;
        string git_url;
    };
}
