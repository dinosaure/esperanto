#!/bin/bash

PATH=":$PATH:"
PATH=${PATH//":"/"::"}
PATH=${PATH//":$(opam var bin):"/}
PATH=${PATH//"::"/":"}
PATH=${PATH#:}; PATH=${PATH%:}

echo $PATH
