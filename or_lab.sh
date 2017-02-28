# Hack to run c files with 1 command like Python / Ruby
function or_c {
gcc $1 -o $1.out
./$1.out
ls
}

# Hack to push all files to git with 1 command.
function or_push {
cd ~/or_lab/
git add -A
git commit -a -m "Deployed by bash : $1"
git push origin master
ls
}

# Hack to pull all files to git with 1 command. Assumes no merge conflictss. Dies otherwise.
function or_pull {
cd ~/or_lab/
git add -A
git stash
git pull origin master
}

# Too lazy to type 6 extra characters
function or_cd {
cd ~/or_lab/
}

# Hack : cd = cd + ls
function cd {
builtin cd $1
ls
}