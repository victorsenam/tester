# Introduction
This tester was developed to help me with correcting programs from students. It's not well documented, it was intended for personal use and I decided to publish it just in case. This file should help a little with getting around with it. I can also help if you [email me](victorsenam@gmail.com).  
The necessary folders for problem-setting:
- `generator`
- `validator`
- `checker`
- `judge`
- `standart`

# Samples
Set samples can be found on the `samples/` folder. Those are the exercices corrected by me with this judge. I'll describe them in `samples/README.sh`. This judge was continuously developed during this time, so basically every exercice uses a different version of `judge.sh`. The best ones are in `5-3-24`, `5-2-8` and `4-2-35`, just copying one of those to the `tester/` folder might be a good start.

# Generator
- Code `generator/generator.cpp`
- Code `validator/validator.cpp`
- Set generator input arguments on `generator\_descriptor.txt`
- Run `./generator/run\_generator.sh < generator/generator\_descriptor.txt`
This is very much like setting a problem on codeforces polygon system. Tutorials on that might help. Samples can be found on the [testlib repository](https://github.com/MikeMirzayanov/testlib).

# Checker
Very much like generators, checkers work on polygon style, should be added to `checker\checker.cpp`.

# Judge
Contains two files, `judge.sh` and `judge\_all.sh`.

## judge.sh
`judge.sh` recieves the folder to be tested as an argument and runs every test on that. It produces two output files on that folder: `judge.out` with the final results and `judge.log` with a debug log. Samples of this program can be found on `judge/samples/` and are described below.  
This program also copies the content of `standart/` into the target folder and deletes some files from the target folder (every `*.class/`, for instance). You should code a Runner inside the `standart/` folder. It should call the functions on the program to be tested and output something to be checked (topcoder style). You can also ignore that and set the judge to run the program to be tested directly (if the main function is well specified).  
Every precoded judge outputs in portuguese.

### simple.sh
Classical correction judge (each test gets Accepted, Wrong Answer, Runtime Error or Time Limit Exceded) and outputs these quantities to judge.out (used in `4-2-35`). It also provides an idea of multiple compilation methods.
Also, it relies on submission's main, it doesn't use a Runner.

### partial\_single.sh
Partial correction with interesting add-ons (used in `5-2-8`). It accepts files with both 1-indexed and 0-indexed outputs, it removes null chars from output.

### partial\_multi.sh
Partial correction judge and with multiple judges (used in `5-3-24`).

## Answer files
The judge will search for the correct answer files in `solution/answer`. Coding the correct solution in `solution/code/` is a good idea.

