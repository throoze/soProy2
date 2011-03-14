#!/bin/bash
# Elimina los archivos chimbos

shopt -s extglob
rm $(echo !(*.h|*.c|*.pdf|nul|[mM]ake*)) 2> /dev/null
