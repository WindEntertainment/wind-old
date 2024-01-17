#include "logger/streams/logger_stream.h"

namespace wind {
    namespace logger {
        class CombineStream : public Stream {
        public:
            CombineStream(vector<Stream*> streams);
            ~CombineStream();
        private:
            vector<Stream*> m_streams;
        public:
            void write(const string& msg) override;
        };
    }
}