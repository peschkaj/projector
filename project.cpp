#include "project.h"
#include "exceptions.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace boost::filesystem;
using namespace Projector;

Project::Project() {}

Project::Project(const string name) : name{name} {
  source = getenv("HOME");
  source /= DEFAULT_TEMPLATE_DIR;
  set_target_directory_from_string(name);
}

Project::Project(const path source, const string name)
    : name{name}, source{source} {
  set_target_directory_from_string(name);

  cerr << "After constructor, directory is... " << directory << endl;
}

Project::~Project() {}

void Project::set_target_directory_from_string(const string dir) {
  if (dir[0] == '/') {
    directory = absolute(path(dir));
  } else {
    // assume that the target is a child of the current directory
    directory = filesystem::current_path();
    directory /= dir;
  }
}

string Project::get_name() const { return name; }

string Project::get_path() const { return directory.string(); }

// Creates a project folder.
//
// Returns `true` if the folder can be created.
// Returns `false`` if the folder already exists.
bool Project::create_project_folder() const {
  boost::system::error_code ec;
  bool success = false;
  bool exists = filesystem::exists(directory);

  if (!exists) {
    success = filesystem::create_directories(directory, ec);

    if (!success) {
      switch (ec.value()) {
        case boost::system::errc::operation_canceled: {
          cerr << "Copy operation canceled." << endl;
          break;
        }
        case boost::system::errc::permission_denied: {
          cerr << "Permission denied. \n"
               << "Make sure you have write permissions for the correct folder. \n"
               << "You used '"
               << directory.string()
               << "'" << endl;
          break;
        }
        case boost::system::errc::no_space_on_device: {
          cerr << "No space left on device.\n"
               << "In the words of Harry Harrison: Make room, make room.\n"
               << endl;
          break;
        }
        case boost::system::errc::not_a_directory: {
          cerr << "That's no directory!\n"
               << endl;
          break;
        }
        default:
          cerr << "Something bad happened. Not sure what. Check journalctl, I guess.\n"
               << "¯\_(ツ)_/¯" << endl;
          break;
      }
      BOOST_THROW_EXCEPTION(ProjectCreateFailed{});
    }
  }

  return success;
}

void Project::copy_template_contents() const {
  for (directory_entry &x : directory_iterator(source)) {
    path target = directory;
    target /= x.path().filename();

    if (x.path().filename() == "CMakeLists.txt") {
      // specialized copy for CMakeLists
      copy_cmake();
    } else {
      filesystem::copy_file(x, target);
    }
  }
}

void Project::copy_cmake() const {
  path t = source;
  path cmake_in = t /= "CMakeLists.txt";
  t = directory;
  path cmake_out = t /= "CMakeLists.txt";

  string buf;
  size_t len = PROJECTOR_NAME.length();

  ifstream read_file(cmake_in.string());
  ofstream out_file(cmake_out.string());

  while (getline(read_file, buf)) {
    while (true) {
      size_t pos = buf.find(PROJECTOR_NAME);
      if (pos != string::npos) {
        buf.replace(pos, len, name);
      } else {
        break;
      }
    }

    out_file << buf << '\n';
  }

  out_file.flush();
  out_file.close();
  read_file.close();
}
