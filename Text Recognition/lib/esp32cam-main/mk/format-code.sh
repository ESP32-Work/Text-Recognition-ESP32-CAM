#!/bin/bash
set -eo pipefail
cd "$( dirname "${BASH_SOURCE[0]}" )"/..

find -name '*.h' -or -name '*.[hc]pp' -or -name '*.ino' | \
  xargs clang-format-11 -i -style=file
