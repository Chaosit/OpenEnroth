#include "EmbeddedFileSystem.h"

#include <vector>
#include <string>
#include <memory>

#include "Utility/Streams/MemoryInputStream.h"

EmbeddedFileSystem::EmbeddedFileSystem(cmrc::embedded_filesystem base, std::string_view displayName) : _base(base), _displayName(displayName) {}

EmbeddedFileSystem::~EmbeddedFileSystem() = default;

bool EmbeddedFileSystem::_exists(const FileSystemPath &path) const {
    return _base.exists(path.string());
}

FileStat EmbeddedFileSystem::_stat(const FileSystemPath &path) const {
    if (!_base.exists(path.string()))
        return {};

    if (_base.is_directory(path.string()))
        return FileStat(FILE_DIRECTORY, 0);

    cmrc::file file = _base.open(path.string());
    return FileStat(FILE_REGULAR, file.size());
}

std::vector<DirectoryEntry> EmbeddedFileSystem::_ls(const FileSystemPath &path) const {
    std::vector<DirectoryEntry> result;
    for (const cmrc::directory_entry &entry : _base.iterate_directory(path.string()))
        result.push_back(DirectoryEntry(entry.filename(), entry.is_file() ? FILE_REGULAR : FILE_DIRECTORY));
    return result;
}

Blob EmbeddedFileSystem::_read(const FileSystemPath &path) const {
    cmrc::file file = _base.open(path.string());
    return Blob::view(file.begin(), file.size());
}

std::unique_ptr<InputStream> EmbeddedFileSystem::_openForReading(const FileSystemPath &path) const {
    cmrc::file file = _base.open(path.string());
    return std::make_unique<MemoryInputStream>(file.begin(), file.size());
}

std::string EmbeddedFileSystem::_displayPath(const FileSystemPath &path) const {
    return _displayName + "://" + path.string();
}
