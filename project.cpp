#include <boost/filesystem.hpp>
#include "project.h"
#include "exceptions.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

using namespace boost::filesystem;
using namespace Projector;

Project::Project()
{

}

Project::Project(const string name) : name{name}
{
    source = getenv("HOME");
    source /= DEFAULT_TEMPLATE_DIR;
    set_target_directory_from_string(name);
}

Project::Project(const path source, const string name) : name{name}, source{source}
{
    set_target_directory_from_string(name);

    cerr << "After constructor, directory is... " << directory << endl;
}

Project::~Project()
{

}

void Project::set_target_directory_from_string(const string dir)
{
    if (dir[0] == '/')
    {
        directory = absolute(path(dir));
    }
    else
    {
        // assume that the target is a child of the current directory
        directory = filesystem::current_path();
        directory /= dir;
    }
}

string Project::get_name() const
{
    return name;
}

string Project::get_path() const
{
    return directory.string();
}

/* Creates a project folder.

   Returns `true` if the folder can be created.
   Returns `false`` if the folder already exists.
*/
bool Project::create_project_folder() const
{
    bool success = false;
    bool exists = filesystem::exists(directory);

    if (!exists)
    {
        success = filesystem::create_directories(directory);

        if (!success)
        {
            BOOST_THROW_EXCEPTION(ProjectCreateFailed{});
        }
    }

    return success;
}

void Project::copy_template_contents() const
{
    cerr << "Source is " << source << endl;
    cerr << "Destination is " << directory << endl;

    // now we're free to copy all the files in the template
    for (directory_entry & x : directory_iterator(source))
    {
        path target = directory;
        target /= x.path().filename();

        if (x.path().filename() == "CMakeLists.txt")
        {
            copy_cmake();
        }
        else
        {
            filesystem::copy_file(x, target);
        }
    }
}

void Project::copy_cmake() const
{
    path t = source;
    path cmake_in = t /= "CMakeLists.txt";
    t = directory;
    path cmake_out = t /= "CMakeLists.txt";

    string buf;
    size_t len = PROJECTOR_NAME.length();

    ifstream read_file(cmake_in.string());
    ofstream out_file(cmake_out.string());

    while (getline(read_file, buf))
    {
        while (true)
        {
            size_t pos = buf.find(PROJECTOR_NAME);
            if (pos != string::npos)
            {
                buf.replace(pos, len, name);
            }
            else
            {
                break;
            }
        }

        out_file << buf << '\n';
    }

    out_file.flush();
    out_file.close();
    read_file.close();
}
