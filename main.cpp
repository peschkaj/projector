/* Projector

 */

//#include <boost/program_options.hpp>
#include "project.h"
#include "docopt.h"
#include <string>
#include <iostream>

using namespace docopt;
using namespace std;
using namespace Projector;
//namespace po = boost::program_options;

static const string USAGE = R"(Projector

  Usage:
   projector new <name>

  Options:
   -h --help  Show this screen.
   -d --project-directory Create the project in the specified directory. Defaults to '.'
   -t --template-location Template project location. Defaults to '.projector'

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
    //     cout << arg.first << arg.second << endl;
    // }


    // Project p(source, project_name);
    // p.create_project_folder();
    // bool copy_results = p.copy_template_contents();

    // if (!copy_results)
    // {
    //     cerr << "Projector failed" << endl;

    //     cout << "Are you attempting to copy into a location that already exists?" << endl;
    // }

    return 0;
}
