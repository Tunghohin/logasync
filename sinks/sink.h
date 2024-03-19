#ifndef _SGIMG_SINK_H
#define _SGIMG_SINK_H

#include <memory>

namespace sgimg::sinks {

class SinkBase {
public:
    using ptr = SinkBase*;
    using sptr = std::shared_ptr<SinkBase>;
    using uptr = std::unique_ptr<SinkBase>;

    virtual ~SinkBase() = default;

private:
};

using sink_sptr = std::shared_ptr<sinks::SinkBase::sptr>;

} // namespace sgimg::sinks

#endif
