from conans import ConanFile

class SliceConan(ConanFile):
    name = "slice"
    version = "0.2.0"
    url = "https://github.com/hnOsmium0001/slice"
    description = "Container slice library for C++14 and above"
    license = "CC0-1.0"
    exports_sources = "include/*"
    no_copy_source = True

    def package(self):
        self.copy("*.hpp")

    def package_id(self):
        self.info.header_only()
