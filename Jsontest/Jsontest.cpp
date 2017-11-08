// Jsontest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "./json/json.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	//根节点
	Json::Value root;
	//根节点属性
	root["name"] = Json::Value("Tsybius");
	root["age"] = Json::Value(23);
	root["sex_is_male"] = Json::Value(true);

	//子节点
	Json::Value partner;

	//子节点属性
	partner["partner_name"] = Json::Value("Galatea");
	partner["partner_age"] = Json::Value(21);
	partner["partner_sex_is_male"] = Json::Value(false);

	//子节点挂到根节点上
	root["partner"] = Json::Value(partner);

	//数组形式
	root["achievement"].append("ach1");
	root["achievement"].append("ach2");
	root["achievement"].append("ach3");

	//直接输出
	//cout << "FastWriter:" << endl;
	//Json::FastWriter fw;
	//cout << fw.write(root) << endl << endl;
	cout << "StreamWriterBuilder:" << endl;
	Json::StreamWriterBuilder builder;
	std::cout <<Json::writeString(builder, root);

	////缩进输出
	//cout << "StyledWriter:" << endl;
	//Json::StyledWriter sw;
	//cout << sw.write(root) << endl << endl;

	//输出到文件
	ofstream os;
	os.open("./PersonalInfo.js");
	os << Json::writeString(builder, root);
	os.close();

    return 0;
}

