#include <boost/filesystem.hpp>
#include "project.h"
#include "exceptions.h"

#include <iostream>
using namespace std;

using namespace boost::filesystem;
using namespace Projector;


Project::Project()
{
    BOOST_THROW_EXCEPTION(ParameterRequired{});
}

Project::Project(const string template_path, const string name) : name{name}
{
    directory = filesystem::current_path();
    directory /= name;

    source = path(template_path);
}

Project::~Project()
{

}

string Project::get_name() const
{
    return name;
}

string Project::get_path() const
{
    return directory.string();
}

void Project::create_project_folder() const
{
    bool exists = filesystem::exists(directory);

    if (!exists)
    {
        bool success = filesystem::create_directories(directory);

        if (!success)
        {
            BOOST_THROW_EXCEPTION(ProjectCreateFailed{});
        }
    }
}

bool Project::copy_template_contents() const
{
    bool success = false;
    cerr << "Source is " << source << endl;
    cerr << "Destination is " << directory << endl;

    if (exists(directory))
        return false;

    // now we're free to copy all the files in the template
    for (directory_entry & x : directory_iterator(source))
    {
        path target = directory;
        target /= x.path().filename();

        filesystem::copy_file(x, target);
    }

    return success;
}
