/* Projector

 */

//#include <boost/program_options.hpp>
#include "project.h"
#include "docopt.h"
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>

using namespace docopt;
using namespace std;
using namespace Projector;
using namespace boost::filesystem;

static const string USAGE = R"(Projector

  Usage:
   projector <action> <name> [-d=DIR -t=DIR]

  Options:
   -h --help                   Show this screen.
   -d --project-directory DIR  Create the project in the specified directory [default: .]
   -t --template-location DIR  Template project location [default: ~/.projector]

)";

int main(int argc, char **argv)
{
    std::map<std::string, docopt::value> args
        = docopt::docopt(USAGE,
                         {argv + 1, argv + argc},
                         true,
                         "Projector 1.0",
                         false);

    // for (auto const & arg : args)
    // {
    //     cout << arg.first << "\t" << arg.second << endl;
    // }

    Project p;

    if (args["--template-location"].asString() == "~/.projector")
    {
        p = Project(args["<name>"].asString());
    }
    else
    {
        p = Project(args["--template-location"].asString(),
                    args["<name>"].asString()
                   );
    }

    bool folder_create = p.create_project_folder();

    if (folder_create)
    {
        cout << "Created folder for '"
             << args["<name>"].asString()
             << "' at '"
             << p.get_path()
             << "'"
             << endl;
    }
    else
    {
        cout << "Folder already exists for '"
             << args["<name>"].asString()
             << "' at '"
             << p.get_path()
             << "'"
             << endl;
    }
    p.copy_template_contents();

    // if (!copy_results)
    // {
    //     cerr << "Projector failed" << endl;

    //     cout << "Are you attempting to copy into a location that already exists?" << endl;
    // }

    return 0;
}
