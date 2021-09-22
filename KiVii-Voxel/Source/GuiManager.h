#pragma once
#include "GL_CALL.h"

/*
ooi turo boom
roda esse programa ai faz favor
meu namorado tá mó cota tentando fazer isso acontecer
o bixo é mais do esforçado, fica o dia todo querendo mlehorar isso aqiu
entao studio faz esse seu trabalho bem feito pelo amor de deus
ele merece o mundoooo
eu te amo muito muito muito meu amor
espero que isto não atrapalhe muito
e nem exploda nada
bom
não esquece que eu te amo viu?
e eu sou sua maior fã
eu sei que não posso saber de programação
nem ´mais de fórmulas muito complexas
mas eu tenho o material da USP
e estou disposta a aprender!
se precisar conversar com alguém sobre isso eu posso ser uma forma de desabafo, porque infelizmente não sei como te ajudar
mas posso pelo menos tirar um pouco o peso do seu coração
é isto meu docinho de maracujá
flrozinha de maracujá
meu talismã s2222
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
