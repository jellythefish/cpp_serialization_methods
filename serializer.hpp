#ifndef SERIALIZATION_SERIALIZER_H_
#define SERIALIZATION_SERIALIZER_H_

#include "struct.hpp"
#include "data_struct.pb.h"

#include <fstream>
#include <sstream>

class Serializer {
public:
    Serializer(const DataStruct& dataStruct);

    void SerializeBinary();
    void DeserializeBinary();
    void SerializeBinaryToFile();
    void DeserializeBinaryFromFile();

    void SerializeXML();
    void DeserializeXML();
    void SerializeXMLToFile();
    void DeserializeXMLFromFile();

    void SerializeText();
    void DeserializeText();
    void SerializeTextToFile();
    void DeserializeTextFromFile();

    void SerializeJSON();
    void DeserializeJSON();
    void SerializeJSONToFile();
    void DeserializeJSONFromFile();

    void SerializeProtobuf();
    void DeserializeProtobuf();
    void SerializeProtobufToFile();
    void DeserializeProtobufFromFile();

    size_t GetDataSize() const;
    std::string GetFilename() const;

private:
    std::stringstream ss; // a memory buffer for serialized data
    // TODO to fix this
    std::stringstream pb_ss; // separate for brotobufs, don't know why protobuf ser/deser breaks basic ss
    std::ofstream ofs; // for serialization to file
    std::ifstream ifs; // for deserialization from file
    const DataStruct& data_struct;
    proto::DataStruct ds_message;

    std::string filepath = "../datafiles/";
    std::string filename; // is defined in class methods
};

#endif  // SERIALIZATION_SERIALIZER_H_

