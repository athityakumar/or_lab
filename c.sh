# Hack to run c files with 1 command like Python / Ruby

function c {
gcc $1 -o $1.out
./$1.out
}