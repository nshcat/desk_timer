cmake -S . -B bld -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1

ln -s ./bld/compile_commands.json ./compile_commands.json
