# Hack to run c files with 1 command like Python / Ruby
function c {
gcc $1 -o $1.out
./$1.out
}

# Hack to deploy all files to git with 1 command.
function deploy {
git add -A
git commit -a -m "Deployed by deploy.sh : $1"
git push origin master
}