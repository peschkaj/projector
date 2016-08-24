#include <boost/exception/all.hpp>
#include <exception>
using namespace std;
using namespace boost;

namespace Projector
{
    typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info;

    struct ProjectCreateFailed
        : public boost::exception, public std::exception
    {
        const char * what() const noexcept {
            return "Unable to create project.";
        }
    };

    struct ParameterRequired
        : public boost::exception, public std::exception
    {
        const char * what() const noexcept {
            return "Project name (`name`) is required.";
        }
    };
}
