//#pragma once
//#ifndef SSBO_CLASS_H
//#define SSBO_CLASS_H
//
//#include <glad/glad.h>
//#include <vector>
//#include <iostream>
//
//using namespace std;
//
//class SSBO
//{
//public:
//	GLuint ID;
//
//	~SSBO();
//	SSBO(const void * vertices, GLsizeiptr size, GLuint ShaderBindingLayout);
//	SSBO() {}
//	void Create(const void * vertices, GLsizeiptr size, GLuint ShaderBindingLayout);
//	void Bind();
//	void Unbind();
//	void Delete();
//	
//};
//
//class SSBO4MODEL
//{
//private:
//	SSBO ssbo;
//public:
//	struct Data
//	{
//	private:
//		
//		
//
//	public:
//		vector<unsigned int> offsets;
//		vector<float> data;
//
//		unsigned int getMeshCount() 
//		{
//			return offsets.size();
//		}
//		unsigned int getCurrentEnd() 
//		{
//			return data.size();
//		}
//		void append(unsigned int offs, vector<float>& dat) 
//		{
//			offsets.push_back(offs);
//			for (const auto & item : dat) 
//			{
//				data.push_back(item);
//			}
//		}
//		void append(unsigned int offs, float* dat, unsigned int sizeOfArr)
//		{
//			offsets.push_back(offs);
//			for (unsigned int i = 0; i < sizeOfArr / sizeof(float); i++)
//			{
//				data.push_back(dat[i]);
//			}
//		}
//		float* GetData() 
//		{
//			return(data.data());
//		}
//		unsigned int SizeofData()
//		{
//			return(data.size() * sizeof(float));
//		}
//	};
//
//	Data vertises[3];
//	unsigned int appendData(float* data, unsigned int size, short type) 
//	{
//		unsigned int Offset = vertises[type].getCurrentEnd();
//		vertises[type].append(vertises[type].getCurrentEnd(), data, size);
//		return Offset;
//	}
//	void BuildSSBO() 
//	{
//		ssbo.Create(vertises[0].GetData(), vertises[0].SizeofData(), 0);
//		ssbo.Create(vertises[1].GetData(), vertises[1].SizeofData(), 1);
//		ssbo.Create(vertises[2].GetData(), vertises[2].SizeofData(), 2);
//
//		cout << '\n';
//		for (const auto & item : vertises[0].offsets) 
//		{
//			cout <<' '<< item;
//		}
//
//		cout << '\n';
//		for (const auto & item : vertises[0].data)
//		{
//			cout << ' ' << item;
//		}
//	}
//	void Bind() 
//	{
//		ssbo.Bind();
//	}
//	void Unbind()
//	{
//		ssbo.Unbind();
//	}
//	void Delete() 
//	{
//		ssbo.Delete();
//	}
//
//};
//
//#endif