from conan import ConanFile
from conan.tools.cmake import cmake_layout


class SDL3LearningConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        # SDL3 for graphics and window management
        self.requires("sdl/3.2.20")
        # Catch2 for unit testing
        self.requires("catch2/3.5.2")

    def configure(self):
        # Force static linking for all dependencies
        self.options["sdl"].shared = False
        self.options["catch2"].shared = False

    def layout(self):
        cmake_layout(self)
