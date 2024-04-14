import os

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import copy

class MyConanFile(ConanFile):
    name = "dreich"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    exports_sources = "*"
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

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        copy(self, "LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(self, pattern="*", src=os.path.join(self.build_folder, "game", "res"), dst=os.path.join(self.package_folder, "res"))
        copy(self, pattern="game", src=os.path.join(self.build_folder, "game"), dst=os.path.join(self.package_folder), keep_path=False)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["Dreich"]
