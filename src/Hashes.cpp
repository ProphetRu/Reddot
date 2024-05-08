#include "Hashes.h"
#include <stdexcept>
#include <boost/uuid/detail/md5.hpp>
#include <Poco/SHA1Engine.h>
#include <Poco/DigestStream.h>
#include <Poco/DigestEngine.h>

namespace Hashes
{
    namespace ud = boost::uuids::detail;

    std::string Hashes::GetMD5(std::string_view str)
    {
        if (str.empty())
        {
            throw std::invalid_argument("Argument for MD5 is empty");
        }

        ud::md5 hash{};
        ud::md5::digest_type digest{};

        hash.process_bytes(str.data(), str.size());
        hash.get_digest(digest);

        const auto char_digest{ reinterpret_cast<const char*>(&digest) };
        return { char_digest, char_digest + sizeof(digest) };
    }

    std::string Hashes::GetSHA1(std::string_view str)
    {
        if (str.empty())
        {
            throw std::invalid_argument("Argument for SHA1 is empty");
        }

        Poco::SHA1Engine sha1{};
        Poco::DigestOutputStream ds{ sha1 };
        ds << str;
        ds.close();
        return Poco::DigestEngine::digestToHex(sha1.digest());
    }
}
