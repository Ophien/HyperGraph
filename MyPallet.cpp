/*MIT License
*
*Copyright (c) 2018 Alysson Ribeiro da Silva
*
*Permission is hereby granted, free of charge, to any person obtaining a copy 
*of this software and associated documentation files (the "Software"), to deal 
*in the Software without restriction, including *without limitation the rights 
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
*copies of the Software, and to permit persons to whom the Software is furnished 
*to do so, subject *to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
*EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *IN NO EVENT SHALL THE AUTHORS 
*OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
*AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
*THE *SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "MyPallet.h"

MyPallet* MyPallet::instancia(0);

MyPallet::MyPallet()
{
	pallet.insert(pair<string, vec3>("branco", vec3(1,1,1)));
	pallet.insert(pair<string, vec3>("preto", vec3(0,0,0)));
	pallet.insert(pair<string, vec3>("amarelo", vec3(1,1,0)));
	//pallet.insert(pair<string, vec3>("laranja", vec3(1,0.8,0)));
	pallet.insert(pair<string, vec3>("laranja2", vec3(1,0.6f,0)));
	pallet.insert(pair<string, vec3>("vermelho", vec3(1,0,0)));
	pallet.insert(pair<string, vec3>("lilas", vec3(1,0,1)));
	pallet.insert(pair<string, vec3>("rosa", vec3(1,0.8f,1)));
	pallet.insert(pair<string, vec3>("verde", vec3(0.8f,1,0)));
	//pallet.insert(pair<string, vec3>("verde1", vec3(0.8,0.8,0)));
	//pallet.insert(pair<string, vec3>("verde2", vec3(0.2,0.8,0)));
	pallet.insert(pair<string, vec3>("marrom", vec3(0.8f,0.4f,0)));
	//pallet.insert(pair<string, vec3>("marrom2", vec3(0.6,0.2,0)));
	//pallet.insert(pair<string, vec3>("marron3", vec3(0.4,0,0)));
	pallet.insert(pair<string, vec3>("azul", vec3(0.4f,0.4f,1)));
	//pallet.insert(pair<string, vec3>("azul2", vec3(0.4,0.2,1)));
	//pallet.insert(pair<string, vec3>("azul3", vec3(0,0,1)));
	pallet.insert(pair<string, vec3>("roxo", vec3(0.6f,0,0.8f)));
	//pallet.insert(pair<string, vec3>("roxo2", vec3(0.4,0,0.4)));

	palletB.insert(pair<int, string>(11,"branco"));
	palletB.insert(pair<int, string>(10,"preto"));
	palletB.insert(pair<int, string>(9,"amarelo"));
	//pallet.insert(pair<int, string>("laranja", vec3(1,0.8,0)));
	palletB.insert(pair<int, string>(8,"laranja2"));
	palletB.insert(pair<int, string>(7,"vermelho"));
	palletB.insert(pair<int, string>(6,"lilas"));
	palletB.insert(pair<int, string>(5,"rosa"));
	palletB.insert(pair<int, string>(4,"verde"));
	//pallet.insert(pair<int, string>("verde1", vec3(0.8,0.8,0)));
	//pallet.insert(pair<int, string>("verde2", vec3(0.2,0.8,0)));
	palletB.insert(pair<int, string>(3,"marrom"));
	//pallet.insert(pair<int, string>("marrom2", vec3(0.6,0.2,0)));
	//pallet.insert(pair<int, string>("marron3", vec3(0.4,0,0)));
	palletB.insert(pair<int, string>(2,"azul"));
	//pallet.insert(pair<int, string>("azul2", vec3(0.4,0.2,1)));
	//pallet.insert(pair<int, string>("azul3", vec3(0,0,1)));
	palletB.insert(pair<int, string>(1,"roxo"));
	//pallet.insert(pair<int, string>("roxo2", vec3(0.4,0,0.4)));
}
 
MyPallet* MyPallet::getInstance()
{
	if(!instancia)
		instancia = new MyPallet();
	return instancia;
}

MyPallet::~MyPallet(void)
{
}
