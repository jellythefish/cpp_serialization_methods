#include "serializer.hpp"

#include <fstream>

Serializer::Serializer(const DataStruct& data_struct) :
    data_struct(data_struct),
    ds_message(GenerateProtoMessage(data_struct)) {}

size_t Serializer::GetDataSize() const {
    if (current_mode == SerializerMode::RAM) {
        std::stringstream tmp;
        switch (current_type) {
            case SerializerType::Binary:
            case SerializerType::XML:
            case SerializerType::Text:
            case SerializerType::JSON:
            case SerializerType::MsgPack:
            case SerializerType::Protobuf:
                return ss.str().size();
            case SerializerType::Avro:
                return avro_os->byteCount();
            case SerializerType::Yaml:
                tmp << tree;
                return tmp.str().size();
        }
    } else {
        std::ifstream in_file(filepath + filename, std::ios::binary);
        in_file.seekg(0, std::ios::end);
        return in_file.tellg();
    }
    return -1;
}
