// Jsontest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "./json/json.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	//���ڵ�
	Json::Value root;
	//���ڵ�����
	root["name"] = Json::Value("Tsybius");
	root["age"] = Json::Value(23);
	root["sex_is_male"] = Json::Value(true);

	//�ӽڵ�
	Json::Value partner;

	//�ӽڵ�����
	partner["partner_name"] = Json::Value("Galatea");
	partner["partner_age"] = Json::Value(21);
	partner["partner_sex_is_male"] = Json::Value(false);

	//�ӽڵ�ҵ����ڵ���
	root["partner"] = Json::Value(partner);

	//������ʽ
	root["achievement"].append("ach1");
	root["achievement"].append("ach2");
	root["achievement"].append("ach3");

	//ֱ�����
	//cout << "FastWriter:" << endl;
	//Json::FastWriter fw;
	//cout << fw.write(root) << endl << endl;
	cout << "StreamWriterBuilder:" << endl;
	Json::StreamWriterBuilder builder;
	std::cout <<Json::writeString(builder, root);

	////�������
	//cout << "StyledWriter:" << endl;
	//Json::StyledWriter sw;
	//cout << sw.write(root) << endl << endl;

	//������ļ�
	ofstream os;
	os.open("./PersonalInfo.js");
	os << Json::writeString(builder, root);
	os.close();

    return 0;
}

