#ifndef TEXMAT_H
#define TEXMAT_H

#include <string>

using namespace std;

class TexMat
{
	public:
		TexMat(string texture,int debut);
		TexMat();
		~TexMat();

		

		int debut;
		string texture;

	private:
		
};
#endif
