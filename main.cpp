#include <iostream>
#include <ctime>
#include <sstream>
#include <functional>

#include "serializer.hpp"
#include <tabulate/table.hpp>

struct Entry {
    std::string type;
    std::string operation;
    std::string place;
};

void profile(void (Serializer::*function)(), Serializer& obj, const Entry& e, tabulate::Table& t) {
    clock_t time;
    time = clock();
    (obj.*function)(); // calling function which is a non-static method of class Serializer
    double diff = clock() - time;
    size_t data_size = obj.GetDataSize();
    std::stringstream time_ss, memory_ss;
    time_ss << diff / (CLOCKS_PER_SEC / 1000)  << " ms/" << diff / CLOCKS_PER_SEC << " s";
    memory_ss << data_size << " b/" << data_size / 1024 << " Kb/" << data_size / (1024 * 1024) << " Mb";
    t.add_row({{e.type, e.operation, e.place, time_ss.str(), memory_ss.str()}});
}

int main() {
    std::cout << "Generating Data Structure...\r" << std::flush;
//    DataStruct data_struct = GetSimpleStruct();
    DataStruct data_struct = GenerateStruct(StructSize::Small); // Small/Medium/Large
    Serializer bs(data_struct);
    std::cout << "Generating Data Structure...OK" << std::endl;

    // configuring beautiful output magic :)
    tabulate::Table table_info;
    table_info.add_row({"Type", "Operation", "Place", "Time", "Memory"});
    table_info.format().font_align(tabulate::FontAlign::center);
    for (size_t i = 0; i < 5; ++i) {
        table_info[0][i].format()
            .font_align(tabulate::FontAlign::center)
            .font_color(tabulate::Color::grey)
            .font_style({tabulate::FontStyle::bold})
            .font_background_color(tabulate::Color::white);
    }

    std::cout << "Serialization running...\r" << std::flush;

    profile(&Serializer::SerializeBinary, bs, {"Binary\n(Boost)", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeBinary, bs, {"Binary\n(Boost)", "Deserialization", "RAM"}, table_info);
    profile(&Serializer::SerializeXML, bs, {"XML", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeXML, bs, {"XML", "Deserialization", "RAM"}, table_info);
    profile(&Serializer::SerializeText, bs, {"Raw text", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeText, bs, {"Raw text", "Deserialization", "RAM"}, table_info);
    profile(&Serializer::SerializeJSON, bs, {"JSON", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeJSON, bs, {"JSON", "Deserialization", "RAM"}, table_info);
    profile(&Serializer::SerializeProtobuf, bs, {"Protobuf", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeProtobuf, bs, {"Protobuf", "Deserialization", "RAM"}, table_info);
    profile(&Serializer::SerializeAvro, bs, {"Avro", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeAvro, bs, {"Avro", "Deserialization", "RAM"}, table_info);
    profile(&Serializer::SerializeYAML, bs, {"YAML", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeYAML, bs, {"YAML", "Deserialization", "RAM"}, table_info);

    table_info.add_row({"---------","---------","---------","---------","---------"});


    profile(&Serializer::SerializeBinaryToFile, bs, {"Binary\n(Boost)", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeBinaryFromFile, bs, {"Binary\n(Boost)", "Deserialization", "File"}, table_info);
    profile(&Serializer::SerializeXMLToFile, bs, {"XML", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeXMLFromFile, bs, {"XML", "Deserialization", "File"}, table_info);
    profile(&Serializer::SerializeTextToFile, bs, {"Raw text", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeTextFromFile, bs, {"Raw text", "Deserialization", "File"}, table_info);
    profile(&Serializer::SerializeJSONToFile, bs,{"JSON", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeJSONFromFile, bs,{"JSON", "Deserialization", "File"}, table_info);
    profile(&Serializer::SerializeProtobufToFile, bs, {"Protobuf", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeProtobufFromFile, bs, {"Protobuf", "Deserialization", "File"}, table_info);
    profile(&Serializer::SerializeAvroToFile, bs, {"Avro", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeAvroFromFile, bs, {"Avro", "Deserialization", "File"}, table_info);
    profile(&Serializer::SerializeYAMLToFile, bs, {"YAML", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeYAMLFromFile, bs, {"YAML", "Deserialization", "File"}, table_info);

    // TODO to implement progress bar
    std::cout << "Serialization running...OK" << std::endl;
    std::cout << table_info << std::endl;
    std::cout << "Serialization finished." << std::endl;
    return 0;
}





