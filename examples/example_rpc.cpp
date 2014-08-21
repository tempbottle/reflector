/*
    Boost Software License - Version 1.0 - August 17, 2003

    Permission is hereby granted, free of charge, to any person or organization
    obtaining a copy of the software and accompanying documentation covered by
    this license (the "Software") to use, reproduce, display, distribute,
    execute, and transmit the Software, and to prepare derivative works of the
    Software, and to permit third-parties to whom the Software is furnished to
    do so, all subject to the following:

    The copyright notices in the Software and this entire statement, including
    the above license grant, this restriction and the following disclaimer,
    must be included in all copies of the Software, in whole or in part, and
    all derivative works of the Software, unless such copies or derivative
    works are solely in the form of machine-executable object code generated by
    a source language processor.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <reflection/api.hpp>
#include <reflection/basic_types.hpp>
#include <reflection/class.hpp>
#include <reflection/rpc.hpp>

#include <utility/memory_reader_writer.hpp>

// Type declarations common for server and client

using std::string;

struct CachePolicy_t {
    string policy;
    uint64_t maxDataUsage;
    int timeout;

    REFL_BEGIN("CachePolicy_t", 1)
        REFL_FIELD(policy)
        REFL_FIELD(maxDataUsage)
        REFL_FIELD(timeout)
    REFL_END
};

// Client-side function usage

int getResourceFromServer(const string& resource, unsigned int maxSize, const CachePolicy_t& cp);

RPC_SERIALIZED_3(getResourceFromServerRPC, getResourceFromServer)

int main(int argc, char* argv[]) {
    CachePolicy_t cp = {"static-only", 4096, 3600};
    int result = getResourceFromServerRPC("/test", 3000, cp);

    printf("[CLIENT]\tResult is %d\n", result);
}

// Server-side function implementation

int getResourceFromServer(const string& resourceName, unsigned int maxSize, const CachePolicy_t& cp) {
    printf("[SERVER]\tgetResourceFromServer(%s, %u, [%s, max %u kB, %d s])\n", resourceName.c_str(), maxSize,
            cp.policy.c_str(), (unsigned) cp.maxDataUsage, cp.timeout);

    return 42;
}

DEFINE_RPC_SERIALIZED(getResourceFromServerWrapper, getResourceFromServer)

// Implementation of byte-level RPC transport
// In this example, we just stuff everything into a buffer

namespace rpc {
    string rpcFunctionName;
    utility::MemoryReaderWriter io;

    // Called by client when initiating a RPC request
    // Returned writer and reader are used for serializing the arguments and deserializing
    // the response, respectively
    bool beginRPC(const char* functionName, IWriter*& writer_out, IReader*& reader_out) {
        rpcFunctionName = functionName;
        writer_out = &io;
        reader_out = &io;
        return true;
    }

    // Called after all arguments are written throught the provided reader
    // After this function returns, the client will read the response
    bool invokeRPC() {
        printf("[RPC]\t%u bytes of arguments to server\n", unsigned(io.writePos));
        auto w1 = io.writePos;

        // In practice, this would be processed server-side
        if (rpcFunctionName == "getResourceFromServer")
            assert(getResourceFromServerWrapper(&io, &io));
        else
            fprintf(stderr, "Invalid RPC %s\n", rpcFunctionName.c_str());

        printf("[RPC]\t%u bytes of response from server\n", unsigned(io.writePos - w1));
        return true;
    }

    void endRPC() {
        io.reset();
    }
}

#include <reflection/default_error_handler.cpp>

/*
[RPC]   24 bytes of arguments to server
[SERVER]        getResourceFromServer(/test, 3000, [static-only, max 4096 kB, 3600 s])
[RPC]   1 bytes of response from server
[CLIENT]        Result is 42
*/
