# OR Lab

This repository that contains the code I've submitted for the course MA39014 - Operations Research Lab, IIT Kharagpur.

### Getting started

- Clone this repository
- Set this up in your shell configuration file (`~/.bashrc`, `~/.zshrc/` or `~/.fishrc`). This code snippet can also be found in [`bashrc.sh file`](https://github.com/athityakumar/or_lab/blob/master/bashrc.sh)

```
export OR_LAB_REPO_PATH=/path/to/or_lab/
source $OR_LAB_REPO_PATH/or_lab.sh
```
- Restart your terminal, or just source your shell configuration file (say, `source ~/.bashrc`for bash shell)

### Shell Commands

All tweaks required can be made, by incorporating the changes in the [`or_lab.sh`](https://github.com/athityakumar/or_lab/blob/master/or_lab.sh) file

- `or_c` : Single command to compile and execute the `*.c` file. For example, `or_c filename.c`
- `or_cpp` : Single command to compile and execute the `*.cpp` file. For example, `or_cpp filename.cpp` 
- `or_push` : Command to commit and push your changes to the remote git repository. You may have to set your git remote `origin` properly to point to a repository you have push access to. For example, `or_push "Makes these changes"`.
- `or_pull` : Single command to commit and push your changes to the remote git repository. You may have to set your git remote `origin` properly to point to a repository you have push access to. For example, simply use `or_pull` from the root directory of the git repository.
- `or_cd` : Command to directly change the directory to this path. Made for fellow developers, who might be lazy to type 6 extra characters. For example, `or_cd`.

### License

Feel free to use any code present in this repository, without any restrictions.