.cpp and .hpp files are stores in src/ for the main executable, test/ for test.*, and catch/ for catch
requirements. notes/ contains intermediate text files written over the course of the project, while the
finalized files are stored in report/. Data for the project from OpenFlights is stored in data/, and it
is recommended that any written files are also kept there.

To run, first compile by running make. This will create a file called a.out in the working directory,
and a directory called build which will contain .o and .d files, sorted into directories in the same
way as the source files are. A nix environment is also available but not nessecary. Several flags
can be used with the executable; for a list, run ./a.out -h. Results of the project can be written
to output files or queried via command line using these flags.

A basic test suite is available with make test. This will create a filed called test in the working
directory. This can be ran with ./test.