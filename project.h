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
        Project(const string template_path, const string name);
        ~Project();
        string get_name() const;
        string get_path() const;
        bool copy_template_contents() const;
        void create_project_folder() const;
    private:
        string name;
        filesystem::path source;
        filesystem::path directory;
        string git_url;
    };
}
