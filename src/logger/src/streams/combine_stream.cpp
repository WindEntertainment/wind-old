#include <streams/combine_stream.h>

namespace wind
{
    namespace logger
    {
        CombineStream::CombineStream(vector<Stream *> streams)
        {
            m_streams = streams;
        }

        CombineStream::~CombineStream()
        {
            for (auto stream : m_streams)
                delete stream;
        }

        void CombineStream::write(const string &_msg)
        {
            for (auto stream : m_streams)
                stream->write(_msg);
        }
    }
}