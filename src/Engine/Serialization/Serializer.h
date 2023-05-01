#pragma once

#include <cassert>
#include <string>
#include <vector>
#include <utility>

#include "Utility/Embedded.h"
#include "Utility/Streams/FileOutputStream.h"
#include "Utility/Streams/OutputStream.h"
#include "Utility/Streams/StringOutputStream.h"
#include "Utility/Memory/Blob.h"

class Serializer {
 public:
    explicit Serializer(OutputStream *outputStream) {
        Reset(outputStream);
    }

    void Reset(OutputStream *outputStream) {
        assert(outputStream);

        outputStream_ = outputStream;
    }

    void WriteBytes(const void *src, size_t size) {
        outputStream_->write(src, size);
    }

    template<class T>
    void WriteRaw(const T *src) {
        WriteBytes(src, sizeof(T));
    }

    template<class LegacyT, class T>
    void WriteLegacy(const T *src) {
        LegacyT tmp;
        Serialize(*src, &tmp);
        WriteRaw(&tmp);
    }

    template<class T>
    void WriteRawArray(const T *src, size_t size) {
        WriteBytes(src, sizeof(T) * size);
    }

    template<class T>
    void WriteVector(const std::vector<T> &src) {
        WriteVectorInternal(src);
    }

    template<class LegacyT, class T>
    void WriteLegacyVector(const std::vector<T> &src) {
        WriteVectorInternal<LegacyT>(src);
    }

    template<class T>
    void WriteSizedVector(const std::vector<T> &src) {
        WriteVectorInternal(src, false);
    }

    template<class LegacyT, class T>
    void WriteSizedLegacyVector(const std::vector<T> &src) {
        WriteVectorInternal<LegacyT>(src, false);
    }

 private:
    template<class LegacyT = void, class T>
    void WriteVectorInternal(const std::vector<T> &src, bool writeSize = true) {
        if (writeSize) {
            uint32_t size = src.size();
            WriteRaw(&size);
        }

        constexpr bool isLegacyMode = !std::is_same_v<LegacyT, void>;
        if constexpr (isLegacyMode) {
            LegacyT tmp;
            for (const T &element : src) {
                Serialize(element, &tmp);
                WriteRaw(&tmp);
            }
        } else {
            WriteRawArray(src.data(), src.size());
        }
    }

 private:
    OutputStream *outputStream_ = nullptr;
};


class FileSerializer : private Embedded<FileOutputStream>, public Serializer {
    using StreamBase = Embedded<FileOutputStream>;
 public:
    explicit FileSerializer(const std::string &path): StreamBase(path), Serializer(&StreamBase::get()) {}

    void Close() {
        StreamBase::get().close();
    }
};

class BlobSerializer : private Embedded<std::string>, private Embedded<StringOutputStream>, public Serializer {
    using StringBase = Embedded<std::string>;
    using StreamBase = Embedded<StringOutputStream>;
 public:
    BlobSerializer(): StreamBase(&StringBase::get()), Serializer(&StreamBase::get()) {}

    Blob Close() {
        StreamBase::get().close();
        return Blob::fromString(std::move(StringBase::get()));
    }
};
