from conans import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake

class CesiumAsyncConan(ConanFile):
    name = "CesiumAsync"
    version = "0.12.0"
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of CesiumGltf here>"
    topics = ("<Put some tag here>", "<here>", "<and here>")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "CMakeToolchain", "CMakeDeps"
    requires = [
      "asyncplusplus/1.1",
      "ms-gsl/3.1.0",
      "spdlog/1.9.2",
      "sqlite3/3.37.2"
    ]
    exports_sources = [
      "include/*",
      "src/*",
      "test/*",
      "CMakeLists.txt",
      "../tools/cmake/cesium.cmake"
    ]
    cesiumNativeDependencies = [
      "CesiumUtility"
    ]

    def requirements(self):
      # For other cesium-native packages, use the same version, user, and channel.
      for lib in self.cesiumNativeDependencies:
        try:
          user = self.user
          channel = self.channel
        except ConanException:
            self.requires("%s/%s" % (lib, self.version))
        else:
            self.requires("%s/%s@%s/%s" % (lib, self.version, user, channel))

    def config_options(self):
      if self.settings.os == "Windows":
          del self.options.fPIC

    def build(self):
      cmake = CMake(self)
      cmake.configure()
      cmake.build()

    def package(self):
      cmake = CMake(self)
      cmake.install()
