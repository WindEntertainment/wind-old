from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class MyConanFile(ConanFile):
    name = "dreich"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    requires = [
        "spdlog/1.13.0",
        "yaml-cpp/0.8.0",
        "zlib/1.2.11",
        "stb/cci.20220909",
        "pugixml/1.13",
        "cxxopts/3.1.1",
        "glad/0.1.36",
        "glfw/3.3.8",
        "glm/cci.20230113"
    ]
    layout = cmake_layout

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "MyLibrary")
