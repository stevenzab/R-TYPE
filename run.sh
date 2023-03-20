#!/bin/bash

CONAN_SYSREQUIRES_SUDO="1" conan install . -c tools.system.package_manager:mode=install --build=missing && cmake . -G "Unix Makefiles" && cmake --build .