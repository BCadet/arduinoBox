# Install arduino-cli to ~/.local/bin
@install_arduino_cli:
    [ ! -d "~/.local/bin" ] && mkdir -p ~/.local/bin
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=~/.local/bin sh

# Ensure the arduino-cli exist
@ensure_arduino_cli:
    command -v arduino-cli 1>/dev/null 2>&1 || just install_arduino_cli


@ensure_workspace: ensure_arduino_cli
    command -v yq 1>/dev/null 2>&1 || exit "yq is not found!" 

# Install an arduino-cli platform
@platform_install *platform: ensure_workspace
    arduino-cli core install {{platform}}

# Ensure that the required platform is installed
# not needed for compilation but for flash
# arduino platform syntax is not consitent between sketch.yaml and command line
# sketch.yaml format : "<package> (<version>)"
# command line format: "<package>@<version>"
@ensure_platform platform: ensure_workspace
    arduino_platform=$(yq e '.profiles.{{platform}}.platforms[].platform' sketch.yaml) && \
    arduino_platform=$(echo $arduino_platform | sed 's| (|@|g') &&\
    arduino_platform=$(echo $arduino_platform | sed 's|)||g') &&\
    just platform_install $arduino_platform

# Install an arduino-cli library
@lib_install *lib: ensure_workspace
    arduino-cli lib install {{lib}}

# Build the sketch
@build board: ensure_workspace
    arduino-cli compile --profile {{board}} .

# upload the sketch
@flash board port="/dev/ttyACM0": (build board) (ensure_platform board)
    arduino-cli upload --port {{port}} --profile {{board}} .