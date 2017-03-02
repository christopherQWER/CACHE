//
// Created by cat on 3/1/17.
//

#ifndef PROJECT_SERIALIZIBLE_H
#define PROJECT_SERIALIZIBLE_H

#include <iostream>
#include <string>

template<class Container>
class Serializable
{
protected:
    typedef function<void(const string&, Container&)> Func;

    struct SerializerPair
    {
        Func Serializer;
        Func Deserializer;
    };

    Container* ContainerInf = 0;

    static char Add(string _key, Func _serializer, Func _deserializer)
    {
        auto& lv_Pair = m_Serializers[_key];
        lv_Pair.Serializer = _serializer;
        lv_Pair.Deserializer = _deserializer;

        return 0;
    }

public:
    virtual void Serialize(Container& _cont)
    {
        for (auto& lv_Ser : m_Serializers)
            lv_Ser.second.Serializer(lv_Ser.first, _cont);
    }

    virtual void Deserialize(Container& _cont)
    {
        for (auto& lv_Ser : m_Serializers)
            lv_Ser.second.Deserializer(lv_Ser.first, _cont);
    }

private:

    map<string, SerializerPair> m_Serializers;
};

#define UNNAMED_IMPL(x, y) UNNAMED_##x##_##y
#define UNNAMED_DECL(x, y) UNNAMED_IMPL(x, y)
#define UNNAMED UNNAMED_DECL(__LINE__ , __COUNTER__)

// Макрос UNNAMED нам нужен для генерации не повторяющихся имён

#define serialize(x) char UNNAMED = Add		\
(											\
	#x,							  			\
	[this](const std::string& _key)			\
	{										\
		::Serialize(_key, x);			    \
	},										\
	[this](const std::string& _key) 	    \
	{										\
		::Deserialize(_key, x);			    \
	}										\
)

#endif //PROJECT_SERIALIZIBLE_H
