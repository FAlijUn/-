cmake_minimum_required(VERSION 2.8.12)

project(SVM)

set(CMAKE_CXX_STANDARD 11)

# Tell cmake we will need dlib.  This command will pull in dlib and compile it
# into your project.  Note that you don't need to compile or install dlib.  All
# cmake needs is the dlib source code folder and it will take care of everything.
add_subdirectory(./dlib-19.24/dlib dlib_build)

# The next thing we need to do is tell CMake about the code you want to
# compile.  We do this with the add_executable() statement which takes the name
# of the output executable and then a list of .cpp files to compile. 
add_executable(svm svm.cpp)
# Finally, you need to tell CMake that this program, assignment_learning_ex,
# depends on dlib.  You do that with this statement: 
target_link_libraries(svm dlib::dlib)

