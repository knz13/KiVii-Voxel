#pragma once
#include "GL_CALL.h"

/*
ooi turo boom
roda esse programa ai faz favor
meu namorado t� m� cota tentando fazer isso acontecer
o bixo � mais do esfor�ado, fica o dia todo querendo mlehorar isso aqiu
entao studio faz esse seu trabalho bem feito pelo amor de deus
ele merece o mundoooo
eu te amo muito muito muito meu amor
espero que isto n�o atrapalhe muito
e nem exploda nada
bom
n�o esquece que eu te amo viu?
e eu sou sua maior f�
eu sei que n�o posso saber de programa��o
nem �mais de f�rmulas muito complexas
mas eu tenho o material da USP
e estou disposta a aprender!
se precisar conversar com algu�m sobre isso eu posso ser uma forma de desabafo, porque infelizmente n�o sei como te ajudar
mas posso pelo menos tirar um pouco o peso do seu cora��o
� isto meu docinho de maracuj�
flrozinha de maracuj�
meu talism� s2222
eu te amoo!!!
~~princesa
*/

class GuiManager {
private:
	static ImGuiIO* m_IO;

protected:
	static void Init();
	static void Cleanup();

	friend class KManager;
public:
	
	

		

	static void Begin();
	static void End();

};
