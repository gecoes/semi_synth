# CMakeLists.txt per al mòdul de sortida d'àudio (ALSA)

# Crea una biblioteca estàtica o compartida per a la sortida d'àudio
add_library(io_alsa_output
AlsaOutput.cpp
)

# Cerca ALSA via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(ALSA REQUIRED alsa)

# Inclou les capçaleres i enllaça les llibreries
target_include_directories(io_alsa_output
PUBLIC
    ${ALSA_INCLUDE_DIRS}
)

target_link_libraries(io_alsa_output
PUBLIC
    ${ALSA_LIBRARIES}
)

add_subdirectory(test)