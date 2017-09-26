#pragma once
#include <string>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
//#include <boost/serialization/binary_object.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

/////////////////////////////////////序列化，感觉不适合用在流处理中/////////////////////
#pragma pack(1)
struct STRPACKET
{
public:
	STRPACKET():_name(""), _id(0) {};
	STRPACKET(int ID, std::string str) :_name(str), _id(ID) 
	{
		//_scores.push_back(5.3322);
		//_scores.push_back(15.3322);
	};
	~STRPACKET() {};

	const STRPACKET& operator = (const STRPACKET& other)
	{
		if (this != &other)
		{
			_name = other._name;
			_id = other._id;
			_scores = other._scores;
		}
		return (*this);
	}
private:
	friend boost::serialization::access;        //声明友元，授予访问权限
	template<typename Archive>
	void serialize(Archive & ar, const unsigned int version) //序列化函数
	{
		ar & _id;
		ar & _name;
		ar & _scores;
	}
private:
	std::string _name;
	int _id;
	std::vector<double> _scores;
};
#pragma pack()