#include <string>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost;
using namespace boost::filesystem;

const string DEFAULT_TEMPLATE_DIR = ".projector";
const string PROJECTOR_NAME = "PROJECTOR_NAME";

namespace Projector
{
    // A class representing a C++ project.
    class Project
    {
    public:
        Project();
        Project(const string name);
        Project(const path source, const string name);
        ~Project();
        string get_name() const;
        string get_path() const;
        void copy_template_contents() const;
        bool create_project_folder() const;
    private:
        string name;
        filesystem::path source;
        filesystem::path directory;
        string git_url;
        void set_target_directory_from_string(const string dir);
        bool apply_options_to_template();
        void copy_cmake() const;
    };
}
