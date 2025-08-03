# desk_timer

# TODOs

[ ] For some reason, I needed to add "-isystem /usr/arm-none-eabi/include/c++/14.2.0" to the `compile_commands.json` entry for `main.cxx` in order for `clangd` to find the system includes.

[ ] Compiling and linking u8g2 as a static library does not seem to work - the final `desk_timer.elf` binary is way too large (multiple megabytes big), and while having LTO enabled via the CMake LTO settings shrinks the binary again, it doesnt work on the MCU. I did have to use `-ffunction-sections` and `-fdata-sections`, maybe that messed up the final `.bin` flash image generation, because it creates individual sections for each function and data symbol?
