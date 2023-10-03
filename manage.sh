#!/usr/bin/env bash

CMD="$1"

SCRIPT="$0"
ME=$(basename $0)
DIR=$(dirname $0)

usage()
{
    echo "usage: $ME get"
    echo
    echo "  get    : collect required files on development system"
    echo "  update : update git"
    exit 99
}

do_update()
{
    echo "Updating local git repository"
    git add *.cpp README.md *.sh
    git status
}

do_get()
{
  echo "updating README.md..."
  cp --verbose --preserve --update ../../cpp-iterator-boilerplates/README.md .
}

FN="do_${CMD}"

if [ "$( type -t "$FN" )" = function ]
then
    $FN
else
    echo ""
    echo "unknown command: $1"
    echo ""
    usage
fi

exit 0

