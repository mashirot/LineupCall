project(LineupCall C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(LineupCall main.c manu.c manu.h manage.c manage.h file.c file.h data.c data.h util.c util.h)
